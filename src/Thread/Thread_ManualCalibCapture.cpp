#include "Event/Event_Calibration.hpp"
#include "Event/Event_Error.hpp"
#include "Event/Event_UpdatePreview.hpp"
#include "Event/Event_UpdateStatus.hpp"
#include "Model/CalibrationData.hpp"
#include "Thread/Thread_ManualCalib.hpp"
#include "UI/Layout/StatusPanel.hpp"
#include <Thread/Thread_ManualCalibCapture.hpp>
#include <opencv2/imgproc.hpp>
#include <wx/utils.h>

ManualCalibrationCaptureThread::ManualCalibrationCaptureThread(
    wxEvtHandler *parent, DataPtr data)
    : BaseManualCalibrationThread(parent), data(data) {

    if (data->isCaptureDataEmpty()) {
        throw std::runtime_error("Capture data is empty");
    }
}

ManualCalibrationCaptureThread::~ManualCalibrationCaptureThread() {}

wxThread::ExitCode ManualCalibrationCaptureThread::Entry() {

    wxCommandEvent startCalibrationEvent(c_CALIBRATION_EVENT,
                                         CALIBRATION_START);
    wxPostEvent(parent, startCalibrationEvent);

    try {

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

            if (isLineValid(yellowLine)) {
                cv::line(previewFrame, yellowLine.p1, yellowLine.p2,
                         cv::Scalar(0, 255, 255), 2);
            }

            if (isLineValid(blueLine)) {
                cv::line(previewFrame, blueLine.p1, blueLine.p2,
                         cv::Scalar(255, 0, 0), 2);
            }

            UpdatePreviewEvent::Submit(parent, previewFrame);

            wxMilliSleep(100);
        }
    } catch (const std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }

    UpdatePreviewEvent::Submit(parent, CLEAR_PREVIEW);

    wxCommandEvent endCalibrationEvent(c_CALIBRATION_EVENT, CALIBRATION_END);
    wxPostEvent(parent, endCalibrationEvent);
    return 0;
}

ThreadID ManualCalibrationCaptureThread::getID() const { return threadID; }

CalibData ManualCalibrationCaptureThread::getCalibData() {
    std::unique_lock<std::mutex> lock(m_mutex);
    return CalibData(yellowLine, blueLine);
}