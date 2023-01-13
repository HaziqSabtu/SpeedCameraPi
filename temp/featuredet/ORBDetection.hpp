#ifndef ORBDETECTION_H
#define ORBDETECTION_H

#include "DescriptorMatcher.hpp"
#include "Homography.hpp"

#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/xfeatures2d.hpp>

class ORBDetection {
  private:
    // ORB Parameters
    int nfeatures = 2000;
    float scaleFactor = 1.2f;
    int nlevels = 8;
    int edgeThreshold = 31;
    int firstLevel = 0;
    int WTA_K = 2;
    int patchSize = 31;
    int fastThreshold = 20;
    cv::ORB::ScoreType scoreType = cv::ORB::HARRIS_SCORE;

  private:
    /* data */
    cv::Mat descriptors1;
    cv::Mat descriptors2;
    cv::Mat siftResult;
    cv::Mat homographyMatrix;
    cv::Mat transform;
    cv::Mat fillOutput;
    cv::Ptr<cv::ORB> detector;

    std::vector<cv::KeyPoint> keyPoints1;
    std::vector<cv::KeyPoint> keyPoints2;

    std::vector<cv::Point2f> obj;
    std::vector<cv::Point2f> scene;

    std::vector<cv::DMatch> filterKP;
    std::vector<std::vector<cv::DMatch>> matchKP;

  public:
    ORBDetection(/* args */);
    ~ORBDetection();
    void run(cv::Mat &image1, cv::Mat &image2);
};

#endif