#ifndef SPEED_CALCULATION_HPP
#define SPEED_CALCULATION_HPP

#include <Utils/fileWR.hpp>
#include <chrono>
#include <opencv2/core.hpp>
#include <wx/log.h>

struct SpeedData {
    cv::Mat image;
    std::chrono::high_resolution_clock::time_point time;
    std::vector<cv::Point2f> points;

    cv::Point2f BottomLine() {
        // same Implementation as in ObjectDetection
        std::vector<cv::Point2f> tmp;
        tmp.assign(points.begin(), points.end());
        std::sort(tmp.begin(), tmp.end(),
                  [](cv::Point2f a, cv::Point2f b) { return a.y > b.y; });
        return tmp.front();
    }
};

class SpeedCalculation {
  public:
    SpeedCalculation(int imageWidth);

    void runCalculation(std::vector<SpeedData> speedData);

    static std::vector<SpeedData>
    toSpeedData(std::vector<ImgData> &imgData,
                std::vector<std::vector<cv::Point2f>> &points);
    void SetLine(std::vector<cv::Vec4i> l);
    double distanceFromCamera(float pixelWidth);

    static cv::Point2f intersection(float y, cv::Vec4i b);
    static cv::Point2f intersection(cv::Vec4f a, cv::Vec4f b);
    static double
    calcSpeed(double prevDist, double curDist,
              std::chrono::high_resolution_clock::time_point prevTime,
              std::chrono::high_resolution_clock::time_point curTime);

  private:
    std::vector<cv::Vec4i> line;

  private:
    const int imageWidth;
    const double LANE_WIDTH = 371.00; // in mm
    // const double LANE_WIDTH = 0.37100; // in meters

    // Camera Parameters
    const double SensorWidth = 3.68;  // in mm
    const double SensorHeight = 2.76; // in mm
    const double FocalLength = 3.04;  // in mm

    // set default values for prevTime -1
    double prevDistFromCamera = -1;
    std::chrono::high_resolution_clock::time_point prevTime;
};

#endif