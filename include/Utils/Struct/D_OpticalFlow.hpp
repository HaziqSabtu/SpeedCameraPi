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
/**
 * @brief Struct for Optical Flow Point
 *
 */
struct OFPoint {
    int id;
    cv::Point2f point;
    float error;

    OFPoint(int id, cv::Point2f point, float error);
};

/**
 * @brief Struct for Optical Flow Data with custom composition of vector
 *
 */
struct OpticalFlowData {
    cv::Mat gray;
    std::vector<Detection::OFPoint> data;

    OpticalFlowData();
    OpticalFlowData(cv::Mat gray);
    OpticalFlowData(cv::Mat gray, std::vector<cv::Point2f> points);
    Detection::OFPoint &operator[](int index);
    int size() const;
    void push(std::vector<cv::Point2f> points);
    void push(OpticalFlowData &OFData, std::vector<cv::Point2f> points,
              std::vector<float> errors, std::vector<uchar> status);
    std::vector<cv::Point2f> GetPoints();
    void update(OpticalFlowData OFData);
};
} // namespace Detection

#endif