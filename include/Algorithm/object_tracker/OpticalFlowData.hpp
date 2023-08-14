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

#pragma once

#include <Utils/Struct/D_Line.hpp>
#include <opencv2/opencv.hpp>
#include <unordered_map>

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
 * @brief Struct for Detection Data
 *
 */
struct DetectionData {
    std::vector<OFPoint> points;

    DetectionData();
    DetectionData(std::vector<OFPoint> points);

    std::vector<cv::Point2f> GetPoints();
    cv::Rect GetRect();
    Line GetLine();
};

/**
 * @brief Struct for Optical Flow Data with custom composition of vector
 *
 */
struct OpticalFlowData {
    cv::Mat gray;
    std::unordered_map<int, OFPoint> data;

    OpticalFlowData();
    OpticalFlowData(cv::Mat gray);
    OpticalFlowData(cv::Mat gray, std::vector<cv::Point2f> points);
    void push(std::vector<cv::Point2f> points);
    void push(OpticalFlowData &OFData, std::vector<cv::Point2f> points,
              std::vector<float> errors, std::vector<uchar> status);
    static std::vector<cv::Point2f>
    GetPoints(std::unordered_map<int, OFPoint> &points);
    std::vector<cv::Point2f> GetPoints();
    void thresholdPointsId(std::vector<int> &ids, OpticalFlowData &previous,
                           float threshold);
    std::vector<OFPoint> GetPointsById(std::vector<int> &ids);
    void update(OpticalFlowData OFData);
    std::vector<OFPoint> threshold(OpticalFlowData &previous, float threshold);
    std::vector<OFPoint> update2(std::vector<OFPoint> &refData);
    OFPoint GetPointById(int id);
};
