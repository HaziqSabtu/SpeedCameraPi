#pragma once

#include <Thread/Thread_Base.hpp>

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
