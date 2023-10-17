#include "Event/Event_UpdateStatus.hpp"
#include "UI/Layout/StatusPanel.hpp"
#include <Thread/Thread_DistanceCalibrationCapture.hpp>

DistanceCalibrationCaptureThread::DistanceCalibrationCaptureThread(
    wxEvtHandler *parent, DataPtr data)
    : BaseDistanceCalibrationThread(parent, data), ImageSizeDataThread(data) {

    if (data->isCaptureDataEmpty()) {
        throw std::runtime_error("Capture data is empty");
    }
}

DistanceCalibrationCaptureThread::~DistanceCalibrationCaptureThread() {}

wxThread::ExitCode DistanceCalibrationCaptureThread::Entry() {

    wxCommandEvent startCalibrationEvent(c_CALIBRATION_EVENT,
                                         CALIBRATION_CAPTURE_START);
    wxPostEvent(parent, startCalibrationEvent);

    try {

        direction == DistanceDirection::DISTANCE_TOP
            ? UpdateStatusEvent::Submit(parent, SC::STATUS_DISTANCE_SELECTTOP)
            : UpdateStatusEvent::Submit(parent,
                                        SC::STATUS_DISTANCE_SELECTBOTTOM);

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

            if (isLineValid(topLine)) {
                cv::line(previewFrame, topLine.p1, topLine.p2,
                         cv::Scalar(0, 255, 255), 2);
            }

            if (isLineValid(bottomLine)) {
                cv::line(previewFrame, bottomLine.p1, bottomLine.p2,
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

ThreadID DistanceCalibrationCaptureThread::getID() const { return threadID; }

// line size is in preview size
// need to convert to original size (image size)
Line DistanceCalibrationCaptureThread::getRealTopLine() {
    std::unique_lock<std::mutex> lock(m_mutex);

    Line rl = this->topLine.Scale(pSize, imageSize);
    return rl;
}

Line DistanceCalibrationCaptureThread::getRealBottomLine() {
    std::unique_lock<std::mutex> lock(m_mutex);

    Line ll = this->bottomLine.Scale(pSize, imageSize);
    return ll;
}

CalibrationData DistanceCalibrationCaptureThread::getCalibrationData() {
    return CalibrationData(getRealTopLine(), getRealBottomLine());
}