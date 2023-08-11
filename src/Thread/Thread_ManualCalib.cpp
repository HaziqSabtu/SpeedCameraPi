#include "Event/Event_Calibration.hpp"
#include "Event/Event_Error.hpp"
#include "Event/Event_UpdatePreview.hpp"
#include "Event/Event_UpdateStatus.hpp"
#include "Model/CalibrationData.hpp"
#include "UI/Layout/StatusPanel.hpp"
#include <Thread/Thread_ManualCalib.hpp>
#include <opencv2/imgproc.hpp>
#include <wx/event.h>

BaseManualCalibrationThread::BaseManualCalibrationThread(wxEvtHandler *parent)
    : wxThread(wxTHREAD_JOINABLE) {
    this->parent = parent;

    auto config = AppConfig();
    auto previewConfig = config.GetPreviewConfig();
    int pWidth = previewConfig.width;
    int pHeight = previewConfig.height;
    this->pSize = cv::Size(pWidth, pHeight);
}

BaseManualCalibrationThread::~BaseManualCalibrationThread() {}

ManualCalibrationThread::ManualCalibrationThread(
    wxEvtHandler *parent, std::unique_ptr<CameraBase> &camera)
    : BaseManualCalibrationThread(parent), camera(std::move(camera)) {}

ManualCalibrationThread::~ManualCalibrationThread() {}

wxThread::ExitCode ManualCalibrationThread::Entry() {

    wxCommandEvent startCalibrationEvent(c_CALIBRATION_EVENT,
                                         CALIBRATION_START);
    wxPostEvent(parent, startCalibrationEvent);

    try {

        while (!TestDestroy()) {
            cv::Mat frame;
            camera->getFrame(frame);

            if (frame.empty()) {
                throw std::runtime_error("Failed to capture frame");
            }

            cv::resize(frame, frame, pSize);

            if (isLineValid(yellowLine)) {

                cv::line(frame, yellowLine.p1, yellowLine.p2,
                         cv::Scalar(0, 255, 255), 2);
            }

            if (isLineValid(blueLine)) {
                cv::line(frame, blueLine.p1, blueLine.p2, cv::Scalar(255, 0, 0),
                         2);
            }

            UpdatePreviewEvent::Submit(parent, frame);

            wxMilliSleep(100);
        }
    } catch (const std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }

    UpdatePreviewEvent::Submit(parent, CLEAR_PREVIEW);

    wxCommandEvent endCalibrationEvent(c_CALIBRATION_EVENT, CALIBRATION_END);
    wxPostEvent(parent, endCalibrationEvent);
    return 0;
}

std::unique_ptr<CameraBase> ManualCalibrationThread::getCamera() {
    return std::move(camera);
}

ThreadID ManualCalibrationThread::getID() const { return threadID; }

void BaseManualCalibrationThread::updateYellowLine(Detection::Line line) {
    std::unique_lock<std::mutex> lock(m_mutex);
    yellowLine = line;
}

void BaseManualCalibrationThread::updateBlueLine(Detection::Line line) {
    std::unique_lock<std::mutex> lock(m_mutex);
    blueLine = line;
}

CalibData ManualCalibrationThread::getCalibData() {
    std::unique_lock<std::mutex> lock(m_mutex);
    return CalibData(yellowLine, blueLine);
}

void BaseManualCalibrationThread::setPoint1(cv::Point point) {
    Detection::Line line;
    line.setP1(point);

    direction == MANUAL_LEFT ? updateBlueLine(line) : updateYellowLine(line);
}

void BaseManualCalibrationThread::setPoint2(cv::Point point) {
    Detection::Line line = direction == MANUAL_LEFT ? blueLine : yellowLine;
    line.setP2(point);

    direction == MANUAL_LEFT ? updateBlueLine(line) : updateYellowLine(line);
}

void BaseManualCalibrationThread::setPoint2f(cv::Point point) {
    Detection::Line line = direction == MANUAL_LEFT ? blueLine : yellowLine;
    line.setP2(point);

    direction == MANUAL_LEFT
        ? updateBlueLine(line.Extrapolate(pSize.height, pSize.width))
        : updateYellowLine(line.Extrapolate(pSize.height, pSize.width));
}

void BaseManualCalibrationThread::setDirection(ManualDirection direction) {
    this->direction = direction;
}

ManualDirection BaseManualCalibrationThread::getDirection() {
    return direction;
}

bool BaseManualCalibrationThread::isLineValid(Detection::Line &line) {
    if (line.p1.x == 0 && line.p1.y == 0) {
        return false;
    }

    if (line.p2.x == 0 && line.p2.y == 0) {
        return false;
    }

    return true;
}

void BaseManualCalibrationThread::setYellowLine(Detection::Line line) {
    updateYellowLine(line);
}

Detection::Line BaseManualCalibrationThread::getYellowLine() {
    std::unique_lock<std::mutex> lock(m_mutex);
    return yellowLine;
}

void BaseManualCalibrationThread::setBlueLine(Detection::Line line) {
    updateBlueLine(line);
}

Detection::Line BaseManualCalibrationThread::getBlueLine() {
    std::unique_lock<std::mutex> lock(m_mutex);
    return blueLine;
}