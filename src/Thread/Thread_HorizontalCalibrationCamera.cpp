#include "Event/Event_Calibration.hpp"
#include "Event/Event_Error.hpp"
#include "Event/Event_UpdatePreview.hpp"
#include "Event/Event_UpdateStatus.hpp"
#include "Model/CalibrationData.hpp"
#include "Thread/Thread_Base.hpp"
#include "UI/Data/StatusData.hpp"
#include "Utils/Camera/CameraBase.hpp"
#include <Thread/Thread_HorizontalCalibrationCamera.hpp>
#include <opencv2/imgproc.hpp>
#include <wx/event.h>

BaseHorizontalCalibrationThread::BaseHorizontalCalibrationThread(
    wxEvtHandler *parent, DataPtr data)
    : BaseThread(parent, data), PreviewableThread() {}

BaseHorizontalCalibrationThread::~BaseHorizontalCalibrationThread() {}

CalibrationData HorizontalCalibrationCameraThread::getCalibrationData() {
    return CalibrationData(getRealBottomLine(), getRealTopLine());
}

HorizontalCalibrationCameraThread::HorizontalCalibrationCameraThread(
    wxEvtHandler *parent, CameraPtr &camera)
    : BaseHorizontalCalibrationThread(parent, nullptr), CameraAccessor(camera),
      ImageSizeCameraThread() {}

HorizontalCalibrationCameraThread::~HorizontalCalibrationCameraThread() {}

wxThread::ExitCode HorizontalCalibrationCameraThread::Entry() {

    wxCommandEvent startCalibrationEvent(c_CALIBRATION_EVENT,
                                         CALIBRATION_CAMERA_START);
    wxPostEvent(parent, startCalibrationEvent);

    try {

        direction == HorizontalDirection::HORIZONTAL_TOP
            ? UpdateStatusEvent::Submit(parent, SC::STATUS_HORIZONTAL_SELECTTOP)
            : UpdateStatusEvent::Submit(parent,
                                        SC::STATUS_HORIZONTAL_SELECTBOTTOM);

        while (!TestDestroy()) {
            cv::Mat frame;
            camera->getFrame(frame);

            if (frame.empty()) {
                throw std::runtime_error("Failed to capture frame");
            }

            cv::resize(frame, frame, pSize);

            if (isLineValid(topLine)) {

                cv::line(frame, topLine.p1, topLine.p2, cv::Scalar(0, 255, 255),
                         2);
            }

            if (isLineValid(bottomLine)) {
                cv::line(frame, bottomLine.p1, bottomLine.p2,
                         cv::Scalar(255, 0, 0), 2);
            }

            UpdatePreviewEvent::Submit(parent, frame);

            wxMilliSleep(100);
        }
    } catch (const std::exception &e) {
        ErrorEvent::Submit(parent, e.what());

        wxCommandEvent endCalibrationEvent(c_CALIBRATION_EVENT,
                                           CALIBRATION_CAMERA_ERROR);
        wxPostEvent(parent, endCalibrationEvent);

        return 0;
    }

    UpdatePreviewEvent::Submit(parent, CLEAR_PREVIEW);

    wxCommandEvent endCalibrationEvent(c_CALIBRATION_EVENT,
                                       CALIBRATION_CAMERA_END);
    wxPostEvent(parent, endCalibrationEvent);
    return 0;
}

ThreadID HorizontalCalibrationCameraThread::getID() const { return threadID; }

void BaseHorizontalCalibrationThread::updateTopLine(Line line) {
    std::unique_lock<std::mutex> lock(m_mutex);
    topLine = line;
}

void BaseHorizontalCalibrationThread::updateBottomLine(Line line) {
    std::unique_lock<std::mutex> lock(m_mutex);
    bottomLine = line;
}

void BaseHorizontalCalibrationThread::setPointAndExtend(cv::Point point) {
    Line line;
    line.setP1(point);

    auto point2 = cv::Point(point.x + 1, point.y);
    line.setP2(point2);

    auto extrapolated = line.Extrapolate(pSize.height, pSize.width);

    direction == HORIZONTAL_TOP ? updateTopLine(extrapolated)
                                : updateBottomLine(extrapolated);
}

void BaseHorizontalCalibrationThread::setDirection(
    HorizontalDirection direction) {
    this->direction = direction;
}

HorizontalDirection BaseHorizontalCalibrationThread::getDirection() {
    return direction;
}

bool BaseHorizontalCalibrationThread::isLineValid(Line &line) {
    if (line.p1.x == 0 && line.p1.y == 0) {
        return false;
    }

    if (line.p2.x == 0 && line.p2.y == 0) {
        return false;
    }

    return true;
}

void BaseHorizontalCalibrationThread::setTopLine(Line line) {
    updateTopLine(line);
}

Line BaseHorizontalCalibrationThread::getTopLine() {
    std::unique_lock<std::mutex> lock(m_mutex);
    return topLine;
}

void BaseHorizontalCalibrationThread::setBottomLine(Line line) {
    updateBottomLine(line);
}

Line BaseHorizontalCalibrationThread::getBottomLine() {
    std::unique_lock<std::mutex> lock(m_mutex);
    return bottomLine;
}

// line size is in preview size
// need to convert to original size (image size)
Line HorizontalCalibrationCameraThread::getRealTopLine() {
    std::unique_lock<std::mutex> lock(m_mutex);

    Line rl = this->topLine.Scale(pSize, imageSize);
    return rl;
}

Line HorizontalCalibrationCameraThread::getRealBottomLine() {
    std::unique_lock<std::mutex> lock(m_mutex);

    Line ll = this->bottomLine.Scale(pSize, imageSize);
    return ll;
}
