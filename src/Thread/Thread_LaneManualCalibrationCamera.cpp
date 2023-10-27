#include <Event/Event.hpp>
#include <Thread/Thread_LaneManualCalibrationCamera.hpp>
#include <UI/Layout/StatusPanel.hpp>

/**
 * @brief Construct a new Base Lane Manual Calibration Thread:: Base Lane Manual
 * Calibration Thread object
 *
 * @param parent Pointer to the View
 * @param data Pointer to the SessionData
 */
BaseLaneManualCalibrationThread::BaseLaneManualCalibrationThread(
    wxEvtHandler *parent, DataPtr data)
    : BaseThread(parent, data), PreviewableThread() {}

/**
 * @brief Destroy the Base Lane Manual Calibration Thread:: Base Lane Manual
 * Calibration Thread object
 *
 */
BaseLaneManualCalibrationThread::~BaseLaneManualCalibrationThread() {}

/**
 * @brief return the CalibrationData
 *
 * @return CalibrationData
 */
CalibrationData ManualCalibrationCameraThread::getCalibrationData() {
    return CalibrationData(getRealLeftLine(), getRealRightLine());
}

/**
 * @brief Construct a new Manual Calibration Camera Thread:: Manual Calibration
 * Camera Thread object
 *
 * @param parent Pointer to the View
 * @param camera Unique_ptr to the Camera
 */
ManualCalibrationCameraThread::ManualCalibrationCameraThread(
    wxEvtHandler *parent, CameraPtr &camera)
    : BaseLaneManualCalibrationThread(parent, nullptr), CameraAccessor(camera),
      ImageSizeCameraThread() {}

/**
 * @brief Destroy the Manual Calibration Camera Thread:: Manual Calibration
 * Camera Thread object
 *
 */
ManualCalibrationCameraThread::~ManualCalibrationCameraThread() {}

/**
 * @brief Entry point of the Thread
 * @details Send the start event to the View. Then capture the frame from the
 * camera and send it to the View. Perform the manual calibration. If an error
 * occurs, send the error event to the View. Finally send the end event to the
 * View.
 *
 * @return ExitCode
 */
wxThread::ExitCode ManualCalibrationCameraThread::Entry() {

    wxCommandEvent startCalibrationEvent(c_CALIBRATION_EVENT,
                                         CALIBRATION_CAMERA_START);
    wxPostEvent(parent, startCalibrationEvent);

    try {

        direction == ManualDirection::MANUAL_LEFT
            ? UpdateStatusEvent::Submit(parent, SC::STATUS_MANUAL_SELECTLEFT)
            : UpdateStatusEvent::Submit(parent, SC::STATUS_MANUAL_SELECTRIGHT);

        while (!TestDestroy()) {
            cv::Mat frame;
            camera->getFrame(frame);

            if (frame.empty()) {
                throw std::runtime_error("Failed to capture frame");
            }

            cv::resize(frame, frame, pSize);

            if (isLineValid(rightLine)) {

                cv::line(frame, rightLine.p1, rightLine.p2,
                         cv::Scalar(0, 255, 255), 2);
            }

            if (isLineValid(leftLine)) {
                cv::line(frame, leftLine.p1, leftLine.p2, cv::Scalar(255, 0, 0),
                         2);
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
 * @brief Get the Thread ID
 *
 * @return ThreadID
 */
ThreadID ManualCalibrationCameraThread::getID() const { return threadID; }

/**
 * @brief Get the selected right Line
 *
 * @param line Line
 */
void BaseLaneManualCalibrationThread::updateRightLine(Line line) {
    std::unique_lock<std::mutex> lock(m_mutex);
    rightLine = line;
}

/**
 * @brief Get the selected left Line
 *
 * @param line Line
 */
void BaseLaneManualCalibrationThread::updateLeftLine(Line line) {
    std::unique_lock<std::mutex> lock(m_mutex);
    leftLine = line;
}

/**
 * @brief Set the first point of the Line
 *
 * @param point Point
 */
void BaseLaneManualCalibrationThread::setPoint1(cv::Point point) {
    Line line;
    line.setP1(point);

    direction == MANUAL_LEFT ? updateLeftLine(line) : updateRightLine(line);
}

/**
 * @brief Set the second point of the Line
 *
 * @param point Point
 */
void BaseLaneManualCalibrationThread::setPoint2(cv::Point point) {
    Line line = direction == MANUAL_LEFT ? leftLine : rightLine;
    line.setP2(point);

    direction == MANUAL_LEFT ? updateLeftLine(line) : updateRightLine(line);
}

/**
 * @brief Set the second point of the Line and extend it
 *
 * @param point Point
 */
void BaseLaneManualCalibrationThread::setPoint2AndExtend(cv::Point point) {
    Line line = direction == MANUAL_LEFT ? leftLine : rightLine;
    line.setP2(point);

    direction == MANUAL_LEFT
        ? updateLeftLine(line.Extrapolate(pSize.height, pSize.width))
        : updateRightLine(line.Extrapolate(pSize.height, pSize.width));
}

/**
 * @brief Set the direction
 *
 * @param direction
 */
void BaseLaneManualCalibrationThread::setDirection(ManualDirection direction) {
    this->direction = direction;
}

/**
 * @brief Get the direction
 *
 * @return ManualDirection
 */
ManualDirection BaseLaneManualCalibrationThread::getDirection() {
    return direction;
}

/**
 * @brief Check if the Line is valid
 *
 * @param line
 * @return true
 * @return false
 */
bool BaseLaneManualCalibrationThread::isLineValid(Line &line) {
    if (line.p1.x == 0 && line.p1.y == 0) {
        return false;
    }

    if (line.p2.x == 0 && line.p2.y == 0) {
        return false;
    }

    return true;
}

/**
 * @brief Set the Calibration Data
 *
 * @param line  Line
 */
void BaseLaneManualCalibrationThread::setRightLine(Line line) {
    updateRightLine(line);
}

/**
 * @brief Get the Calibration Data
 *
 * @return Line
 */
Line BaseLaneManualCalibrationThread::getRightLine() {
    std::unique_lock<std::mutex> lock(m_mutex);
    return rightLine;
}

/**
 * @brief Set the Calibration Data
 *
 * @param line  Line
 */
void BaseLaneManualCalibrationThread::setLeftLine(Line line) {
    updateLeftLine(line);
}

/**
 * @brief Get the Calibration Data
 *
 * @return Line
 */
Line BaseLaneManualCalibrationThread::getLeftLine() {
    std::unique_lock<std::mutex> lock(m_mutex);
    return leftLine;
}

// line size is in preview size
// need to convert to original size (image size)

/**
 * @brief Get the real right Line
 * @note The Line is scaled to the original image size
 *
 * @return Line
 */
Line ManualCalibrationCameraThread::getRealRightLine() {
    std::unique_lock<std::mutex> lock(m_mutex);

    Line rl = this->rightLine.Scale(pSize, imageSize);
    return rl;
}

/**
 * @brief Get the real left Line
 * @note The Line is scaled to the original image size
 *
 * @return Line
 */
Line ManualCalibrationCameraThread::getRealLeftLine() {
    std::unique_lock<std::mutex> lock(m_mutex);

    Line ll = this->leftLine.Scale(pSize, imageSize);
    return ll;
}
