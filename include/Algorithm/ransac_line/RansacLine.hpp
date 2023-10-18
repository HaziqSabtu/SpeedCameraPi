#pragma once

#include "Algorithm/Struct/D_Line.hpp"
#include <opencv2/core/core.hpp>
#include <vector>

/**
 * @brief Class to find a line in a binary image using RANSAC
 * (example)[https://cs.gmu.edu/~kosecka/cs482/lect-fitting.pdf]
 *
 */
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

    Line run(cv::Mat &src);

  private:
    std::vector<cv::Point> maskToPoint(cv::Mat &mask);

    int countInliers(std::vector<cv::Point> &points, Line &line);

    // accessors
  public:
    void setNumIterations(int numIterations);

    void setMinPoints(int minPoints);

    void setThreshold(double threshold);

    int getNumIterations() const;

    int getMinPoints() const;

    double getThreshold() const;
};
