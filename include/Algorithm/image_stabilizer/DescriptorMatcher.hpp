/**
 * @file DescriptorMatcher.hpp
 * @author Haziq Sabtu (mhaziq.sabtu@gmail.com)
 * @brief  A class for performing feature matching using OpenCV's
 * DescriptorMatcher class.
 *
 * @version 1.0.0
 * @date 2023-03-01
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef DESCRIPTOR_MATCHER_H
#define DESCRIPTOR_MATCHER_H

#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/flann.hpp>
#include <opencv2/xfeatures2d.hpp>

class DESCRIPTORMATCHER {
  public:
    static void BruteForceMatcher(cv::Mat &query, cv::Mat &target,
                                  std::vector<cv::DMatch> &matches,
                                  std::string type, int normType = 0);

    static void getNormType(int normType, cv::NormTypes &normTypes,
                            std::string &typeName);

    static void BruteForceMatcher(cv::Mat &query, cv::Mat &target,
                                  std::vector<std::vector<cv::DMatch>> &matches,
                                  std::string type, int normType = 0);

    static void FlannBasedMatcher(cv::Mat &query, cv::Mat &target,
                                  std::vector<std::vector<cv::DMatch>> &matches,
                                  std::string type);

    // Run Lowe's Ratio Test to remove bad matches on KNN.
    static void
    FilterKeyPoints(std::vector<std::vector<cv::DMatch>> &knnMatches,
                    std::vector<cv::DMatch> &goodMatch, double RATIO = 0.3);
};
#endif
