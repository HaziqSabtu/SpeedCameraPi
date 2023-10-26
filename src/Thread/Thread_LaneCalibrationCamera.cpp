#include <Event/Event.hpp>
#include <Thread/Thread_LaneCalibrationCamera.hpp>
#include <UI/Layout/StatusPanel.hpp>

/**
 * @brief Construct a new Base Lane Calibration Thread:: Base Lane Calibration
 * Thread object
 *
 * @param parent Pointer to the View
 * @param data Pointer to the SessionData
 * @param hsvFilter Pointer to the HSVFilter object
 * @param bfs Pointer to the BFS object
 * @param ransac Pointer to the RansacLine object
 */
BaseLaneCalibrationThread::BaseLaneCalibrationThread(wxEvtHandler *parent,
                                                     DataPtr data,
                                                     HSVFilterPtr hsvFilter,
                                                     BFSPtr bfs,
                                                     RansacLinePtr ransac)
    : BaseThread(parent, data), hsvFilter(hsvFilter), bfs(bfs), ransac(ransac),
      PreviewableThread() {}

/**
 * @brief Destroy the Base Lane Calibration Thread:: Base Lane Calibration
 * Thread object
 *
 */
BaseLaneCalibrationThread::~BaseLaneCalibrationThread() {}

/**
 * @brief Construct a new Lane Calibration Camera Thread:: Lane Calibration
 * Camera Thread object
 *
 * @param parent Pointer to the View
 * @param data Pointer to the SessionData
 * @param camera Unique_ptr to the Camera
 * @param hsvFilter Pointer to the HSVFilter object
 * @param bfs Pointer to the BFS object
 * @param ransac Pointer to the RansacLine object
 */
LaneCalibrationCameraThread::LaneCalibrationCameraThread(
    wxEvtHandler *parent, DataPtr data, CameraPtr &camera,
    HSVFilterPtr hsvFilter, BFSPtr bfs, RansacLinePtr ransac)
    : BaseLaneCalibrationThread(parent, data, hsvFilter, bfs, ransac),
      CameraAccessor(camera), ImageSizeCameraThread() {}

/**
 * @brief Destroy the Lane Calibration Camera Thread:: Lane Calibration Camera
 * Thread object
 *
 */
LaneCalibrationCameraThread::~LaneCalibrationCameraThread() {}

/**
 * @brief Entry point of the Thread
 * @details Send the start event to the View. Then capture the frame from the
 * camera and send it to the View. Perform the lane calibration. If an error
 * occurs, send the error event to the View. Finally send the end event to the
 * View.
 *
 * @return ExitCode
 */
wxThread::ExitCode LaneCalibrationCameraThread::Entry() {

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

            cv::Mat hsvFrame = hsvFilter->toHSV(frame);
            cv::Mat filteredFrame = bfs->run(hsvFrame);

            auto boundingBox = cv::boundingRect(filteredFrame);
            cv::rectangle(filteredFrame, boundingBox, cv::Scalar(0, 255, 0), 2);

            cv::Mat combined =
                cv::Mat::zeros(frame.rows, frame.cols, frame.type());
            if (!boundingBox.empty()) {
                cv::Mat crop = hsvFrame(boundingBox);

                cv::Mat mask = cv::Mat::zeros(frame.rows, frame.cols, CV_8UC1);
                cv::rectangle(mask, boundingBox, cv::Scalar(255, 255, 255), -1);
                cv::bitwise_and(hsvFrame, hsvFrame, combined, mask);

                cv::Mat mask_yellow = hsvFilter->yellowMask(combined);
                Line yellowLine =
                    ransac->run(mask_yellow).Extrapolate(mask_yellow);
                if (!yellowLine.isNull()) {
                    updateRightLine(yellowLine);
                    cv::line(frame, yellowLine.p1, yellowLine.p2,
                             cv::Scalar(0, 255, 255), 2);
                }

                cv::Mat mask_blue = hsvFilter->blueMask(combined);
                Line blueLine = ransac->run(mask_blue).Extrapolate(mask_blue);
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

/**
 * @brief Set the point where the mat is located
 *
 * @param point
 */
void BaseLaneCalibrationThread::setPoint(cv::Point point) {
    std::unique_lock<std::mutex> lock(m_mutex);
    this->point = point;
    bfs->setStart(point);
}

/**
 * @brief Clear the point
 *
 */
void BaseLaneCalibrationThread::clearPoint() {
    std::unique_lock<std::mutex> lock(m_mutex);
    this->point = cv::Point(-1, -1);
    bfs->setStart(point);
}

/**
 * @brief update the right Line
 *
 * @param line Line
 */
void BaseLaneCalibrationThread::updateRightLine(Line line) {
    std::unique_lock<std::mutex> lock(m_mutex);
    rightLine = line;
}

/**
 * @brief update the left Line
 *
 * @param line Line
 */
void BaseLaneCalibrationThread::updateLeftLine(Line line) {
    std::unique_lock<std::mutex> lock(m_mutex);
    leftLine = line;
}

/**
 * @brief Check if both Line are valid
 *
 * @return true if  both Line are valid
 * @return false if one or both Line are not valid
 */
bool BaseLaneCalibrationThread::isBothLineValid() {
    std::unique_lock<std::mutex> lock(m_mutex);
    if (leftLine.isNull() || rightLine.isNull()) {
        return false;
    }

    return true;
}

/**
 * @brief Get the ID of the Thread
 *
 * @return ThreadID
 */
ThreadID LaneCalibrationCameraThread::getID() const { return threadID; }

/**
 * @brief Get the Calibration Data
 *
 * @return CalibrationData
 */
CalibrationData LaneCalibrationCameraThread::getCalibrationData() {
    return CalibrationData(getRealLeftLine(), getRealRightLine());
}

/**
 * @brief Get the real right Line
 * @note The Line is scaled to the original image size
 *
 * @return Line
 */
Line LaneCalibrationCameraThread::getRealRightLine() {
    std::unique_lock<std::mutex> lock(m_mutex);
    auto rl = rightLine.Scale(pSize, imageSize);
    return rl;
}

/**
 * @brief Get the real left Line
 * @note The Line is scaled to the original image size
 *
 * @return Line
 */
Line LaneCalibrationCameraThread::getRealLeftLine() {
    std::unique_lock<std::mutex> lock(m_mutex);
    auto ll = leftLine.Scale(pSize, imageSize);
    return ll;
}