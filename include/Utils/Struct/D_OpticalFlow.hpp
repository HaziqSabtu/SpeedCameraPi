/**
 * @file D_OpticalFlow.hpp
 * @author Haziq Sabtu (mhaziq.sabtu@gmail.com)
 * @brief Struct for Optical Flow Data
 * @version 1.0.0
 * @date 2023-03-07
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef D_OPTICALFLOW_HPP
#define D_OPTICALFLOW_HPP

#include <opencv2/opencv.hpp>

namespace Detection {
struct OpticalFlowData {
    std::vector<cv::Point2f> points;

    OpticalFlowData(std::vector<cv::Point2f> points);

    OpticalFlowData();
};
} // namespace Detection

#endif