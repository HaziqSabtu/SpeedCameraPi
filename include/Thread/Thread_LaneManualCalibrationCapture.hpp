#pragma once

#include <Thread/Thread_LaneManualCalibrationCamera.hpp>

class LaneManualCalibrationCaptureThread
    : public BaseLaneManualCalibrationThread,
      public ImageSizeDataThread {
  public:
    LaneManualCalibrationCaptureThread(wxEvtHandler *parent, DataPtr data);
    ~LaneManualCalibrationCaptureThread();

    CalibrationData getCalibrationData() override;

    ThreadID getID() const override;

    Line getRealRightLine() override;
    Line getRealLeftLine() override;

  protected:
    virtual ExitCode Entry() override;

  private:
    const ThreadID threadID = ThreadID::THREAD_LANE_MANUAL_CALIBRATION_CAPTURE;
};