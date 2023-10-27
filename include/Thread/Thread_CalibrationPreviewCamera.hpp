#pragma once

#include <Thread/Thread_Base.hpp>

#include <Utils/Camera/CameraBase.hpp>

/**
 * @brief Thread implementation for Preview the Calibration result with camera
 *
 */
class CalibrationPreviewCameraThread : public BaseThread,
                                       public CameraAccessor,
                                       public ImageSizeCameraThread,
                                       public PreviewableThread {
  public:
    CalibrationPreviewCameraThread(wxEvtHandler *parent, DataPtr data,
                                   CameraPtr &camera);
    ~CalibrationPreviewCameraThread();

    ThreadID getID() const override;

  protected:
    virtual ExitCode Entry() override;

  private:
    const ThreadID id = THREAD_CALIBRATION_PREVIEW_CAMERA;
};
