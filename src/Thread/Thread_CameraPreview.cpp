#include <Event/Event.hpp>
#include <Thread/Thread_CameraPreview.hpp>

/**
 * @brief Construct a new Camera Preview Thread:: Camera Preview Thread object
 *
 * @param parent Pointer to the parent wxEvtHandler
 * @param camera Unique_ptr to the Camera
 */
CameraPreviewThread::CameraPreviewThread(wxEvtHandler *parent,
                                         CameraPtr &camera)
    : BaseThread(parent, nullptr), CameraAccessor(camera), PreviewableThread() {
}

/**
 * @brief Destroy the Camera Preview Thread:: Camera Preview Thread object
 *
 */
CameraPreviewThread::~CameraPreviewThread() {}

/**
 * @brief Entry point of the Thread
 * @details Send the start event to the View. Then capture the frame from the
 * camera and send it to the View. If an error occurs, send the error event to
 * the View. Finally send the end event to the View.
 *
 * @return ExitCode
 */
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

/**
 * @brief Get the ThreadID
 *
 * @return ThreadID
 */
ThreadID CameraPreviewThread::getID() const { return id; }