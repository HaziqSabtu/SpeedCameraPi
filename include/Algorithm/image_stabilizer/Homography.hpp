/**
 * @file Homography.hpp
 * @author Haziq Sabtu (mhaziq.sabtu@gmail.com)
 * @brief Class for Running Homography based on the result from Feature
 * Detection
 * @version 1.0.0
 * @date 2023-03-01
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef HOMOGRAPHY_H
#define HOMOGRAPHY_H

#include <iostream>
#include <opencv2/calib3d.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>

class HOMOGRAPHY {
  public:
    static void FindHomography(std::vector<cv::KeyPoint> keypoints_obj,
                               std::vector<cv::KeyPoint> keypoints_scene,
                               std::vector<cv::DMatch> &matches,
                               std::vector<cv::Point2f> &obj,
                               std::vector<cv::Point2f> &scene, cv::Mat &H,
                               std::string type);

    static void PerscpectiveTransform(cv::Mat &target, cv::Mat &transform,
                                      cv::Mat &M);

    static void FillTransform(cv::Mat &bg, cv::Mat &target, cv::Mat &M,
                              cv::Mat &result);
};
#endif

// todo: add RANSAC alternative