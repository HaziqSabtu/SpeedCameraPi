
#include "Event/Event_Error.hpp"
#include "Event/Event_UpdateState.hpp"
#include "Event/Event_UpdateStatus.hpp"
#include "Model/ExtraModel.hpp"
#include "Thread/Thread_Base.hpp"
#include "Utils/Camera/CameraBase.hpp"
#include <Thread/Thread_ColorCalibrationPreview.hpp>
#include <memory>
#include <opencv2/core/types.hpp>
#include <wx/utils.h>

ColorCalibrationPreviewThread::ColorCalibrationPreviewThread(
    wxEvtHandler *parent, CameraPtr &camera, const ColorRange &blueRange,
    const ColorRange &yellowRange)
    : BaseThread(parent, nullptr), CameraAccessor(camera), PreviewableThread(),
      blueRange(blueRange), yellowRange(yellowRange) {}

ColorCalibrationPreviewThread::~ColorCalibrationPreviewThread() {}

wxThread::ExitCode ColorCalibrationPreviewThread::Entry() {
    wxCommandEvent startCaptureEvent(c_PREVIEW_CAMERA_EVENT, PREVIEW_START);
    wxPostEvent(parent, startCaptureEvent);

    if (!isCalibrationComplete()) {
        UpdateStatusEvent::Submit(parent, "Color calibration is NOT completed");
    }

    try {
        while (!TestDestroy()) {
            cv::Mat frame;
            camera->getFrame(frame);

            if (frame.empty()) {
                std::cout << "Failed to capture frame" << std::endl;
                continue;
            }

            cv::resize(frame, frame, pSize);

            if (!isCalibrationComplete()) {
                UpdatePreviewEvent::Submit(parent, frame);
                wxMilliSleep(200);
                continue;
            }

            auto blue_lower = blueRange.first;
            auto blue_upper = blueRange.second;

            auto yellow_lower = yellowRange.first;
            auto yellow_upper = yellowRange.second;

            cv::Mat hsvFrame;
            cv::cvtColor(frame, hsvFrame, cv::COLOR_BGR2HSV);

            cv::Mat blueMask, yellowMask;
            cv::inRange(hsvFrame, blue_lower, blue_upper, blueMask);
            cv::inRange(hsvFrame, yellow_lower, yellow_upper, yellowMask);

            cv::Mat gray;
            cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);
            cv::Mat gray8uc3;
            cv::cvtColor(gray, gray8uc3, cv::COLOR_GRAY2BGR);

            for (int i = 0; i < frame.rows; i++) {
                for (int j = 0; j < frame.cols; j++) {
                    if (blueMask.at<uchar>(i, j) == 255) {
                        gray8uc3.at<cv::Vec3b>(i, j) = cv::Vec3b(255, 0, 0);
                    } else if (yellowMask.at<uchar>(i, j) == 255) {
                        gray8uc3.at<cv::Vec3b>(i, j) = cv::Vec3b(0, 255, 255);
                    }
                }
            }
            UpdatePreviewEvent::Submit(parent, gray8uc3);
            wxMilliSleep(100);
        }
    } catch (const std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }

    UpdatePreviewEvent clearPreviewEvent(c_UPDATE_PREVIEW_EVENT, CLEAR_PREVIEW);
    wxPostEvent(parent, clearPreviewEvent);

    wxCommandEvent endCaptureEvent(c_PREVIEW_CAMERA_EVENT, PREVIEW_END);
    wxPostEvent(parent, endCaptureEvent);

    return 0;
}

ThreadID ColorCalibrationPreviewThread::getID() const { return id; }

bool ColorCalibrationPreviewThread::isCalibrationComplete() {
    // return ccExtraModel->isBlueCalibrated() &&
    //        ccExtraModel->isYellowCalibrated();
    return true;
}