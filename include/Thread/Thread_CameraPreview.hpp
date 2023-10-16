/**
 * @file Thread_Capture.hpp
 * @author Haziq Sabtu (mhaziq.sabtu@gmail.com)
 * @brief Custom wxThread for capturing image from camera
 * @version 1.0.0
 * @date 2023-03-18
 *
 * @copyright Copyright (c) 2023
 *
 */
#ifndef CAPTURE_THREAD_HPP
#define CAPTURE_THREAD_HPP

#include "Thread/Thread_Base.hpp"
#include "Thread/Thread_ID.hpp"
#include <Event/Event_Preview.hpp>
#include <Event/Event_UpdatePreview.hpp>

#include <Utils/Camera/CameraBase.hpp>

#include <memory>
#include <string>

#include <opencv2/opencv.hpp>

#include <wx/thread.h>

/**
 * @brief Custom wxThread for capturing image from camera
 *
 */
class CameraPreviewThread : public BaseThread,
                            public CameraAccessor,
                            public PreviewableThread {
  public:
    CameraPreviewThread(wxEvtHandler *parent, CameraPtr &camera);
    ~CameraPreviewThread();

    ThreadID getID() const override;

  protected:
    virtual ExitCode Entry() override;

  private:
    const ThreadID id = THREAD_CAMERA_PREVIEW;
};

#endif