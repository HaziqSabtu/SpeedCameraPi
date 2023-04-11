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
LoadCaptureThread::LoadCaptureThread(wxEvtHandler *parent, CameraBase *camera,
                                     const int maxFrame, const bool debug)
    : wxThread(wxTHREAD_JOINABLE), parent(parent), camera(camera),
      maxFrame(maxFrame), debug(debug) {}

/**
 * @brief Destroy the Load Capture Thread:: Load Capture Thread object
 */
LoadCaptureThread::~LoadCaptureThread() { camera = nullptr; }

/**
 * @brief Entry point for the thread
 * @details This function will be called when the thread is started
 * <ul>
 * <li>Check if camera is opened</li>
 * <li>Grab and retrieve frame from camera</li>
 * <li>Post CaptureImageEvent to parent to signal the start of capture</li>
 * <li>Post UpdateImageEvent to parent to signal that a new frame is
 * available</li>
 * <li>Post CaptureImageEvent to parent to signal the end of capture</li>
 * </ul>
 *
 *
 * @return wxThread::ExitCode
 */
wxThread::ExitCode LoadCaptureThread::Entry() {
      std::unique_ptr<std::vector<ImageData>> imgData =
          std::make_unique<std::vector<ImageData>>();

      CaptureImageEvent startCaptureEvent(c_CAPTURE_IMAGE_EVENT, CAPTURE_START);
      wxPostEvent(parent, startCaptureEvent);

      cv::Mat frame;

      for (int i = 0; i < maxFrame; i++) {
            camera->getFrame(frame);
            if (frame.empty()) {
                  std::cout << "Failed to capture frame" << std::endl;
                  continue;
            }
            imgData->push_back(ImageData(frame.clone()));
            UpdateImageEvent event(c_UPDATE_IMAGE_EVENT, UPDATE_IMAGE);
            event.SetImageData(ImageData(frame));
            wxPostEvent(parent, event);

            if (TestDestroy()) {
                  break;
            }
      }

      cv::Mat first = imgData->at(0).image;
      UpdateImageEvent updateImageEvent(c_UPDATE_IMAGE_EVENT, UPDATE_IMAGE);
      updateImageEvent.SetImageData(first);
      wxPostEvent(parent, updateImageEvent);

      if (debug) {
            FILEWR::WriteFile(imgData.get());
      }

      CaptureImageEvent stopCaptureEvent(c_CAPTURE_IMAGE_EVENT, CAPTURE_END);
      stopCaptureEvent.SetImageData(imgData.release());
      wxPostEvent(parent, stopCaptureEvent);

      return 0;
}