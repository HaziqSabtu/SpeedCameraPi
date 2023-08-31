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

#include "Model/SessionData.hpp"
#include "Thread/Thread_Base.hpp"
#include "Thread/Thread_ID.hpp"
#include <Event/Event_Error.hpp>
#include <Event/Event_LoadImage.hpp>
#include <Event/Event_UpdatePreview.hpp>

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
class LoadCaptureThread : public BaseThread,
                          public PreviewableThread,
                          public CameraAccessor {
  public:
    LoadCaptureThread(wxEvtHandler *parent, CameraPtr &camera, DataPtr data,
                      const int maxFrame, const bool debug_ShowImage = false,
                      const bool debug_Save = false);
    ~LoadCaptureThread();

    ThreadID getID() const override;

  protected:
    ExitCode Entry() override;

  private:
    const int maxFrame;
    const int WARMPUP_COUNT = 5;
    const bool debug_SaveImageData;
    const bool debug_ShowImagesWhenCapture;

    const ThreadID id = THREAD_LOAD_CAPTURE;
};

#endif