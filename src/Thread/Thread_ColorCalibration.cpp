#include <Thread/Thread_ColorCalibration.hpp>

#include <UI/Layout/StatusPanel.hpp>

#include <Event/Event.hpp>

/**
 * @brief Construct a new Color Calibration Thread:: Color Calibration Thread
 * object
 *
 * @param parent Pointer to the View
 * @param data Pointer to the SessionData
 * @param camera Unique_ptr to the Camera
 * @param hsvFilter Pointer to the HSVFilter object
 * @param bfs Pointer to the BFS object
 */
ColorCalibrationThread::ColorCalibrationThread(wxEvtHandler *parent,
                                               DataPtr data, CameraPtr &camera,
                                               HSVFilterPtr hsvFilter,
                                               BFSPtr bfs)
    : BaseThread(parent, data), PreviewableThread(), CameraAccessor(camera),
      hsvFilter(hsvFilter), bfs(bfs) {}

/**
 * @brief Destroy the Color Calibration Thread:: Color Calibration Thread object
 *
 */
ColorCalibrationThread::~ColorCalibrationThread() {}

/**
 * @brief Entry point of the Thread
 * @details Send the start event to the View. Then capture the frame from the
 * camera and send it to the View. Perform the color calibration. If an error
 * occurs, send the error event to the View. Finally send the end event to the
 * View.
 *
 * @return ExitCode
 */
wxThread::ExitCode ColorCalibrationThread::Entry() {

    wxCommandEvent startCalibrationEvent(c_CALIBRATION_EVENT,
                                         CALIBRATION_CAMERA_START);
    wxPostEvent(parent, startCalibrationEvent);

    try {
        unsigned char hmin = 0, hmax = 0;
        unsigned char smin = 0, smax = 0;
        unsigned char vmin = 0, vmax = 0;

        cv::Mat frame;
        camera->getFrame(frame);

        if (frame.empty()) {
            throw std::runtime_error("Failed to capture frame");
        }

        cv::resize(frame, frame, pSize);

        while (!TestDestroy()) {
            {
                if (point == cv::Point(-1, -1)) {
                    wxMilliSleep(300);
                    UpdatePreviewEvent::Submit(parent, frame);
                    continue;
                }

                auto p = getPoint();
                auto pType = getColorCalibrationType();

                if (processedPoint != point) {
                    hmin = 0;
                    hmax = 0;
                    smin = 0;
                    smax = 0;
                    vmin = 0;
                    vmax = 0;
                    processedPoint = point;
                }

                cv::Mat hsvFrame = hsvFilter->toHSV(frame);
                cv::Mat filteredFrame = bfs->run(hsvFrame);

                cv::Mat grayImage;
                cv::cvtColor(frame, grayImage, cv::COLOR_BGR2GRAY);

                // crop image
                auto boundingBox = cv::boundingRect(filteredFrame);
                cv::Mat hsvCrop = hsvFrame(boundingBox);
                cv::Mat maskCrop = filteredFrame(boundingBox);

                if (hmin == 0 && hmax == 0 && smin == 0 && smax == 0 &&
                    vmin == 0 && vmax == 0) {
                    cv::Scalar now = hsvFrame.at<cv::Vec3b>(p);
                    hmin = now[0];
                    hmax = now[0];
                    smin = now[1];
                    smax = now[1];
                    vmin = now[2];
                    vmax = now[2];
                }

                if (!boundingBox.empty()) {

                    for (int y = 0; y < maskCrop.rows; y++) {
                        for (int x = 0; x < maskCrop.cols; x++) {
                            uchar alpha = maskCrop.at<uchar>(y, x);

                            if (alpha == 0) {
                                continue;
                            }

                            if (hsvCrop.at<cv::Vec3b>(y, x)[0] < hmin) {
                                hmin = hsvCrop.at<cv::Vec3b>(y, x)[0];
                            }

                            if (hsvCrop.at<cv::Vec3b>(y, x)[0] > hmax) {
                                hmax = hsvCrop.at<cv::Vec3b>(y, x)[0];
                            }

                            if (hsvCrop.at<cv::Vec3b>(y, x)[1] < smin) {
                                smin = hsvCrop.at<cv::Vec3b>(y, x)[1];
                            }

                            if (hsvCrop.at<cv::Vec3b>(y, x)[1] > smax) {
                                smax = hsvCrop.at<cv::Vec3b>(y, x)[1];
                            }

                            if (hsvCrop.at<cv::Vec3b>(y, x)[2] < vmin) {
                                vmin = hsvCrop.at<cv::Vec3b>(y, x)[2];
                            }

                            if (hsvCrop.at<cv::Vec3b>(y, x)[2] > vmax) {
                                vmax = hsvCrop.at<cv::Vec3b>(y, x)[2];
                            }
                        }
                    }
                }

                auto color = pType == COLOR_CALIBRATION_BLUE ? blue : yellow;
                cv::Mat combined = cv::Mat::zeros(frame.size(), CV_8UC4);
                for (int y = 0; y < frame.rows; y++) {
                    for (int x = 0; x < frame.cols; x++) {
                        uchar alpha = filteredFrame.at<uchar>(y, x);
                        if (alpha == 255) {
                            combined.at<cv::Vec4b>(y, x) = color;
                        } else if (alpha == 0) {
                            combined.at<cv::Vec4b>(y, x) = {
                                grayImage.at<uchar>(y, x),
                                grayImage.at<uchar>(y, x),
                                grayImage.at<uchar>(y, x), 255};
                        }
                    }
                }

                cv::cvtColor(combined, combined, cv::COLOR_BGRA2BGR);

                cv::circle(combined, p, 5, cv::Scalar(0, 0, 255), -1);

                cv::Scalar lower = cv::Scalar(hmin, smin, vmin);
                cv::Scalar upper = cv::Scalar(hmax, smax, vmax);

                auto val = std::make_pair(upper, lower);

                pType == COLOR_CALIBRATION_BLUE ? updateBlueRange(val)
                                                : updateYellowRange(val);

                UpdatePreviewEvent::Submit(parent, combined);

                std::string range = "H: " + std::to_string(hmin) + " - " +
                                    std::to_string(hmax) +
                                    " S: " + std::to_string(smin) + " - " +
                                    std::to_string(smax) +
                                    " V: " + std::to_string(vmin) + " - " +
                                    std::to_string(vmax);
                UpdateStatusEvent::Submit(parent, range);

                if (updateStateSwitch) {
                    updateStateSwitch = false;

                    wxCommandEvent updateState(c_REQUEST_UPDATE_STATE_EVENT,
                                               REQUEST_UPDATE_STATE);
                    wxPostEvent(parent, updateState);
                }
                wxMilliSleep(100);
            }
        }
    } catch (const std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }

    UpdatePreviewEvent::Submit(parent, CLEAR_PREVIEW);

    wxCommandEvent endCalibrationEvent(c_CALIBRATION_EVENT,
                                       CALIBRATION_CAMERA_END);
    wxPostEvent(parent, endCalibrationEvent);
    return 0;
}

