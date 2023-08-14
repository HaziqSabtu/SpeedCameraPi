/**
 * @file D_Line.hpp
 * @author Haziq Sabtu (mhaziq.sabtu@gmail.com)
 * @brief Custom Implementation of Line Struct with Standard Methods
 * @version 1.0.0
 * @date 2023-03-06
 *
 * @copyright Copyright (c) 2023
 *
 */

#pragma once

#include <opencv2/core.hpp>
#include <string>

/**
 * @brief Custom Implementation of Line Struct with Standard Methods
 *
 */
struct Line {
    cv::Point2f p1;
    cv::Point2f p2;

    Line(cv::Point2f p1, cv::Point2f p2);

    Line(cv::Vec4i line);

    Line();

    double Length();

    double Slope();

    double Angle();

    double Distance(cv::Point2f p);

    cv::Point2f Intersection(Line line);

    Line Extrapolate(int height, int width);

    Line Extrapolate(cv::Mat &image);

    bool isIntersect(cv::Point2f p, int radius);

    static Line Average(std::vector<Line> lines);

    std::string ToString();

    bool isNull();

    void setP1(cv::Point2f p1);

    void setP2(cv::Point2f p2);

    Line Scale(cv::Size src, cv::Size dst);

    bool isVertical();

    bool isHorizontal();
};