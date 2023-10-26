#pragma once

#include <Thread/Thread_Base.hpp>

#include <Utils/Camera/CameraBase.hpp>

/**
 * @brief Thread implementation for Preview the the captured data
 *
 */
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
