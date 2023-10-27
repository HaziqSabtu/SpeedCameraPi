#include <Algorithm/ransac_line/RansacLine.hpp>

#include <iostream>
#include <opencv2/core/hal/interface.h>
#include <opencv2/core/types.hpp>

/**
 * @brief Construct a new Ransac Line:: Ransac Line object
 *
 */
RansacLine::RansacLine() {}

/**
 * @brief Construct a new Ransac Line:: Ransac Line object
 *
 * @param numIterations number of iterations required to find the best line
 * @param minPoints minimum number of points inside the mask to find a line
 * @param threshold maximum distance between a point and a line to be considered
 * an inlier
 */
RansacLine::RansacLine(int numIterations, int minPoints, double threshold)
    : numIterations(numIterations), minPoints(minPoints), threshold(threshold) {
}

/**
 * @brief Find the best line in a binary image
 *
 * @param src binary image (or mask image with 0 and 255 values)
 * @note The image must be CV_8UC1
 * @return Line best line found
 */
Line RansacLine::run(cv::Mat &src) {

    // convert mask to points array
    std::vector<cv::Point> points = maskToPoint(src);

    // check if there are enough points
    if (points.size() < minPoints) {
        return Line();
    }

    Line bestLine;
    bestInliers = 0;
    confidence = 0;

    // run ransac
    for (int i = 0; i < numIterations; i++) {

        // get two random points and create a line
        Line line(points[rand() % points.size()],
                  points[rand() % points.size()]);

        // count inliers
        int inliers = countInliers(points, line);

        // update best line
        if (inliers > bestInliers) {
            bestLine = line;
            bestInliers = inliers;
            confidence =
                1.0 - pow(1.0 - (double)bestInliers / points.size(), 3);
        }
    }

    return bestLine;
}

// convert mask to points array
std::vector<cv::Point> RansacLine::maskToPoint(cv::Mat &mask) {
    CV_Assert(mask.depth() == CV_8UC1);

    std::vector<cv::Point> points;

    int channels = mask.channels();
    int nRows = mask.rows;
    int nCols = mask.cols * channels;

    int i, j;
    uchar *p;

    for (i = 0; i < nRows; ++i) {
        p = mask.ptr<uchar>(i);
        for (j = 0; j < nCols; ++j) {
            if (p[j] == 255) {
                points.push_back(cv::Point(j, i));
            }
        }
    }
    return points;
}

// count inliers
int RansacLine::countInliers(std::vector<cv::Point> &points, Line &line) {
    int inliers = 0;
    for (cv::Point &p : points) {
        if (line.Distance(p) < threshold) {
            inliers++;
        }
    }
    return inliers;
}

/**
 * @brief Set the number of iterations required to find the best line
 *
 * @param numIterations number of iterations
 */
void RansacLine::setNumIterations(int numIterations) {
    this->numIterations = numIterations;
}

/**
 * @brief Set the minimum number of points inside the mask to find a line
 *
 * @param minPoints minimum number of points
 */
void RansacLine::setMinPoints(int minPoints) { this->minPoints = minPoints; }

/**
 * @brief Set the maximum distance between a point and a line to be considered
 * an inlier
 *
 * @param threshold maximum distance
 */
void RansacLine::setThreshold(double threshold) { this->threshold = threshold; }

/**
 * @brief Get the number of iterations required to find the best line
 *
 * @return int number of iterations
 */
int RansacLine::getNumIterations() const { return numIterations; }

/**
 * @brief Get the minimum number of points inside the mask to find a line
 *
 * @return int minimum number of points
 */
int RansacLine::getMinPoints() const { return minPoints; }

/**
 * @brief Get the maximum distance between a point and a line to be considered
 * an inlier
 *
 * @return double maximum distance
 */
double RansacLine::getThreshold() const { return threshold; }
