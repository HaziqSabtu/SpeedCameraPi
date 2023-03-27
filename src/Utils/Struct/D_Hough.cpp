/**
 * @file D_Hough.cpp
 * @author Haziq Sabtu (mhaziq.sabtu@gmail.com)
 * @brief Struct for Hough Line Detection Data
 * @version 1.0.0
 * @date 2023-03-07
 *
 * @copyright Copyright (c) 2023
 *
 */
#include <Utils/Struct/D_Hough.hpp>

namespace Detection {

/**
 * @brief Construct a new Hough Data:: Hough Data object
 *
 */
HoughData::HoughData() {}

/**
 * @brief Construct a new Hough Data:: Hough Data object
 *
 * @param canny cv::Mat image of canny edge detection
 * @param lines std::vector<Detection::Line> lines detected
 */
HoughData::HoughData(cv::Mat canny, std::vector<Detection::Line> lines)
    : canny(canny), lines(lines) {}
} // namespace Detection