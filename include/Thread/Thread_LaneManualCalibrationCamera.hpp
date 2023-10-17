#pragma once

#include <Thread/Thread_Base.hpp>

#include <Utils/Camera/CameraBase.hpp>

enum ManualDirection { MANUAL_LEFT, MANUAL_RIGHT };

class BaseLaneManualCalibrationThread : public BaseThread,
                                        public PreviewableThread {
  public:
    BaseLaneManualCalibrationThread(wxEvtHandler *parent, DataPtr data);
    ~BaseLaneManualCalibrationThread();

    virtual CalibrationData getCalibrationData() = 0;

    void setPoint1(cv::Point point);
    void setPoint2(cv::Point point);
    void setPoint2AndExtend(cv::Point point);

    void setDirection(ManualDirection direction);
    ManualDirection getDirection();

    void setRightLine(Line line);
    Line getRightLine();
    virtual Line getRealRightLine() = 0;

    void setLeftLine(Line line);
    Line getLeftLine();
    virtual Line getRealLeftLine() = 0;

  protected:
    std::mutex m_mutex;
    Line rightLine;
    Line leftLine;

    ManualDirection direction = MANUAL_LEFT;

  protected:
    void updateRightLine(Line line);
    void updateLeftLine(Line line);

    bool isLineValid(Line &line);
};

class ManualCalibrationCameraThread : public BaseLaneManualCalibrationThread,
                                      public CameraAccessor,
                                      public ImageSizeCameraThread {
  public:
    ManualCalibrationCameraThread(wxEvtHandler *parent, CameraPtr &camera);
    ~ManualCalibrationCameraThread();

    CalibrationData getCalibrationData() override;

    ThreadID getID() const override;

    Line getRealRightLine() override;
    Line getRealLeftLine() override;

  protected:
    virtual ExitCode Entry() override;

  private:
    const ThreadID threadID = ThreadID::THREAD_LANE_MANUAL_CALIBRATION_CAMERA;
};