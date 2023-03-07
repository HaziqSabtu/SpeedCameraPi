/**
 * @file D_Hough.hpp
 * @author Haziq Sabtu (mhaziq.sabtu@gmail.com)
 * @brief Struct for Hough Line Detection Data
 * @version 1.0.0
 * @date 2023-03-07
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef D_HOUGH_HPP
#define D_HOUGH_HPP

#include <Utils/Struct/D_Line.hpp>

namespace Detection {
struct HoughData {
    cv::Mat canny;
    std::vector<Detection::Line> lines;

    HoughData(cv::Mat canny, std::vector<Detection::Line> lines);

    HoughData();
};
} // namespace Detection

#endif