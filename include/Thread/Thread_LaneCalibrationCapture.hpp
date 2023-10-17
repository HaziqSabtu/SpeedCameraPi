#pragma once

#include <Thread/Thread_LaneCalibrationCamera.hpp>

#include <Utils/Algorithm/AlgorithmFactory.hpp>

#include <Utils/Camera/CameraBase.hpp>

class LaneCalibrationCaptureThread : public BaseLaneCalibrationThread,
                                     public ImageSizeDataThread {
  public:
    LaneCalibrationCaptureThread(wxEvtHandler *parent, DataPtr data,
                                 HSVFilterPtr hsvFilter, BFSPtr bfs,
                                 RansacLinePtr ransac);
    ~LaneCalibrationCaptureThread();

    ThreadID getID() const override;

    CalibrationData getCalibrationData() override;

    Line getRealLeftLine() override;
    Line getRealRightLine() override;

  protected:
    virtual ExitCode Entry() override;

  private:
    const ThreadID threadID = ThreadID::THREAD_LANE_CALIBRATION_CAPTURE;
};