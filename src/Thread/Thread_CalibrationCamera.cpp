#include "Algorithm/ransac_line/RansacLine.hpp"
#include "Event/Event_Calibration.hpp"
#include "Event/Event_Error.hpp"
#include "Event/Event_UpdatePreview.hpp"
#include "Event/Event_UpdateStatus.hpp"
#include "Model/CalibrationData.hpp"
#include "Thread/Thread_Base.hpp"
#include "UI/Layout/StatusPanel.hpp"
#include "Utils/Camera/CameraBase.hpp"
#include "Utils/Config/AppConfig.hpp"
#include <Thread/Thread_CalibrationCamera.hpp>
#include <opencv2/imgproc.hpp>
#include <wx/utils.h>

BaseCalibrationThread::BaseCalibrationThread(wxEvtHandler *parent, DataPtr data)
    : BaseThread(parent, data), PreviewableThread() {

    AppConfig c;
    auto RansacConfig = c.GetRansacConfig();
    int minPoints = RansacConfig.minPoints;
    int maxIterations = RansacConfig.maxIterations;
    double threshold = RansacConfig.threshold;
    ransac = RansacLine(maxIterations, minPoints, threshold);
}

BaseCalibrationThread::~BaseCalibrationThread() {}

CalibrationCameraThread::CalibrationCameraThread(wxEvtHandler *parent,
                                                 CameraPtr &camera)
    : BaseCalibrationThread(parent, nullptr), CameraAccessor(camera),
      ImageSizeCameraThread() {}

CalibrationCameraThread::~CalibrationCameraThread() {}

wxThread::ExitCode CalibrationCameraThread::Entry() {

    wxCommandEvent startCalibrationEvent(c_CALIBRATION_EVENT,
                                         CALIBRATION_CAMERA_START);
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
                Line yellowLine =
                    ransac.run(mask_yellow).Extrapolate(mask_yellow);
                if (!yellowLine.isNull()) {
                    updateRightLine(yellowLine);
                    cv::line(frame, yellowLine.p1, yellowLine.p2,
                             cv::Scalar(0, 255, 255), 2);
                }

                cv::Mat mask_blue = hsvFilter.blueMask(combined);
                Line blueLine = ransac.run(mask_blue).Extrapolate(mask_blue);
                if (!blueLine.isNull()) {
                    updateLeftLine(blueLine);
                    cv::line(frame, blueLine.p1, blueLine.p2,
                             cv::Scalar(255, 0, 0), 2);
                }

                if (yellowLine.isNull() && blueLine.isNull()) {
                    wxCommandEvent lineOKEvent(c_CALIBRATION_EVENT,
                                               CALIBRATION_LINE_FOUND);
                    wxPostEvent(parent, lineOKEvent);
                } else {
                    wxCommandEvent lineNotOKEvent(c_CALIBRATION_EVENT,
                                                  CALIBRATION_LINE_NOT_FOUND);
                    wxPostEvent(parent, lineNotOKEvent);
                }
            }

            if (point != cv::Point(0, 0)) {
                cv::circle(frame, point, 5, cv::Scalar(0, 0, 255), -1);
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

void BaseCalibrationThread::setPoint(cv::Point point) {
    std::unique_lock<std::mutex> lock(m_mutex);
    this->point = point;
    bfs.setStart(point);
}

void BaseCalibrationThread::clearPoint() {
    std::unique_lock<std::mutex> lock(m_mutex);
    this->point = cv::Point(-1, -1);
    bfs.setStart(point);
}

void BaseCalibrationThread::updateRightLine(Line line) {
    std::unique_lock<std::mutex> lock(m_mutex);
    rightLine = line;
}

void BaseCalibrationThread::updateLeftLine(Line line) {
    std::unique_lock<std::mutex> lock(m_mutex);
    leftLine = line;
}

bool BaseCalibrationThread::isBothLineValid() {
    std::unique_lock<std::mutex> lock(m_mutex);
    if (leftLine.isNull() || rightLine.isNull()) {
        return false;
    }

    return true;
    // return !leftLine.isNull() && !rightLine.isNull();
}

ThreadID CalibrationCameraThread::getID() const { return threadID; }

CalibrationData CalibrationCameraThread::getCalibrationData() {
    return CalibrationData(getRealLeftLine(), getRealRightLine());
}

Line CalibrationCameraThread::getRealRightLine() {
    std::unique_lock<std::mutex> lock(m_mutex);
    auto rl = rightLine.Scale(pSize, imageSize);
    return rl;
}

Line CalibrationCameraThread::getRealLeftLine() {
    std::unique_lock<std::mutex> lock(m_mutex);
    auto ll = leftLine.Scale(pSize, imageSize);
    return ll;
}