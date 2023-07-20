#pragma once

#include "Utils/Struct/D_Line.hpp"
#include <opencv2/core/core.hpp>
#include <vector>

class RansacLine {
  private:
    const int numIterations;
    const int minPoints;
    const double threshold;

    int bestInliers;
    double confidence;

  public:
    RansacLine(int numIterations, int minPoints, double threshold);

    Detection::Line run(cv::Mat &src);

    std::vector<cv::Point> maskToPoint(cv::Mat &mask);

    int countInliers(std::vector<cv::Point> &points, Detection::Line &line);
};
