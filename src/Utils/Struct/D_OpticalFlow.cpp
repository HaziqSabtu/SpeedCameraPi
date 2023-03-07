/**
 * @file D_OpticalFlow.cpp
 * @author Haziq Sabtu (mhaziq.sabtu@gmail.com)
 * @brief Struct for Optical Flow Data
 * @version 1.0.0
 * @date 2023-03-07
 *
 * @copyright Copyright (c) 2023
 *
 */
#include <Utils/Struct/D_OpticalFlow.hpp>

namespace Detection {
OpticalFlowData::OpticalFlowData(std::vector<cv::Point2f> points)
    : points(points) {}

OpticalFlowData::OpticalFlowData() {}
} // namespace Detection
