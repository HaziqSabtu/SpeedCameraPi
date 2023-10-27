#include <Thread/Thread_CapturePreview.hpp>

#include <Event/Event.hpp>

/**
 * @brief Construct a new Capture Preview Thread:: Capture Preview Thread object
 *
 * @param parent Pointer to the View
 * @param data Pointer to the SessionData
 */
CapturePreviewThread::CapturePreviewThread(wxEvtHandler *parent, DataPtr data)
    : BaseThread(parent, data), PreviewableThread() {}

/**
 * @brief Destroy the Capture Preview Thread:: Capture Preview Thread object
 *
 */
CapturePreviewThread::~CapturePreviewThread() {}

/**
 * @brief Entry point of the Thread
 * @details If capture data is available, send the start event to the View. Then
 * send the captured image to the View. If an error occurs, send the error event
 * to the View. Finally send the end event to the View.
 *
 * @return ExitCode
 */
wxThread::ExitCode CapturePreviewThread::Entry() {
    try {

        wxCommandEvent previewCaptureStartEvent(c_PREVIEW_CAPTURE_EVENT,
                                                PREVIEW_START);
        wxPostEvent(parent, previewCaptureStartEvent);

        if (data->isCaptureDataEmpty()) {
            throw std::runtime_error("capture data is empty");
        }

        auto captureData = data->getCaptureData();

        const int MAX_FRAME = captureData.size();

        for (int i = 0; i < MAX_FRAME; i++) {

            cv::Mat frame = captureData.at(i).image.clone();
            cv::resize(frame, frame, pSize);
            UpdatePreviewEvent::Submit(parent, frame);

            wxMilliSleep(200);

            if (TestDestroy()) {
                break;
            }
        }

    } catch (const std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
        wxCommandEvent previewCaptureErrorEvent(c_PREVIEW_CAPTURE_EVENT,
                                                PREVIEW_ERROR);
        wxPostEvent(parent, previewCaptureErrorEvent);

        return 0;
    }

    wxCommandEvent previewCaptureStopEvent(c_PREVIEW_CAPTURE_EVENT,
                                           PREVIEW_END);
    wxPostEvent(parent, previewCaptureStopEvent);
    return 0;
}

ThreadID CapturePreviewThread::getID() const { return id; }