void ColorCalibrationThread::setPoint(cv::Point point) {
    std::unique_lock<std::recursive_mutex> lock(m_mutex);
    this->point = point;
    bfs->setStart(point);
    updateStateSwitch = true;
}

cv::Point ColorCalibrationThread::getPoint() {
    std::unique_lock<std::recursive_mutex> lock(m_mutex);
    return point;
}

ThreadID ColorCalibrationThread::getID() const { return threadID; }

std::pair<cv::Scalar, cv::Scalar> ColorCalibrationThread::getBlueRange() {
    std::unique_lock<std::recursive_mutex> lock(m_mutex);
    return blueRange;
}

std::pair<cv::Scalar, cv::Scalar> ColorCalibrationThread::getYellowRange() {
    std::unique_lock<std::recursive_mutex> lock(m_mutex);
    return yellowRange;
}

cv::Point ColorCalibrationThread::grabPoint() {
    std::unique_lock<std::recursive_mutex> lock(m_mutex);
    cv::Point point = this->point;
    this->point = cv::Point(-1, -1);
    return point;
}

void ColorCalibrationThread::setColorCalibrationType(
    ColorCalibrationType type) {
    std::unique_lock<std::recursive_mutex> lock(m_mutex);
    this->point = cv::Point(-1, -1);
    this->type = type;
}

ColorCalibrationType ColorCalibrationThread::getColorCalibrationType() {
    std::unique_lock<std::recursive_mutex> lock(m_mutex);
    return type;
}

void ColorCalibrationThread::removeBlueRange() {
    std::unique_lock<std::recursive_mutex> lock(m_mutex);
    point = cv::Point(-1, -1);
    type = COLOR_CALIBRATION_BLUE;
    blueRange = std::make_pair(cv::Scalar(0, 0, 0), cv::Scalar(0, 0, 0));
}

// Problem: Synchronization not completed
// there is a posibility where
void ColorCalibrationThread::removeYellowRange() {
    std::unique_lock<std::recursive_mutex> lock(m_mutex);
    point = cv::Point(-1, -1);
    type = COLOR_CALIBRATION_YELLOW;
    yellowRange = std::make_pair(cv::Scalar(0, 0, 0), cv::Scalar(0, 0, 0));
}

void ColorCalibrationThread::updateBlueRange(
    std::pair<cv::Scalar, cv::Scalar> range) {
    std::unique_lock<std::recursive_mutex> lock(m_mutex);
    blueRange = range;
}

void ColorCalibrationThread::updateYellowRange(
    std::pair<cv::Scalar, cv::Scalar> range) {
    std::unique_lock<std::recursive_mutex> lock(m_mutex);
    yellowRange = range;
}

bool ColorCalibrationThread::isBlueRangeDefined() {
    std::unique_lock<std::recursive_mutex> lock(m_mutex);
    return blueRange.first != cv::Scalar(0, 0, 0) &&
           blueRange.second != cv::Scalar(0, 0, 0);
}

bool ColorCalibrationThread::isYellowRangeDefined() {
    std::unique_lock<std::recursive_mutex> lock(m_mutex);
    return yellowRange.first != cv::Scalar(0, 0, 0) &&
           yellowRange.second != cv::Scalar(0, 0, 0);
}