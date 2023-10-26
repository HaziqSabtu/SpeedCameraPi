#pragma once

#include <Thread/Thread_Base.hpp>

#include <Utils/Camera/CameraBase.hpp>

/**
 * @brief Enum for the Distance Direction, Used within the
 * BaseDistanceCalibrationThread
 *
 */
enum DistanceDirection { DISTANCE_TOP, DISTANCE_BOTTOM };

/**
 * @brief Base Class for the Distance Calibration
 *
 */
class BaseDistanceCalibrationThread : public BaseThread,
                                      public PreviewableThread {
  public:
    BaseDistanceCalibrationThread(wxEvtHandler *parent, DataPtr data);
    ~BaseDistanceCalibrationThread();

    virtual CalibrationData getCalibrationData() = 0;

    void setPointAndExtend(cv::Point point);

    void setDirection(DistanceDirection direction);
    DistanceDirection getDirection();

    void setTopLine(Line line);
    Line getTopLine();
    virtual Line getRealTopLine() = 0;

    void setBottomLine(Line line);
    Line getBottomLine();
    virtual Line getRealBottomLine() = 0;

  protected:
    std::mutex m_mutex;
    Line topLine;
    Line bottomLine;

    DistanceDirection direction = DISTANCE_TOP;

  protected:
    void updateTopLine(Line line);
    void updateBottomLine(Line line);

    bool isLineValid(Line &line);
};

/**
 * @brief Thread implementation for the Distance Calibration with camera
 *
 */
class DistanceCalibrationCameraThread : public BaseDistanceCalibrationThread,
                                        public CameraAccessor,
                                        public ImageSizeCameraThread {
  public:
    DistanceCalibrationCameraThread(wxEvtHandler *parent, CameraPtr &camera);
    ~DistanceCalibrationCameraThread();

    CalibrationData getCalibrationData() override;

    ThreadID getID() const override;

    Line getRealTopLine() override;
    Line getRealBottomLine() override;

  protected:
    virtual ExitCode Entry() override;

  private:
    const ThreadID threadID = ThreadID::THREAD_DISTANCE_CALIBRATION_CAMERA;
};