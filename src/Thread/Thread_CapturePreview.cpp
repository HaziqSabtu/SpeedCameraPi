#include "Thread/Thread_CapturePreview.hpp"
#include "Event/Event_Error.hpp"
#include "Event/Event_LoadImage.hpp"
#include "Event/Event_Preview.hpp"
#include "Event/Event_Replay.hpp"
#include "Thread/Thread_Base.hpp"
#include "Thread/Thread_ID.hpp"
#include <memory>
#include <opencv2/imgproc.hpp>

CapturePreviewThread::CapturePreviewThread(wxEvtHandler *parent, DataPtr data)
    : BaseThread(parent, data), PreviewableThread() {}

CapturePreviewThread::~CapturePreviewThread() {}

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
