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
};

class SpeedCalculation {
  public:
    SpeedCalculation();

    void runCalculation(std::vector<SpeedData> speedData);

    static std::vector<SpeedData>
    toSpeedData(std::vector<ImgData> &imgData,
                std::vector<std::vector<cv::Point2f>> &points);
    void SetLine(std::vector<cv::Vec4i> l);

  private:
    std::vector<cv::Vec4i> line;
};

#endif