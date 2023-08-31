#include "Event/Event_Error.hpp"
#include "Thread/Thread_Base.hpp"
#include <Thread/Thread_CameraPreview.hpp>
#include <memory>

CameraPreviewThread::CameraPreviewThread(wxEvtHandler *parent,
                                         CameraPtr &camera)
    : BaseThread(parent, nullptr), CameraAccessor(camera) {}

/**
 * @brief Destroy the Capture Thread:: Capture Thread object
 *
 */
CameraPreviewThread::~CameraPreviewThread() {}

wxThread::ExitCode CameraPreviewThread::Entry() {

    wxCommandEvent startCaptureEvent(c_CAPTURE_EVENT, CAPTURE_START);
    wxPostEvent(parent, startCaptureEvent);

    try {

        while (!TestDestroy()) {
            cv::Mat frame;
            camera->getFrame(frame);

            if (frame.empty()) {
                std::cout << "Failed to capture frame" << std::endl;
                continue;
            }

            UpdatePreviewEvent::Submit(parent, frame);
        }
    } catch (const std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }

    UpdatePreviewEvent clearPreviewEvent(c_UPDATE_PREVIEW_EVENT, CLEAR_PREVIEW);
    wxPostEvent(parent, clearPreviewEvent);

    wxCommandEvent endCaptureEvent(c_CAPTURE_EVENT, CAPTURE_END);
    wxPostEvent(parent, endCaptureEvent);

    return 0;
}

ThreadID CameraPreviewThread::getID() const { return id; }