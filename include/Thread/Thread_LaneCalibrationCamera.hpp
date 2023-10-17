#pragma once

#include <Thread/Thread_Base.hpp>

#include <Utils/Algorithm/AlgorithmFactory.hpp>
#include <Utils/Camera/CameraBase.hpp>

class BaseLaneCalibrationThread : public BaseThread, public PreviewableThread {
  public:
    BaseLaneCalibrationThread(wxEvtHandler *parent, DataPtr data,
                              HSVFilterPtr hsvFilter, BFSPtr bfs,
                              RansacLinePtr ransac);
    ~BaseLaneCalibrationThread();

    void setPoint(cv::Point point);
    void clearPoint();

    virtual CalibrationData getCalibrationData() = 0;

    virtual Line getRealRightLine() = 0;
    virtual Line getRealLeftLine() = 0;

  protected:
    HSVFilterPtr hsvFilter;
    BFSPtr bfs;
    RansacLinePtr ransac;

    std::mutex m_mutex;
    cv::Point point;
    Line rightLine; // yellow line
    Line leftLine;  // blue line

  protected:
    void updateRightLine(Line line);
    void updateLeftLine(Line line);

    bool isBothLineValid();
};

class LaneCalibrationCameraThread : public BaseLaneCalibrationThread,
                                    public CameraAccessor,
                                    public ImageSizeCameraThread {
  public:
    LaneCalibrationCameraThread(wxEvtHandler *parent, DataPtr data,
                                CameraPtr &camera, HSVFilterPtr hsvFilter,
                                BFSPtr bfs, RansacLinePtr ransac);
    ~LaneCalibrationCameraThread();

    ThreadID getID() const override;

    CalibrationData getCalibrationData() override;

    Line getRealRightLine() override;
    Line getRealLeftLine() override;

  protected:
    virtual ExitCode Entry() override;

  private:
    const ThreadID threadID = ThreadID::THREAD_LANE_CALIBRATION_CAMERA;
};