#ifndef SIFTDETECTION_H
#define SIFTDETECTION_H

#include "DescriptorMatcher.hpp"
#include "Homography.hpp"
#include <Utils/fileWR.hpp>


#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/xfeatures2d.hpp>

class SIFTDetection {
  public:
    /* const */
    int minHessian = 400;
    int FLANN_INDEX_KDTREE = 1;

    cv::Mat descriptors1;
    cv::Mat descriptors2;
    cv::Mat siftResult;
    cv::Mat homographyMatrix;
    cv::Mat transform;
    cv::Mat fillOutput;
    cv::Ptr<cv::SIFT> detector;

    std::vector<cv::KeyPoint> keyPoints1;
    std::vector<cv::KeyPoint> keyPoints2;

    std::vector<cv::Point2f> obj;
    std::vector<cv::Point2f> scene;

    std::vector<cv::DMatch> filterKP;
    std::vector<std::vector<cv::DMatch>> matchKP;

  public:
    SIFTDetection(/* args */);
    ~SIFTDetection();
    void run(cv::Mat &image1, cv::Mat &image2);
    void processImageData(std::vector<ImgData> &imgData);
    void clearVector();
    cv::Mat getFillOutput();
    cv::Mat getTransform();
};

#endif