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

/**
 * @brief Calculate the time difference in milliseconds
 *
 * @param time1 First time point
 * @param time2 Second time point
 * @return double difference in milliseconds
 */
double TimeDiffInMilli(std::chrono::high_resolution_clock::time_point time1,
                       std::chrono::high_resolution_clock::time_point time2);

/**
 * @brief Get the current date and time in string format
 *
 * @return std::string date and time in string format
 */
std::string dateToString();

/**
 * @brief Get the File Extension object
 *
 * @param path Path to the file
 * @return FileExtension File extension
 */
FileExtension GetFileExtension(std::string &path);

/**
 * @brief Rotate image at a certain angle
 *
 * @param imgData vector of cv::Mat
 * @param angle angle to rotate
 */
void RotateImage(std::vector<cv::Mat> &imgData, int angle);

/**
 * @brief Perform trim mean of data
 *
 * @param data vector of double of the data
 * @param percentage percentage of data to be trimmed
 * @return double trimmed mean
 */
double TrimmedMean(const std::vector<double> &data, double percentage);

/**
 * @brief Get the relative point on different image size
 *
 * @param src source image
 * @param target target image
 * @param point point to be converted
 * @return cv::Point relative point
 */
cv::Point getRelativePoint(const cv::Mat &src, const cv::Mat &target,
                           const cv::Point &point);

/**
 * @brief Scale rect on different image size
 *
 * @param rect the rect to be scaled
 * @param src source image size
 * @param dst target image size
 * @return cv::Rect scaled rect
 */
cv::Rect scaleRect(const cv::Rect &rect, cv::Size src, cv::Size dst);

/**
 * @brief Generate random ID
 *
 * @return int random ID
 */
int generateRandomID();

/**
 * @brief Check if cv::Mat is equal
 *
 * @param img1 cv::Mat object
 * @param img2 cv::Mat object
 * @return true is same
 * @return false if same
 */
bool isCvMatSame(const cv::Mat &img1, const cv::Mat &img2);

/**
 * @brief Check if cv::Mat is equal at random points
 *
 * @param img1 cv::Mat object
 * @param img2 cv::Mat object
 * @param points number of points to be checked
 * @return true is same
 * @return false if same
 */
bool isCvMatSameRandom(const cv::Mat &img1, const cv::Mat &img2, int points);

/**
 * @brief Check if the range is calibrated
 *
 * @param range range to be checked
 * @return true
 * @return false
 */
bool isRangeCalibrated(const std::pair<cv::Scalar, cv::Scalar> &range);

} // namespace Utils
