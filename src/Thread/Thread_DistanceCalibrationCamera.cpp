#include <Event/Event.hpp>
#include <Thread/Thread_DistanceCalibrationCamera.hpp>

/**
 * @brief Construct a new Base Distance Calibration Thread:: Base Distance
 * Calibration Thread object
 *
 * @param parent Pointer to the View
 * @param data Pointer to the SessionData
 */
BaseDistanceCalibrationThread::BaseDistanceCalibrationThread(
    wxEvtHandler *parent, DataPtr data)
    : BaseThread(parent, data), PreviewableThread() {}

/**
 * @brief Destroy the Base Distance Calibration Thread:: Base Distance
 * Calibration Thread object
 *
 */
BaseDistanceCalibrationThread::~BaseDistanceCalibrationThread() {}

/**
 * @brief return the CalibrationData
 *
 * @return CalibrationData
 */
CalibrationData DistanceCalibrationCameraThread::getCalibrationData() {
    return CalibrationData(getRealBottomLine(), getRealTopLine());
}

/**
 * @brief Construct a new Distance Calibration Camera Thread:: Distance
 * Calibration Camera Thread object
 *
 * @param parent Pointer to the View
 * @param camera Pointer to the Camera
 */
DistanceCalibrationCameraThread::DistanceCalibrationCameraThread(
    wxEvtHandler *parent, CameraPtr &camera)
    : BaseDistanceCalibrationThread(parent, nullptr), CameraAccessor(camera),
      ImageSizeCameraThread() {}

/**
 * @brief Destroy the Distance Calibration Camera Thread:: Distance Calibration
 * Camera Thread object
 *
 */
DistanceCalibrationCameraThread::~DistanceCalibrationCameraThread() {}

/**
 * @brief Entry point of the Thread
 * @details Send the start event to the View. Then capture the frame from the
 * camera and send it to the View. Perform the distance calibration. If an error
 * occurs, send the error event to the View. Finally send the end event to the
 * View.
 *
 * @return ExitCode
 */
wxThread::ExitCode DistanceCalibrationCameraThread::Entry() {

    wxCommandEvent startCalibrationEvent(c_CALIBRATION_EVENT,
                                         CALIBRATION_CAMERA_START);
    wxPostEvent(parent, startCalibrationEvent);

    try {

        direction == DistanceDirection::DISTANCE_TOP
            ? UpdateStatusEvent::Submit(parent, SC::STATUS_DISTANCE_SELECTTOP)
            : UpdateStatusEvent::Submit(parent,
                                        SC::STATUS_DISTANCE_SELECTBOTTOM);

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

/**
 * @brief Get the ThreadID
 *
 * @return ThreadID
 */
ThreadID DistanceCalibrationCameraThread::getID() const { return threadID; }

/**
 * @brief Update the top Line
 *
 * @param line
 */
void BaseDistanceCalibrationThread::updateTopLine(Line line) {
    std::unique_lock<std::mutex> lock(m_mutex);
    topLine = line;
}

/**
 * @brief Update the bottom Line
 *
 * @param line
 */
void BaseDistanceCalibrationThread::updateBottomLine(Line line) {
    std::unique_lock<std::mutex> lock(m_mutex);
    bottomLine = line;
}

/**
 * @brief Set the point and extend the Line
 *
 * @param point
 */
void BaseDistanceCalibrationThread::setPointAndExtend(cv::Point point) {
    Line line;
    line.setP1(point);

    auto point2 = cv::Point(point.x + 1, point.y);
    line.setP2(point2);

    auto extrapolated = line.Extrapolate(pSize.height, pSize.width);

    direction == DISTANCE_TOP ? updateTopLine(extrapolated)
                              : updateBottomLine(extrapolated);
}

/**
 * @brief Set the direction, either top or bottom
 *
 * @param direction
 */
void BaseDistanceCalibrationThread::setDirection(DistanceDirection direction) {
    this->direction = direction;
}

/**
 * @brief Get the direction
 *
 * @return DistanceDirection
 */
DistanceDirection BaseDistanceCalibrationThread::getDirection() {
    return direction;
}

/**
 * @brief Check if the Line is valid
 *
 * @param line
 * @return true
 * @return false
 */
bool BaseDistanceCalibrationThread::isLineValid(Line &line) {
    if (line.p1.x == 0 && line.p1.y == 0) {
        return false;
    }

    if (line.p2.x == 0 && line.p2.y == 0) {
        return false;
    }

    return true;
}

/**
 * @brief Set the top Line
 *
 * @param line
 */
void BaseDistanceCalibrationThread::setTopLine(Line line) {
    updateTopLine(line);
}

/**
 * @brief Get the top Line
 *
 * @return Line
 */
Line BaseDistanceCalibrationThread::getTopLine() {
    std::unique_lock<std::mutex> lock(m_mutex);
    return topLine;
}

/**
 * @brief Set the bottom Line
 *
 * @param line
 */
void BaseDistanceCalibrationThread::setBottomLine(Line line) {
    updateBottomLine(line);
}

/**
 * @brief Get the bottom Line
 *
 * @return Line
 */
Line BaseDistanceCalibrationThread::getBottomLine() {
    std::unique_lock<std::mutex> lock(m_mutex);
    return bottomLine;
}

// line size is in preview size
// need to convert to original size (image size)
/**
 * @brief Get the real top Line
 * @note The Line is scaled to the original image size
 *
 * @return Line
 */
Line DistanceCalibrationCameraThread::getRealTopLine() {
    std::unique_lock<std::mutex> lock(m_mutex);

    Line rl = this->topLine.Scale(pSize, imageSize);
    return rl;
}

/**
 * @brief Get the real bottom Line
 * @note The Line is scaled to the original image size
 *
 * @return Line
 */
Line DistanceCalibrationCameraThread::getRealBottomLine() {
    std::unique_lock<std::mutex> lock(m_mutex);

    Line ll = this->bottomLine.Scale(pSize, imageSize);
    return ll;
}
