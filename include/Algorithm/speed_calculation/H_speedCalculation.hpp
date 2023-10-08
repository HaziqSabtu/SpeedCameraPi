#pragma once

#include "Algorithm/speed_calculation/speedCalculation.hpp"
#include "Model/SessionData.hpp"
#include <Algorithm/Struct/D_Line.hpp>
#include <Utils/CommonUtils.hpp>
#include <chrono>
#include <opencv2/core.hpp>

enum MovementDirection { MOVING_DOWNWARDS, MOVING_UPWARDS };

class DistanceSpeedCalculation : public SpeedCalculator {
  public:
    DistanceSpeedCalculation();

    void runCalculation(std::vector<cv::Mat> &images,
                        std::vector<HPTime> &times,
                        std::vector<cv::Rect> trackedRoi,
                        std::vector<Line> &lines);

    double GetSpeed();

    SpeedCalculationType GetType() const;

    void setObjectLength(double length);
    double getObjectLength() const;

  private:
    void analyzeDirection(std::vector<cv::Rect> &trackedRoi);
    void assignLines(std::vector<Line> &lines);

    bool isCrossingLine(Line &line, cv::Rect &rect);

    bool isTimeDefault(HPTime &time);

  private:
    const SpeedCalculationType type = SPEED_CALCULATION_DISTANCE;

    double objectLength = 2000; // in mm

    // initialize to 1st Jan 1970 (Default value)
    HPTime startTime = std::chrono::system_clock::from_time_t(0);
    HPTime endTime = std::chrono::system_clock::from_time_t(0);

    Line startLine;
    Line endLine;

    MovementDirection direction;
};