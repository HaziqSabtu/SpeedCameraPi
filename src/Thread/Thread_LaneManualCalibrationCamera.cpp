#include <Event/Event.hpp>
#include <Thread/Thread_LaneManualCalibrationCamera.hpp>
#include <UI/Layout/StatusPanel.hpp>

BaseLaneManualCalibrationThread::BaseLaneManualCalibrationThread(
    wxEvtHandler *parent, DataPtr data)
    : BaseThread(parent, data), PreviewableThread() {}

BaseLaneManualCalibrationThread::~BaseLaneManualCalibrationThread() {}

CalibrationData ManualCalibrationCameraThread::getCalibrationData() {
    return CalibrationData(getRealLeftLine(), getRealRightLine());
}

ManualCalibrationCameraThread::ManualCalibrationCameraThread(
    wxEvtHandler *parent, CameraPtr &camera)
    : BaseLaneManualCalibrationThread(parent, nullptr), CameraAccessor(camera),
      ImageSizeCameraThread() {}

ManualCalibrationCameraThread::~ManualCalibrationCameraThread() {}

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

ThreadID ManualCalibrationCameraThread::getID() const { return threadID; }

void BaseLaneManualCalibrationThread::updateRightLine(Line line) {
    std::unique_lock<std::mutex> lock(m_mutex);
    rightLine = line;
}

void BaseLaneManualCalibrationThread::updateLeftLine(Line line) {
    std::unique_lock<std::mutex> lock(m_mutex);
    leftLine = line;
}

void BaseLaneManualCalibrationThread::setPoint1(cv::Point point) {
    Line line;
    line.setP1(point);

    direction == MANUAL_LEFT ? updateLeftLine(line) : updateRightLine(line);
}

void BaseLaneManualCalibrationThread::setPoint2(cv::Point point) {
    Line line = direction == MANUAL_LEFT ? leftLine : rightLine;
    line.setP2(point);

    direction == MANUAL_LEFT ? updateLeftLine(line) : updateRightLine(line);
}

void BaseLaneManualCalibrationThread::setPoint2AndExtend(cv::Point point) {
    Line line = direction == MANUAL_LEFT ? leftLine : rightLine;
    line.setP2(point);

    direction == MANUAL_LEFT
        ? updateLeftLine(line.Extrapolate(pSize.height, pSize.width))
        : updateRightLine(line.Extrapolate(pSize.height, pSize.width));
}

void BaseLaneManualCalibrationThread::setDirection(ManualDirection direction) {
    this->direction = direction;
}

ManualDirection BaseLaneManualCalibrationThread::getDirection() {
    return direction;
}

bool BaseLaneManualCalibrationThread::isLineValid(Line &line) {
    if (line.p1.x == 0 && line.p1.y == 0) {
        return false;
    }

    if (line.p2.x == 0 && line.p2.y == 0) {
        return false;
    }

    return true;
}

void BaseLaneManualCalibrationThread::setRightLine(Line line) {
    updateRightLine(line);
}

Line BaseLaneManualCalibrationThread::getRightLine() {
    std::unique_lock<std::mutex> lock(m_mutex);
    return rightLine;
}

void BaseLaneManualCalibrationThread::setLeftLine(Line line) {
    updateLeftLine(line);
}

Line BaseLaneManualCalibrationThread::getLeftLine() {
    std::unique_lock<std::mutex> lock(m_mutex);
    return leftLine;
}

// line size is in preview size
// need to convert to original size (image size)
Line ManualCalibrationCameraThread::getRealRightLine() {
    std::unique_lock<std::mutex> lock(m_mutex);

    Line rl = this->rightLine.Scale(pSize, imageSize);
    return rl;
}

Line ManualCalibrationCameraThread::getRealLeftLine() {
    std::unique_lock<std::mutex> lock(m_mutex);

    Line ll = this->leftLine.Scale(pSize, imageSize);
    return ll;
}
