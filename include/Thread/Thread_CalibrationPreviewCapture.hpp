#pragma once

#include "Thread/Thread_Base.hpp"

/**
 * @brief Thread implementation for Preview the Calibration result with captured
 * data
 *
 */
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
