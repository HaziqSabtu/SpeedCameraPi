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

#include <Thread/Thread_LoadCapture.hpp>

/**
 * @brief Construct a new Load Capture Thread:: Load Capture Thread object
 *
 * @param parent parent wxEvtHandler
 * @param camera camera object
 * @param maxFrame maximum frame to capture
 * @param debug debug mode
 */
LoadCaptureThread::LoadCaptureThread(
  wxEvtHandler* parent,
  std::shared_ptr<CameraBase> camera,
  std::shared_ptr<std::vector<ImageData>> imgData,
  const int maxFrame,
  const bool debug_SaveImageData,
  const bool debug_ShowImagesWhenCapture)
    : wxThread(wxTHREAD_JOINABLE), parent(parent), camera(camera),
      imgData(imgData), maxFrame(maxFrame),
      debug_SaveImageData(debug_SaveImageData),
      debug_ShowImagesWhenCapture(debug_ShowImagesWhenCapture) {}

/**
 * @brief Destroy the Load Capture Thread:: Load Capture Thread object
 */
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
        wxCommandEvent startLoadEvent(c_LOAD_IMAGE_EVENT, LOAD_START);
        wxPostEvent(parent, startLoadEvent);

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

            imgData->push_back(ImageData(frame.clone()));

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

        // showing captured frames
        for (int i = 0; i < imgData->size(); i++) {
            cv::Mat frame = imgData->at(i).image;
            UpdatePreviewEvent updatePreviewEvent(c_UPDATE_PREVIEW_EVENT,
                                                  UPDATE_PREVIEW);
            updatePreviewEvent.SetImage(frame);
            wxPostEvent(parent, updatePreviewEvent);
            wxMilliSleep(200);
        }

        if (debug_SaveImageData) {
            FILEWR::WriteFile(imgData);
        }

    } catch (const std::exception& e) {
        std::cout << "LoadCaptureThread::Entry() - " << e.what()
                  << std::endl;
    }

    wxCommandEvent stopLoadEvent(c_LOAD_IMAGE_EVENT, LOAD_END_CAMERA);
    wxPostEvent(parent, stopLoadEvent);
    return 0;
}