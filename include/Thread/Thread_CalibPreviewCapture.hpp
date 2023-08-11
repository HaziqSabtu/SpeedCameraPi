#pragma once

#include "Model/SessionData.hpp"
#include "Thread/Thread_ID.hpp"
#include <Event/Event_Capture.hpp>
#include <Event/Event_UpdatePreview.hpp>

#include <Utils/Camera/CameraBase.hpp>
#include <Utils/DataStruct.hpp>

#include <memory>
#include <string>

#include <opencv2/opencv.hpp>

#include <wx/thread.h>

class CalibCapturePreviewThread : public wxThread {
  public:
    CalibCapturePreviewThread(wxEvtHandler *parent, DataPtr data);
    ~CalibCapturePreviewThread();

    ThreadID getID() const;

  protected:
    virtual ExitCode Entry();

  private:
    wxEvtHandler *parent;
    DataPtr data;

    const ThreadID id = THREAD_CALIBRATION_PREVIEW_CAPTURE;

    cv::Size pSize;
    cv::Size imageSize;
};
