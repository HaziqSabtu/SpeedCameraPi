#pragma once

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

class CapturePreviewThread : public BaseThread, PreviewableThread {
  public:
    CapturePreviewThread(wxEvtHandler *parent, DataPtr data);
    ~CapturePreviewThread();

    ThreadID getID() const override;

  protected:
    ExitCode Entry() override;

  private:
    const ThreadID id = THREAD_CAPTURE_PREVIEW;
};
