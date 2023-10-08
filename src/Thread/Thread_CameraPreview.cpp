#include "Event/Event_Error.hpp"
#include "Thread/Thread_Base.hpp"
#include <Thread/Thread_CameraPreview.hpp>
#include <memory>
#include <wx/event.h>

CameraPreviewThread::CameraPreviewThread(wxEvtHandler *parent,
                                         CameraPtr &camera)
    : BaseThread(parent, nullptr), CameraAccessor(camera), PreviewableThread() {
}

CameraPreviewThread::~CameraPreviewThread() {}

wxThread::ExitCode CameraPreviewThread::Entry() {

    wxCommandEvent startPreviewCameraEvent(c_PREVIEW_CAMERA_EVENT,
                                           PREVIEW_START);
    wxPostEvent(parent, startPreviewCameraEvent);

    try {

        while (!TestDestroy()) {
            cv::Mat frame;
            camera->getFrame(frame);

            if (frame.empty()) {
                std::cout << "Failed to capture frame" << std::endl;
                continue;
            }

            cv::resize(frame, frame, pSize);

            UpdatePreviewEvent::Submit(parent, frame);
        }
    } catch (const std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
        wxCommandEvent errorPreviewCameraEvent(c_PREVIEW_CAMERA_EVENT,
                                               PREVIEW_ERROR);
        wxPostEvent(parent, errorPreviewCameraEvent);
    }

    UpdatePreviewEvent clearPreviewEvent(c_UPDATE_PREVIEW_EVENT, CLEAR_PREVIEW);
    wxPostEvent(parent, clearPreviewEvent);

    wxCommandEvent endPreviewCameraEvent(c_PREVIEW_CAMERA_EVENT, PREVIEW_END);
    wxPostEvent(parent, endPreviewCameraEvent);

    return 0;
}

ThreadID CameraPreviewThread::getID() const { return id; }