/**
 * @file Thread_Capture.cpp
 * @author Haziq Sabtu (mhaziq.sabtu@gmail.com)
 * @brief Custom wxThread for capturing image from camera
 * @version 1.0.0
 * @date 2023-03-18
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <Thread/Thread_Capture.hpp>

/**
 * @brief Construct a new Capture Thread:: Capture Thread object
 *
 * @param parent parent wxPanel/wxEvtHandler
 * @param cap pointer to RaspiCam_Cv object
 */
CaptureThread::CaptureThread(wxEvtHandler* parent,
                             std::shared_ptr<CameraBase> camera)
    : wxThread(wxTHREAD_JOINABLE), camera(camera) {
    this->m_parent = parent;
}

/**
 * @brief Destroy the Capture Thread:: Capture Thread object
 *
 */
CaptureThread::~CaptureThread() {}

/**
 * @brief Thread Entry Point
 * @details This function will be called when the thread is started
 * <ul>
 * <li>Check if camera is opened</li>
 * <li>Grab frame from camera</li>
 * <li>If frame is empty, skip to next iteration</li>
 * <li>Post UpdateImageEvent to signal that a new frame is available</li>
 * </ul>
 *
 * @return wxThread::ExitCode
 */
wxThread::ExitCode CaptureThread::Entry() {

    wxCommandEvent startCaptureEvent(c_CAPTURE_EVENT, CAPTURE_START);
    wxPostEvent(m_parent, startCaptureEvent);

    while (!TestDestroy()) {
        cv::Mat frame;
        camera->getFrame(frame);

        if (frame.empty()) {
            std::cout << "Failed to capture frame" << std::endl;
            continue;
        }

        UpdateImageEvent event(c_UPDATE_IMAGE_EVENT, UPDATE_IMAGE);
        event.SetImageData(ImageData(frame));
        wxPostEvent(m_parent, event);
    }

    UpdateImageEvent event(c_UPDATE_IMAGE_EVENT, CLEAR_IMAGE);
    wxPostEvent(m_parent, event);

    wxCommandEvent endCaptureEvent(c_CAPTURE_EVENT, CAPTURE_END);
    wxPostEvent(m_parent, endCaptureEvent);
    return 0;
}