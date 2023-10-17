#pragma once

#include <Thread/Thread_Base.hpp>

#include <Utils/Algorithm/AlgorithmFactory.hpp>
#include <Utils/Camera/CameraBase.hpp>

#include <condition_variable>

enum ColorCalibrationType { COLOR_CALIBRATION_BLUE, COLOR_CALIBRATION_YELLOW };

class ColorCalibrationThread : public BaseThread,
                               public PreviewableThread,
                               public CameraAccessor {
  public:
    ColorCalibrationThread(wxEvtHandler *parent, DataPtr data,
                           CameraPtr &camera, HSVFilterPtr hsvFilter,
                           BFSPtr bfs);
    ~ColorCalibrationThread();

    ThreadID getID() const override;

    void setPoint(cv::Point point);
    cv::Point getPoint();

    std::pair<cv::Scalar, cv::Scalar> getBlueRange();
    std::pair<cv::Scalar, cv::Scalar> getYellowRange();

    void setColorCalibrationType(ColorCalibrationType type);
    ColorCalibrationType getColorCalibrationType();

    void removeBlueRange();
    void removeYellowRange();

    bool isBlueRangeDefined();
    bool isYellowRangeDefined();

  protected:
    virtual ExitCode Entry() override;

  private:
    const ThreadID threadID = ThreadID::THREAD_COLOR_CALIBRATION;

    HSVFilterPtr hsvFilter;
    BFSPtr bfs;

    std::recursive_mutex m_mutex;
    cv::Point point = cv::Point(-1, -1);
    cv::Point processedPoint = cv::Point(-1, -1);

    std::pair<cv::Scalar, cv::Scalar> blueRange =
        std::make_pair(cv::Scalar(0, 0, 0), cv::Scalar(0, 0, 0));
    std::pair<cv::Scalar, cv::Scalar> yellowRange =
        std::make_pair(cv::Scalar(0, 0, 0), cv::Scalar(0, 0, 0));

    ColorCalibrationType type = ColorCalibrationType::COLOR_CALIBRATION_BLUE;

    cv::Scalar blue = cv::Scalar(255, 0, 0, 255);
    cv::Scalar yellow = cv::Scalar(0, 255, 255, 255);

    bool updateStateSwitch = false;

  private:
    cv::Point grabPoint();

    void updateBlueRange(std::pair<cv::Scalar, cv::Scalar> range);
    void updateYellowRange(std::pair<cv::Scalar, cv::Scalar> range);
};