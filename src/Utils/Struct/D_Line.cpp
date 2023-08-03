/**
 * @file D_Line.cpp
 * @author Haziq Sabtu (mhaziq.sabtu@gmail.com)
 * @brief Custom Implementation of Line Struct with Standard Methods
 * @version 1.0.0
 * @date 2023-03-06
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <Utils/Struct/D_Line.hpp>

namespace Detection {

/**
 * @brief Construct a new Line:: Line object
 *
 * @param p1 first point of line
 * @param p2 second point of line
 */
Line::Line(cv::Point2f p1, cv::Point2f p2) : p1(p1), p2(p2) {}

/**
 * @brief Construct a new Line:: Line object
 *
 * @param line Vec4i line
 */
Line::Line(cv::Vec4i line)
    : p1(cv::Point2f(line[0], line[1])), p2(cv::Point2f(line[2], line[3])) {}

Line::Line() {}

/**
 * @brief Get the Length of Line
 *
 * @return double length of line
 */
double Line::Length() { return cv::norm(p1 - p2); }

/**
 * @brief Get the Slope of Line
 *
 * @return double slope of line
 */
double Line::Slope() { return (p2.y - p1.y) / (p2.x - p1.x); }

/**
 * @brief Get the Angle of Line
 *
 * @return double angle of line
 */
double Line::Angle() { return atan2(p2.y - p1.y, p2.x - p1.x); }

/**
 * @brief Get the Distance of Point to Line
 *
 * @param p point to be calculated
 * @return double distance of point to line
 */
double Line::Distance(cv::Point2f p) {
    double a = p1.y - p2.y;
    double b = p2.x - p1.x;
    double c = p1.x * p2.y - p2.x * p1.y;
    return abs(a * p.x + b * p.y + c) / sqrt(a * a + b * b);
}

/**
 * @brief Get the Intersection Point of 2 Lines
 *
 * @param line line to be intersected
 * @return cv::Point2f point of intersection
 */
cv::Point2f Line::Intersection(Line line) {
    double x1 = p1.x;
    double y1 = p1.y;
    double x2 = p2.x;
    double y2 = p2.y;
    double x3 = line.p1.x;
    double y3 = line.p1.y;
    double x4 = line.p2.x;
    double y4 = line.p2.y;

    double x =
        ((x1 * y2 - y1 * x2) * (x3 - x4) - (x1 - x2) * (x3 * y4 - y3 * x4)) /
        ((x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4));
    double y =
        ((x1 * y2 - y1 * x2) * (y3 - y4) - (y1 - y2) * (x3 * y4 - y3 * x4)) /
        ((x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4));

    return cv::Point2f(x, y);
}

/**
 * @brief Extrapolate Line to the edge of image
 *
 * @param height height of image
 * @param width width of image
 * @return Line extrapolated line
 */
Line Line::Extrapolate(int height, int width) {
    cv::Point2f p1;
    cv::Point2f p2;

    p1 = Intersection(Line(cv::Point2f(0, 0), cv::Point2f(width, 0)));
    p2 = Intersection(Line(cv::Point2f(0, height), cv::Point2f(width, height)));

    return Line(p1, p2);
}

/**
 * @brief Extrapolate Line to the edge of image
 *
 * @param image image to be used for reference
 * @return Line extrapolated line
 */
Line Line::Extrapolate(cv::Mat &image) {
    return Extrapolate(image.rows, image.cols);
}

/**
 * @brief Check if Line is Intersecting with Circle
 * @details Important! This method only checks if the line and
 * not the vector that intersects with the circle. If the line is short and does
 * not actually pass through the circle, this method will return false.
 * @param p center of circle
 * @param radius radius of circle
 * @return true if line is intersecting with circle
 * @return false if line is not intersecting with circle
 */
bool Line::isIntersect(cv::Point2f p, int radius) {
    double dx = p2.x - p1.x;
    double dy = p2.y - p1.y;

    double a = dx * dx + dy * dy;
    double b = 2 * (dx * (p1.x - p.x) + dy * (p1.y - p.y));
    double c = p.x * p.x + p.y * p.y + p1.x * p1.x + p1.y * p1.y -
               2 * (p.x * p1.x + p.y * p1.y) - radius * radius;

    double delta = b * b - 4 * a * c;

    if (delta < 0) {
        return false;
    }

    double t1 = (-b + sqrt(delta)) / (2 * a);
    double t2 = (-b - sqrt(delta)) / (2 * a);

    // Check if either t1 or t2 is within the range [0, 1]
    if ((t1 >= 0 && t1 <= 1) || (t2 >= 0 && t2 <= 1)) {
        return true;
    }
    return false;
}

/**
 * @brief Get the Average of Lines
 *
 * @param lines lines vector to be averaged
 * @return Line averaged line
 */
Line Line::Average(std::vector<Detection::Line> lines) {
    cv::Point2f p1;
    cv::Point2f p2;

    for (auto line : lines) {
        p1 += line.p1;
        p2 += line.p2;
    }

    p1 /= static_cast<float>(lines.size());
    p2 /= static_cast<float>(lines.size());

    return Line(p1, p2);
}

/**
 * @brief Get the String Representation of Line
 *
 * @return std::string
 */
std::string Line::ToString() {
    std::stringstream ss;
    ss << "Line: (" << p1.x << ", " << p1.y << ") -> (" << p2.x << ", " << p2.y
       << ")";
    return ss.str();
}

bool Line::isNull() {
    if (p1.x == 0 && p1.y == 0 && p2.x == 0 && p2.y == 0) {
        return true;
    }

    return false;
}

void Line::setP1(cv::Point2f p1) { this->p1 = p1; }

void Line::setP2(cv::Point2f p2) { this->p2 = p2; }

Line Line::Scale(cv::Size src, cv::Size dst) {
    cv::Point2f p1;
    cv::Point2f p2;

    p1.x = (this->p1.x / src.width) * dst.width;
    p1.y = (this->p1.y / src.height) * dst.height;
    p2.x = (this->p2.x / src.width) * dst.width;
    p2.y = (this->p2.y / src.height) * dst.height;

    return Line(p1, p2);
}

} // namespace Detection