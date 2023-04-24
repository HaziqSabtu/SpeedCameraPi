/**
 * @file FeatureDetector.hpp
 * @author Haziq Sabtu (mhaziq.sabtu@gmail.com)
 * @brief Helper Class for detecting and matching features between two images
 * and alligning them
 * @version 1.0.0
 * @date 2023-03-01
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef FeatureDetector_HPP
#define FeatureDetector_HPP

#include <Algorithm/image_allign/DescriptorMatcher.hpp>
#include <Algorithm/image_allign/Enum.hpp>
#include <Algorithm/image_allign/Homography.hpp>
#include <Utils/DataStruct.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/xfeatures2d.hpp>

/**
 * @brief Helper Class for detecting and matching features between two images
 * and alligning them
 */
class FeatureDetector {

  public:
    FeatureDetector(DetectorType type);
    FeatureDetector();
    void allign(cv::Mat &image1, cv::Mat &image2);
    cv::Mat GetMatchImage(cv::Mat &image1, cv::Mat &image2);
    cv::Mat GetHomographyMatrix();
    cv::Mat GetAllignedImage();
    cv::Mat GetAllignedImage(cv::Mat &bg);

  private:
    cv::Ptr<cv::SIFT> detector;
    DetectorType detectorType;
    void clearVector();

    // ORB Parameters
    // TODO: DOCS -> SET ACCESSORS METHODS
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
    cv::Mat descriptors1;
    cv::Mat descriptors2;
    cv::Mat homographyMatrix;
    cv::Mat transform;

    std::vector<cv::KeyPoint> keyPoints1;
    std::vector<cv::KeyPoint> keyPoints2;

    std::vector<cv::DMatch> filterKP;
    std::vector<std::vector<cv::DMatch>> matchKP;
};

/**
 * @brief Inline function to clear all vectors from previous run
 *
 */
inline void FeatureDetector::clearVector() {
    filterKP.clear();
    matchKP.clear();
    keyPoints1.clear();
    keyPoints2.clear();
}

/**
 * @example ImageAlignment.cpp
 * @brief Example of how to use FeatureDetector class
 */

#endif