#ifndef SPEED_CALCULATION_HPP
#define SPEED_CALCULATION_HPP

#include <Utils/DataStruct.hpp>
#include <Utils/ImageUtils.hpp>
#include <Utils/Struct/D_Line.hpp>
#include <chrono>
#include <opencv2/core.hpp>
#include <wx/log.h>

class SpeedCalculation {
  public:
    // SpeedCalculation(int imageWidth);
    SpeedCalculation();

    void runCalculation(std::vector<SpeedData> speedData);
    void runCalculation(std::vector<ImageData> *imgData,
                        std::vector<Detection::Line> &lines);

    static std::vector<SpeedData>
    toSpeedData(std::vector<ImageData> &imgData,
                std::vector<std::vector<cv::Point2f>> &points);
    void SetImageWidth(int w);
    void SetLine(std::vector<cv::Vec4i> l);
    double distanceFromCamera(float pixelWidth);
    double GetAvgSpeed();
    double rawAvgSpeed(std::vector<double> &speeds);

    static cv::Point2f intersection(float y, cv::Vec4i b);
    static cv::Point2f intersection(cv::Vec4f a, cv::Vec4f b);
    static double
    calcSpeed(double prevDist, double curDist,
              std::chrono::high_resolution_clock::time_point prevTime,
              std::chrono::high_resolution_clock::time_point curTime);

  private:
    std::vector<cv::Vec4i> line;
    std::vector<double> speeds;
    double avgSpeed = -1;

  private:
    int imageWidth;
    const double LANE_WIDTH = 360.00; // in mm
    // const double LANE_WIDTH = 0.37100; // in meters

    // Camera Parameters
    const double SensorWidth = 3.68; // in mm
    // const double SensorHeight = 2.76; // in mm
    const double FocalLength = 3.04; // in mm

    // set default values for prevTime -1
    double prevDistFromCamera = -1;
    std::chrono::high_resolution_clock::time_point prevTime;
};

#endif