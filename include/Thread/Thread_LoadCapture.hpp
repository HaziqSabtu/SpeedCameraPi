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

#include <Event/Event_CaptureImage.hpp>
#include <Event/Event_UpdateImage.hpp>
#include <Utils/Config/AppConfig.hpp>
#include <Utils/FileReader/fileWR.hpp>
#include <memory>
#include <opencv2/opencv.hpp>
#include <raspicam/raspicam_cv.h>
#include <wx/string.h>
#include <wx/thread.h>
#include <wx/wx.h>

/**
 * @brief Custom wxThread for loading ImageData from Camera
 *
 */
class LoadCaptureThread : public wxThread {
  public:
    LoadCaptureThread(wxEvtHandler *parent, raspicam::RaspiCam_Cv *camera,
                      const int maxFrame, const bool debug);
    ~LoadCaptureThread();

  protected:
    ExitCode Entry();

  private:
    wxEvtHandler *parent;
    raspicam::RaspiCam_Cv *camera;
    const int maxFrame;
    const bool debug;
};

#endif