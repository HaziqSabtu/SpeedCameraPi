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

#ifndef D_LINE_HPP
#define D_LINE_HPP

#include <opencv2/core.hpp>
#include <string>

namespace Detection {
struct Line {
    cv::Point2f p1;
    cv::Point2f p2;

    Line(cv::Point2f p1, cv::Point2f p2);

    Line(cv::Vec4i line);

    double Length();

    double Slope();

    double Angle();

    double Distance(cv::Point2f p);

    cv::Point2f Intersection(Line line);

    Line Extrapolate(int height, int width);

    Line Extrapolate(cv::Mat &image);

    bool isIntersect(cv::Point2f p, int radius);

    static Line Average(std::vector<Detection::Line> lines);

    std::string ToString();
};
} // namespace Detection

#endif