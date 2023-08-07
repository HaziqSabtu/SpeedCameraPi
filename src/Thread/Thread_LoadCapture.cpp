/**
 * @file Thread_LoadCapture.cpp
 * @author Haziq Sabtu (mhaziq.sabtu@gmail.com)
 * @brief Custom wxThread for loading ImageData from Camera
 * @version 1.0.0
 * @date 2023-03-18
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "Event/Event_Error.hpp"
#include "Event/Event_LoadImage.hpp"
#include "Model/SessionData.hpp"
#include <Thread/Thread_LoadCapture.hpp>
#include <memory>

LoadCaptureThread::LoadCaptureThread(wxEvtHandler *parent,
                                     std::unique_ptr<CameraBase> &camera,
                                     DataPtr data, const int maxFrame,
                                     const bool debug_SaveImageData,
                                     const bool debug_ShowImagesWhenCapture)
    : wxThread(wxTHREAD_JOINABLE), parent(parent), camera(std::move(camera)),
      data(data), maxFrame(maxFrame), debug_SaveImageData(debug_SaveImageData),
      debug_ShowImagesWhenCapture(debug_ShowImagesWhenCapture) {}

LoadCaptureThread::~LoadCaptureThread() {}

/**
 * @brief Entry point for the thread
 * @details This function will be called when the thread is started
 * <ul>
 * <li>Check if camera is opened</li>
 * <li>Grab and retrieve frame from camera</li>
 * <li>Post CaptureImageEvent to parent to signal the start of capture</li>
 * <li>Post updatePreviewEvent to parent to signal that a new frame is
 * available</li>
 * <li>Post CaptureImageEvent to parent to signal the end of capture</li>
 * </ul>
 *
 *
 * @return wxThread::ExitCode
 */
wxThread::ExitCode LoadCaptureThread::Entry() {
    try {
        wxCommandEvent startLoadEvent(c_LOAD_IMAGE_EVENT, LOAD_START_CAMERA);
        wxPostEvent(parent, startLoadEvent);

        CDVector vec;

        if (data == nullptr) {
            throw std::runtime_error("data is null");
        }

        if (!data->isCaptureDataEmpty()) {
            throw std::runtime_error("capture data is not empty");
        }

        cv::Mat frame;

        // warmup
        // first few frames have inconsistent time stamp
        for (int i = 0; i < WARMPUP_COUNT; i++) {
            camera->getFrame(frame);
        }

        for (int i = 0; i < maxFrame; i++) {

            camera->getFrame(frame);

            if (frame.empty()) {
                std::cout << "Failed to capture frame" << std::endl;
                continue;
            }

            vec.push_back(CaptureData(frame.clone()));

            if (TestDestroy()) {
                break;
            }

            // if running in VNC there are possibility that the image
            // captured at wrong captured time ... better turn off for now
            // show the result after finish capturing instead
            if (!debug_ShowImagesWhenCapture) {
                continue;
            }
        }

        data->setCaptureData(vec);

        // showing captured frames
        for (int i = 0; i < maxFrame; i++) {
            cv::Mat frame = vec.at(i).image;
            UpdatePreviewEvent updatePreviewEvent(c_UPDATE_PREVIEW_EVENT,
                                                  UPDATE_PREVIEW);
            updatePreviewEvent.SetImage(frame);
            wxPostEvent(parent, updatePreviewEvent);
            wxMilliSleep(200);
        }

        // TODO: Handle Saving
        if (debug_SaveImageData) {
            // FILEWR::WriteFile(imgData);
        }

    } catch (const std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }

    wxCommandEvent stopLoadEvent(c_LOAD_IMAGE_EVENT, LOAD_END_CAMERA);
    wxPostEvent(parent, stopLoadEvent);
    return 0;
}

/**
 * @brief Get the Camera object
 *
 * @return std::unique_ptr<CameraBase>
 */
std::unique_ptr<CameraBase> LoadCaptureThread::getCamera() {
    return std::move(camera);
}

/**
 * @brief Get the ID object
 *
 * @return ThreadID
 */
ThreadID LoadCaptureThread::getID() const { return id; }
