/**
 * @file ImageUtils.hpp
 * @author Haziq Sabtu (mhaziq.sabtu@gmail.com)
 * @brief Utils Class
 * @version 1.0.0
 * @date 2023-03-18
 *
 * @copyright Copyright (c) 2023
 *
 */

#pragma once

#include <ctime>
#include <opencv2/core/types.hpp>
#include <opencv2/opencv.hpp>

/**
 * @brief Utils Class
 *
 */
namespace Utils {
enum FileExtension { BIN, H264, UNSUPPORTED };

double TimeDiff(std::chrono::high_resolution_clock::time_point time1,
                std::chrono::high_resolution_clock::time_point time2);

std::string dateToString();

FileExtension GetFileExtension(std::string &path);

void RotateImage(std::vector<cv::Mat> &imgData, int angle);

double TrimmedMean(const std::vector<double> &data, double percentage);

cv::Point getRelativePoint(const cv::Mat &src, const cv::Mat &target,
                           const cv::Point &point);

cv::Rect scaleRect(const cv::Rect &rect, cv::Size src, cv::Size dst);

int generateRandomID();

bool isCvMatSame(const cv::Mat &img1, const cv::Mat &img2);

bool isCvMatSameRandom(const cv::Mat &img1, const cv::Mat &img2, int points);

bool isRangeCalibrated(const std::pair<cv::Scalar, cv::Scalar> &range);

} // namespace Utils
