/**
 * @file Thread_LoadCapture.hpp
 * @author Haziq Sabtu (mhaziq.sabtu@gmail.com)
 * @brief Custom wxThread for loading ImageData from Camera
 * @version 1.0.0
 * @date 2023-03-18
 *
 * @copyright Copyright (c) 2023
 *
 */
#ifndef LOAD_CAPTURE_THREAD_HPP
#define LOAD_CAPTURE_THREAD_HPP

#include <Event/Event_LoadImage.hpp>
#include <Event/Event_UpdateImage.hpp>
#include <Utils/Camera/CameraBase.hpp>
#include <Utils/Config/AppConfig.hpp>
#include <Utils/FileReader/fileWR.hpp>

#include <memory>
#include <opencv2/opencv.hpp>

#include <wx/string.h>
#include <wx/thread.h>
#include <wx/wx.h>

/**
 * @brief Custom wxThread for loading ImageData from Camera
 *
 */
class LoadCaptureThread : public wxThread {
  public:
    LoadCaptureThread(wxEvtHandler* parent,
                      std::shared_ptr<CameraBase> camera,
                      std::shared_ptr<std::vector<ImageData>> imgData,
                      const int maxFrame,
                      const bool debug_SaveImageData,
                      const bool debug_ShowImagesWhenCapture);
    ~LoadCaptureThread();

  protected:
    ExitCode Entry();

  private:
    wxEvtHandler* parent;
    std::shared_ptr<CameraBase> camera;
    std::shared_ptr<std::vector<ImageData>> imgData;
    const int maxFrame;
    const bool debug_SaveImageData;
    const bool debug_ShowImagesWhenCapture;
};

#endif