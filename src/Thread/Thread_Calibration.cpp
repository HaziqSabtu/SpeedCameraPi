#include "Algorithm/ransac_line/RansacLine.hpp"
#include "Event/Event_Calibration.hpp"
#include "Event/Event_Error.hpp"
#include "Event/Event_UpdatePreview.hpp"
#include "Event/Event_UpdateStatus.hpp"
#include "Model/CalibrationData.hpp"
#include "UI/Layout/StatusPanel.hpp"
#include "Utils/Config/AppConfig.hpp"
#include <Thread/Thread_Calibration.hpp>
#include <opencv2/imgproc.hpp>
#include <wx/utils.h>

// TODO: Fix Status
CalibrationThread::CalibrationThread(wxEvtHandler *parent,
                                     std::unique_ptr<CameraBase> &camera)
    : wxThread(wxTHREAD_JOINABLE), camera(std::move(camera)) {
    this->parent = parent;

    auto config = AppConfig();
    auto previewConfig = config.GetPreviewConfig();
    int pWidth = previewConfig.width;
    int pHeight = previewConfig.height;
    pSize = cv::Size(pWidth, pHeight);

    AppConfig c;
    auto RansacConfig = c.GetRansacConfig();
    int minPoints = RansacConfig.minPoints;
    int maxIterations = RansacConfig.maxIterations;
    double threshold = RansacConfig.threshold;
    ransac = RansacLine(maxIterations, minPoints, threshold);
}

CalibrationThread::~CalibrationThread() {}

wxThread::ExitCode CalibrationThread::Entry() {

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

            cv::Mat hsvFrame = hsvFilter.toHSV(frame);
            cv::Mat filteredFrame = bfs.run(hsvFrame);

            auto boundingBox = cv::boundingRect(filteredFrame);
            cv::rectangle(filteredFrame, boundingBox, cv::Scalar(0, 255, 0), 2);

            cv::Mat combined =
                cv::Mat::zeros(frame.rows, frame.cols, frame.type());
            if (!boundingBox.empty()) {
                cv::Mat crop = hsvFrame(boundingBox);

                cv::Mat mask = cv::Mat::zeros(frame.rows, frame.cols, CV_8UC1);
                cv::rectangle(mask, boundingBox, cv::Scalar(255, 255, 255), -1);
                cv::bitwise_and(hsvFrame, hsvFrame, combined, mask);

                cv::Mat mask_yellow = hsvFilter.yellowMask(combined);
                Detection::Line yellowLine =
                    ransac.run(mask_yellow).Extrapolate(mask_yellow);
                if (!yellowLine.isNull()) {
                    updateYellowLine(yellowLine);
                    cv::line(frame, yellowLine.p1, yellowLine.p2,
                             cv::Scalar(0, 255, 255), 2);
                }

                cv::Mat mask_blue = hsvFilter.blueMask(combined);
                Detection::Line blueLine =
                    ransac.run(mask_blue).Extrapolate(mask_blue);
                if (!blueLine.isNull()) {
                    updateBlueLine(blueLine);
                    cv::line(frame, blueLine.p1, blueLine.p2,
                             cv::Scalar(255, 0, 0), 2);
                }

                UpdateStatusEvent::Submit(
                    parent, StatusCollection::STATUS_LINE_DETECTED);
            } else {
                UpdateStatusEvent::Submit(
                    parent, StatusCollection::STATUS_LINE_NOT_DETECTED);
            }

            if (point != cv::Point(0, 0)) {
                cv::circle(frame, point, 5, cv::Scalar(0, 0, 255), -1);
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

std::unique_ptr<CameraBase> CalibrationThread::getCamera() {
    return std::move(camera);
}

void CalibrationThread::setPoint(cv::Point point) {
    std::unique_lock<std::mutex> lock(m_mutex);
    this->point = point;
    bfs.setStart(point);
}

ThreadID CalibrationThread::getID() const { return threadID; }

void CalibrationThread::updateYellowLine(Detection::Line line) {
    std::unique_lock<std::mutex> lock(m_mutex);
    yellowLine = line;
}

void CalibrationThread::updateBlueLine(Detection::Line line) {
    std::unique_lock<std::mutex> lock(m_mutex);
    blueLine = line;
}

CalibData CalibrationThread::getCalibData() {
    std::unique_lock<std::mutex> lock(m_mutex);
    return CalibData(yellowLine, blueLine);
}