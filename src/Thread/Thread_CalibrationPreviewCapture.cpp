
#include "Event/Event_Error.hpp"
#include <Thread/Thread_CalibrationPreviewCapture.hpp>
#include <memory>
#include <opencv2/core/types.hpp>

CalibrationPreviewCaptureThread::CalibrationPreviewCaptureThread(
    wxEvtHandler *parent, DataPtr data)
    : BaseThread(parent, data), ImageSizeDataThread(data), PreviewableThread() {
}

CalibrationPreviewCaptureThread::~CalibrationPreviewCaptureThread() {}

wxThread::ExitCode CalibrationPreviewCaptureThread::Entry() {
    try {
        cv::Mat firstFrame;
        auto captureData = data->getCaptureData();
        auto firstData = captureData.front();
        firstFrame = firstData.image.clone();

        if (firstFrame.empty()) {
            throw std::runtime_error("Frame is empty");
        }

        cv::resize(firstFrame, firstFrame, pSize);

        while (!TestDestroy()) {

            cv::Mat prevFrame = firstFrame.clone();

            auto isLineNull = data->isCalibrationDataEmpty();
            if (!isLineNull) {
                auto calibData = data->getCalibrationData();
                cv::Scalar yellow(0, 255, 255);
                cv::Scalar blue(255, 0, 0);

                Line left = calibData.lineLeft;
                Line right = calibData.lineRight;

                left = left.Scale(imageSize, pSize);
                right = right.Scale(imageSize, pSize);

                cv::line(prevFrame, left.p1, left.p2, yellow, 2);
                cv::line(prevFrame, right.p1, right.p2, blue, 2);
            }

            UpdatePreviewEvent::Submit(parent, prevFrame);
        }
    } catch (const std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }

    UpdatePreviewEvent clearPreviewEvent(c_UPDATE_PREVIEW_EVENT, CLEAR_PREVIEW);
    wxPostEvent(parent, clearPreviewEvent);

    return 0;
}

ThreadID CalibrationPreviewCaptureThread::getID() const { return id; }