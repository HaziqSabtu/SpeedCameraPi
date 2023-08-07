#pragma once

#include "Utils/Struct/D_Line.hpp"
#include <opencv2/core/core.hpp>
#include <vector>

class RansacLine {
  private:
    int numIterations;
    int minPoints;
    double threshold;

    int bestInliers;
    double confidence;

  public:
    RansacLine();
    RansacLine(int numIterations, int minPoints, double threshold);

    Detection::Line run(cv::Mat &src);

    std::vector<cv::Point> maskToPoint(cv::Mat &mask);

    int countInliers(std::vector<cv::Point> &points, Detection::Line &line);

    // accessors
  public:
    void setNumIterations(int numIterations);

    void setMinPoints(int minPoints);

    void setThreshold(double threshold);

    int getNumIterations() const;

    int getMinPoints() const;

    double getThreshold() const;
};
