#include <Event/Event.hpp>
#include <Thread/Thread_LaneManualCalibrationCapture.hpp>

LaneManualCalibrationCaptureThread::LaneManualCalibrationCaptureThread(
    wxEvtHandler *parent, DataPtr data)
    : BaseLaneManualCalibrationThread(parent, data), ImageSizeDataThread(data) {

    if (data->isCaptureDataEmpty()) {
        throw std::runtime_error("Capture data is empty");
    }
}

LaneManualCalibrationCaptureThread::~LaneManualCalibrationCaptureThread() {}

wxThread::ExitCode LaneManualCalibrationCaptureThread::Entry() {

    wxCommandEvent startCalibrationEvent(c_CALIBRATION_EVENT,
                                         CALIBRATION_CAPTURE_START);
    wxPostEvent(parent, startCalibrationEvent);

    try {

        direction == ManualDirection::MANUAL_LEFT
            ? UpdateStatusEvent::Submit(parent, SC::STATUS_MANUAL_SELECTLEFT)
            : UpdateStatusEvent::Submit(parent, SC::STATUS_MANUAL_SELECTRIGHT);

        cv::Mat firstFrame;

        auto captureData = data->getCaptureData();
        auto firstData = captureData.front();
        firstFrame = firstData.image;

        if (firstFrame.empty()) {
            throw std::runtime_error("Failed to capture frame");
        }

        cv::resize(firstFrame, firstFrame, pSize);
        while (!TestDestroy()) {

            cv::Mat previewFrame = firstFrame.clone();

            if (isLineValid(rightLine)) {
                cv::line(previewFrame, rightLine.p1, rightLine.p2,
                         cv::Scalar(0, 255, 255), 2);
            }

            if (isLineValid(leftLine)) {
                cv::line(previewFrame, leftLine.p1, leftLine.p2,
                         cv::Scalar(255, 0, 0), 2);
            }

            UpdatePreviewEvent::Submit(parent, previewFrame);

            wxMilliSleep(100);
        }
    } catch (const std::exception &e) {
        ErrorEvent::Submit(parent, e.what());

        wxCommandEvent endCalibrationEvent(c_CALIBRATION_EVENT,
                                           CALIBRATION_CAPTURE_END);
        wxPostEvent(parent, endCalibrationEvent);

        return 0;
    }

    UpdatePreviewEvent::Submit(parent, CLEAR_PREVIEW);

    wxCommandEvent endCalibrationEvent(c_CALIBRATION_EVENT,
                                       CALIBRATION_CAPTURE_END);
    wxPostEvent(parent, endCalibrationEvent);
    return 0;
}

ThreadID LaneManualCalibrationCaptureThread::getID() const { return threadID; }

// line size is in preview size
// need to convert to original size (image size)
Line LaneManualCalibrationCaptureThread::getRealRightLine() {
    std::unique_lock<std::mutex> lock(m_mutex);

    Line rl = this->rightLine.Scale(pSize, imageSize);
    return rl;
}

Line LaneManualCalibrationCaptureThread::getRealLeftLine() {
    std::unique_lock<std::mutex> lock(m_mutex);

    Line ll = this->leftLine.Scale(pSize, imageSize);
    return ll;
}

CalibrationData LaneManualCalibrationCaptureThread::getCalibrationData() {
    return CalibrationData(getRealRightLine(), getRealLeftLine());
}