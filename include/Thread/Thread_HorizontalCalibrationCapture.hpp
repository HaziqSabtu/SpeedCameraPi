#pragma once

#include "Thread/Thread_HorizontalCalibrationCamera.hpp"

class HorizontalCalibrationCaptureThread
    : public BaseHorizontalCalibrationThread,
      public ImageSizeDataThread {
  public:
    HorizontalCalibrationCaptureThread(wxEvtHandler *parent, DataPtr data);
    ~HorizontalCalibrationCaptureThread();

    CalibrationData getCalibrationData() override;

    ThreadID getID() const override;

    Line getRealTopLine() override;
    Line getRealBottomLine() override;

  protected:
    virtual ExitCode Entry() override;

  private:
    const ThreadID threadID = ThreadID::THREAD_HORIZONTAL_CALIBRATION_CAPTURE;
};