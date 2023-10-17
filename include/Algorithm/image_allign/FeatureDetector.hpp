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
#include <opencv2/core/types.hpp>
#include <opencv2/opencv.hpp>
#include <vector>

/**
 * @brief  Class for detecting and matching features between two images
 * and alligning them
 */
class FeatureDetector {

  public:
    FeatureDetector(DetectorType type);
    FeatureDetector();

    void Init(cv::Mat &image1);

    FeatureDetector &operator=(const FeatureDetector &other);

    FeatureDetector clone();

    void Allign(cv::Mat &image2);

    cv::Mat GetMatchImage(cv::Mat &image1, cv::Mat &image2);
    cv::Mat GetHomographyMatrix();
    cv::Mat GetAllignedImage();
    cv::Mat GetAllignedImage(cv::Mat &bg);

  private:
    cv::Ptr<cv::SIFT> detector;
    DetectorType detectorType;
    void clearVector();

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
 * @example ImageAlignment.cpp
 * @brief Example of how to use FeatureDetector class
 */

#endif