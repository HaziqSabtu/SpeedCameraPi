/**
 * @file speedCalculation.hpp
 * @author Haziq Sabtu (mhaziq.sabtu@gmail.com)
 * @brief Class for Calculating Speed of Object from Image using Optical Flow
 * @version 1.0.0
 * @date 2023-03-18
 *
 * @copyright Copyright (c) 2023
 *
 */
#ifndef SPEED_CALCULATION_HPP
#define SPEED_CALCULATION_HPP

#include "Model/SessionData.hpp"
#include <Algorithm/Struct/D_Line.hpp>
#include <Utils/CommonUtils.hpp>
#include <chrono>
#include <opencv2/core.hpp>

/**
 * @brief Class for Calculating Speed of Tracked Objects
 *
 */
class SpeedCalculation {
  public:
    SpeedCalculation();

    void runCalculation(std::vector<cv::Mat> &images,
                        std::vector<HPTime> &times,
                        std::vector<cv::Rect> trackedRoi,
                        std::vector<Line> &lines);

    double GetTrimmedAverageSpeed(int percentage);
    double GetRawAverageSpeed();
    std::vector<double> GetRawSpeed() const;

    double GetSensorWidth() const;
    void SetSensorWidth(double width);

    double GetFocalLength() const;
    void SetFocalLength(double length);

    double GetLaneWidth() const;
    void SetLaneWidth(double width);

    std::vector<double> GetDistanceFromCamera() const;
    std::vector<Line> GetIntersectingLines() const;

  private:
    double distanceFromCameraInMilli(float pixelWidth);

    double calculateSpeed(double prevDist, double curDist, HPTime prevTime,
                          HPTime curTime);

  private:
    int imageWidth;
    double sensorWidth = 3.68; // in mm
    double focalLength = 3.04; // in mm
    double laneWidth = 3500;   // in mm

    // set default values for prevTime -1
    double prevDistFromCamera = -1;
    HPTime prevTime;

    std::vector<double> speeds;

    // debugging data
    std::vector<double> distFromCamera;
    std::vector<Line> intersectingLines;
};

#endif