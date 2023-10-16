#pragma once

#include "Model/SessionData.hpp"
#include "Thread/Thread_Base.hpp"
#include "Thread/Thread_ID.hpp"
#include <Event/Event_Preview.hpp>
#include <Event/Event_UpdatePreview.hpp>

#include <Utils/Camera/CameraBase.hpp>

#include <memory>
#include <string>

#include <opencv2/opencv.hpp>

#include <wx/thread.h>

class RoiPreviewThread : public BaseThread,
                         PreviewableThread,
                         ImageSizeDataThread {
  public:
    RoiPreviewThread(wxEvtHandler *parent, DataPtr data);
    ~RoiPreviewThread();

    ThreadID getID() const override;

  protected:
    virtual ExitCode Entry() override;

  private:
    const ThreadID id = THREAD_ROI_PREVIEW;
};