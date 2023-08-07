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

class RoiPreviewThread : public wxThread {
  public:
    RoiPreviewThread(wxEvtHandler *parent, DataPtr data);
    ~RoiPreviewThread();

    ThreadID getID() const;

  protected:
    virtual ExitCode Entry();

  private:
    wxEvtHandler *parent;
    DataPtr data;

    const ThreadID id = THREAD_ROI_PREVIEW;

    cv::Size pSize;
    cv::Size imageSize;
};
