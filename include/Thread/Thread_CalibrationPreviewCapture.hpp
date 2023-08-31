#pragma once

#include "Model/SessionData.hpp"
#include "Thread/Thread_Base.hpp"
#include "Thread/Thread_ID.hpp"
#include <Event/Event_Capture.hpp>
#include <Event/Event_UpdatePreview.hpp>

#include <Utils/Camera/CameraBase.hpp>

#include <memory>
#include <string>

#include <opencv2/opencv.hpp>

#include <wx/thread.h>

class CalibrationPreviewCaptureThread : public BaseThread,
                                        public ImageSizeDataThread,
                                        public PreviewableThread {
  public:
    CalibrationPreviewCaptureThread(wxEvtHandler *parent, DataPtr data);
    ~CalibrationPreviewCaptureThread();

    ThreadID getID() const override;

  protected:
    virtual ExitCode Entry() override;

  private:
    const ThreadID id = THREAD_CALIBRATION_PREVIEW_CAPTURE;
};
