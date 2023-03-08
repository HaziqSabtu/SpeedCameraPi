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

#include <Utils/Struct/D_Line.hpp>
#include <opencv2/opencv.hpp>

namespace Detection {
/**
 * @brief Struct for Optical Flow Point
 *
 */
struct OFPoint {
    int id;
    cv::Point2f point;
    uchar status;
    float error;

    OFPoint(int id, cv::Point2f point, float error, uchar status);
    static float distance(OFPoint &p1, OFPoint &p2);
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
    static std::vector<cv::Point2f>
    GetPoints(std::vector<Detection::OFPoint> &points);
    std::vector<cv::Point2f> GetPoints();
    void update(OpticalFlowData OFData);
    std::vector<OFPoint> threshold(OpticalFlowData &previous, float threshold);
    Detection::OFPoint GetPointById(int id);
};

/**
 * @brief Struct for Detection Data
 *
 */
struct DetectionData {
    std::vector<Detection::OFPoint> points;

    DetectionData();
    DetectionData(std::vector<Detection::OFPoint> points);

    std::vector<cv::Point2f> GetPoints();
    cv::Rect GetRect();
    Detection::Line GetLine();
};
} // namespace Detection

#endif