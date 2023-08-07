#include <Algorithm/ransac_line/RansacLine.hpp>

#include <iostream>
#include <opencv2/core/hal/interface.h>
#include <opencv2/core/types.hpp>

RansacLine::RansacLine() {}

RansacLine::RansacLine(int numIterations, int minPoints, double threshold)
    : numIterations(numIterations), minPoints(minPoints), threshold(threshold) {
}

Detection::Line RansacLine::run(cv::Mat &src) {
    std::vector<cv::Point> points = maskToPoint(src);

    if (points.size() < minPoints) {
        return Detection::Line();
    }

    Detection::Line bestLine;
    bestInliers = 0;
    confidence = 0;

    for (int i = 0; i < numIterations; i++) {
        Detection::Line line(points[rand() % points.size()],
                             points[rand() % points.size()]);

        int inliers = countInliers(points, line);

        if (inliers > bestInliers) {
            bestLine = line;
            bestInliers = inliers;
            confidence =
                1.0 - pow(1.0 - (double)bestInliers / points.size(), 3);
        }
    }

    return bestLine;
}

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

int RansacLine::countInliers(std::vector<cv::Point> &points,
                             Detection::Line &line) {
    int inliers = 0;
    for (cv::Point &p : points) {
        if (line.Distance(p) < threshold) {
            inliers++;
        }
    }
    return inliers;
}

void RansacLine::setNumIterations(int numIterations) {
    this->numIterations = numIterations;
}

void RansacLine::setMinPoints(int minPoints) { this->minPoints = minPoints; }

void RansacLine::setThreshold(double threshold) { this->threshold = threshold; }

int RansacLine::getNumIterations() const { return numIterations; }

int RansacLine::getMinPoints() const { return minPoints; }

double RansacLine::getThreshold() const { return threshold; }
