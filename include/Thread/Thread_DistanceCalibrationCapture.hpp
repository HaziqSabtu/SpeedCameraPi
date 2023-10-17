#pragma once

#include "Thread/Thread_DistanceCalibrationCamera.hpp"

class DistanceCalibrationCaptureThread : public BaseDistanceCalibrationThread,
                                         public ImageSizeDataThread {
  public:
    DistanceCalibrationCaptureThread(wxEvtHandler *parent, DataPtr data);
    ~DistanceCalibrationCaptureThread();

    CalibrationData getCalibrationData() override;

    ThreadID getID() const override;

    Line getRealTopLine() override;
    Line getRealBottomLine() override;

  protected:
    virtual ExitCode Entry() override;

  private:
    const ThreadID threadID = ThreadID::THREAD_DISTANCE_CALIBRATION_CAPTURE;
};