
#include <Thread/Thread_CalibrationPreviewCapture.hpp>

#include <Event/Event.hpp>

/**
 * @brief Construct a new Calibration Preview Capture Thread:: Calibration
 * Preview Capture Thread object
 *
 * @param parent Pointer to the View
 * @param data Pointer to the SessionData
 */
CalibrationPreviewCaptureThread::CalibrationPreviewCaptureThread(
    wxEvtHandler *parent, DataPtr data)
    : BaseThread(parent, data), ImageSizeDataThread(data), PreviewableThread() {
}

/**
 * @brief Destroy the Calibration Preview Capture Thread:: Calibration Preview
 * Capture Thread object
 *
 */
CalibrationPreviewCaptureThread::~CalibrationPreviewCaptureThread() {}

/**
 * @brief Entry point of the Thread
 * @details If calibration data is available, draw the lines on the preview
 * image. Then send the image to the View.
 *
 * @return ExitCode
 */
wxThread::ExitCode CalibrationPreviewCaptureThread::Entry() {

    wxCommandEvent startPreviewEvent(c_PREVIEW_CAPTURE_EVENT, PREVIEW_START);
    wxPostEvent(parent, startPreviewEvent);

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

        wxCommandEvent errorPreviewEvent(c_PREVIEW_CAPTURE_EVENT,
                                         PREVIEW_ERROR);
        wxPostEvent(parent, errorPreviewEvent);
    }

    UpdatePreviewEvent::Submit(parent, CLEAR_PREVIEW);

    wxCommandEvent endPreviewEvent(c_PREVIEW_CAPTURE_EVENT, PREVIEW_END);
    wxPostEvent(parent, endPreviewEvent);
    return 0;
}

/**
 * @brief Get the ThreadID
 *
 * @return ThreadID
 */
ThreadID CalibrationPreviewCaptureThread::getID() const { return id; }