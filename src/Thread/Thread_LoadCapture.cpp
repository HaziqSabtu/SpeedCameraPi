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

#include <Event/Event.hpp>
#include <Thread/Thread_LoadCapture.hpp>

LoadCaptureThread::LoadCaptureThread(wxEvtHandler *parent, CameraPtr &camera,
                                     DataPtr data, const int maxFrame,
                                     const bool debug_ShowImage,
                                     const bool debug_Save)
    : BaseThread(parent, data), CameraAccessor(camera), PreviewableThread(),
      maxFrame(maxFrame), debug_SaveImageData(debug_Save),
      debug_ShowImagesWhenCapture(debug_ShowImage) {}

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

            cv::resize(frame, frame, pSize);
            UpdatePreviewEvent::Submit(parent, frame);

            // is this necessary?
            // wxMilliSleep(200);
        }

        data->setCaptureData(vec);

        // showing captured frames after finish capturing
        if (!debug_ShowImagesWhenCapture) {
            for (int i = 0; i < maxFrame; i++) {
                cv::Mat frame = vec.at(i).image.clone();
                cv::resize(frame, frame, pSize);
                UpdatePreviewEvent::Submit(parent, frame);
                wxMilliSleep(200);
            }
        }

        if (debug_SaveImageData) {
            auto random = std::to_string(std::rand());
            auto filename = "DEBUG_" + random;

            Utils::FileReadWrite().WriteFile(data, filename);
        }

    } catch (const std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
        wxCommandEvent errorLoadEvent(c_LOAD_IMAGE_EVENT, LOAD_ERROR_CAMERA);
        wxPostEvent(parent, errorLoadEvent);

        return 0;
    }

    wxCommandEvent stopLoadEvent(c_LOAD_IMAGE_EVENT, LOAD_END_CAMERA);
    wxPostEvent(parent, stopLoadEvent);
    return 0;
}

/**
 * @brief Get the ID object
 *
 * @return ThreadID
 */
ThreadID LoadCaptureThread::getID() const { return id; }
