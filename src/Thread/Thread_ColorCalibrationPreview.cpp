#include <Thread/Thread_ColorCalibrationPreview.hpp>

#include <Event/Event.hpp>

#include <Utils/CommonUtils.hpp>

/**
 * @brief Construct a new Color Calibration Preview Thread:: Color Calibration
 * Preview Thread object
 *
 * @param parent Pointer to the View
 * @param camera Unique_ptr to the Camera
 * @param blueRange Pair of Scalar for the blue range
 * @param yellowRange Pair of Scalar for the yellow range
 */
ColorCalibrationPreviewThread::ColorCalibrationPreviewThread(
    wxEvtHandler *parent, CameraPtr &camera, const ColorRange &blueRange,
    const ColorRange &yellowRange)
    : BaseThread(parent, nullptr), CameraAccessor(camera), PreviewableThread(),
      blueRange(blueRange), yellowRange(yellowRange) {}

/**
 * @brief Destroy the Color Calibration Preview Thread:: Color Calibration
 * Preview Thread object
 *
 */
ColorCalibrationPreviewThread::~ColorCalibrationPreviewThread() {}

/**
 * @brief Entry point of the Thread
 * @details Send the start event to the View. Then capture the frame from the
 * camera and send it to the View. If the color calibration is completed, show
 * the calibrated color on the preview image.
 *
 * @return ExitCode
 */
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
    return Utils::isRangeCalibrated(blueRange) &&
           Utils::isRangeCalibrated(yellowRange);
}