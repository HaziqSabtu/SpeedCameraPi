#pragma once

#include <Thread/Thread_Base.hpp>
#include <Utils/Camera/CameraBase.hpp>

/**
 * @brief Custom wxThread for showing image from camera
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