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

#ifndef IMAGE_UTILS_HPP
#define IMAGE_UTILS_HPP

#include <Utils/DataStruct.hpp>
#include <ctime>
#include <opencv2/opencv.hpp>
#include <wx/log.h>
#include <wx/wx.h>

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
void RotateImage(std::vector<ImageData> &imgData, int angle);
double TrimmedMean(const std::vector<double> &data, double percentage);
} // namespace Utils

#endif