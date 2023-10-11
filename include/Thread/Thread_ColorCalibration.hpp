#pragma once

#include "Algorithm/Struct/D_Line.hpp"
#include "Algorithm/hsv_filter/BFS.hpp"
#include "Algorithm/hsv_filter/HSVFilter.hpp"
#include "Algorithm/ransac_line/RansacLine.hpp"
#include "Model/CalibrationData.hpp"
#include "Thread/Thread_Base.hpp"
#include "Thread/Thread_ID.hpp"
#include <Event/Event_Calibration.hpp>
#include <Event/Event_UpdatePreview.hpp>

#include <Utils/Camera/CameraBase.hpp>

#include <condition_variable>
#include <memory>
#include <opencv2/core/types.hpp>
#include <string>

#include <opencv2/opencv.hpp>

#include <wx/thread.h>

enum ColorCalibrationType { COLOR_CALIBRATION_BLUE, COLOR_CALIBRATION_YELLOW };

class ColorCalibrationThread : public BaseThread,
                               public PreviewableThread,
                               public CameraAccessor {
  public:
    ColorCalibrationThread(wxEvtHandler *parent, CameraPtr &camera);
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

    HSVFilter hsvFilter;
    BFS bfs;

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