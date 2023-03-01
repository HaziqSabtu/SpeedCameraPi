/**
 * @file lineDetection.cpp
 * @author Haziq Sabtu (mhaziq.sabtu@gmail.com)
 * @brief Class for Detecting Lines from Image using Hough Line Transform
 * @version 1.0.0
 * @date 2023-03-01
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <Algorithm/line_detection/lineDetection.hpp>

/**
 * @brief Construct a new Line Detection:: Line Detection object
 *
 */
LineDetection::LineDetection() {}

/**
 * @brief Process the image to get the canny and lines
 *
 */
void LineDetection::ProcessImage() {
    cv::cvtColor(image, grayImage, cv::COLOR_BGR2GRAY);
    cv::Canny(grayImage, cannyImage, threshold1, threshold2, apertureSize,
              L2gradient);
    cv::HoughLinesP(cannyImage, linesP, rho, theta, threshold, minLineLength,
                    maxLineGap);
}

/**
 * @brief Set the Image object
 * @details the image parsed will be processed to get the canny and lines
 * @param image image to be processed
 */
void LineDetection::SetImage(cv::Mat &image) {
    this->image = image;
    this->ProcessImage();
}

/**
 * @brief Get the Canny object
 * @details return the canny image in rgb format
 * @return cv::Mat canny image in rgb format
 */
cv::Mat LineDetection::GetCanny() {
    // return canny in rgb format
    cv::Mat cannyRGB;
    cv::cvtColor(cannyImage, cannyRGB, cv::COLOR_GRAY2BGR);
    return cannyRGB;
}

// std::vector<cv::Vec4i> LineDetection::GetLinesP() { return linesP; }
/**
 * @brief Get the Result of Hough Line
 * @details return the lines detected by Hough Line Transform. The result will
 * be an array of Vec4i object indicating detected Lines on the images.
 * @return std::vector<cv::Vec4i> lines detected by Hough Line Transform
 */
std::vector<cv::Vec4i> &LineDetection::GetLinesP() { return linesP; }

/**
 * @brief Check if the point is on the line
 * @param line line to be checked
 * @param point point to be checked
 * @param tolerance tolerance of the point to be on the line
 * @return true if the point is on the line
 * @return false if the point is not on the line
 */
bool LineDetection::isPointOnLine(cv::Vec4i line, cv::Point2f point,
                                  int tolerance) {
    // check if the point in on the line and dont extrapolate it

    float x1 = static_cast<float>(line[0]);
    float y1 = static_cast<float>(line[1]);
    float x2 = static_cast<float>(line[2]);
    float y2 = static_cast<float>(line[3]);
    float m = (y2 - y1) / (x2 - x1);
    float b = y1 - m * x1;
    float y = m * point.x + b;
    return fabs(point.y - y) <= tolerance && point.x >= x1 && point.x <= x2;
}

/**
 * @brief Get the Extrapolated Line object
 * @details Extrapolate the line to the height of the image
 * @param line line to be extrapolated
 * @param height height of the image
 * @return cv::Vec4i extrapolated line
 */
cv::Vec4i LineDetection::extrapolateLine(cv::Vec4i line, int height) {
    float x1 = static_cast<float>(line[0]);
    float y1 = static_cast<float>(line[1]);
    float x2 = static_cast<float>(line[2]);
    float y2 = static_cast<float>(line[3]);
    float m = (y2 - y1) / (x2 - x1);
    float b = y1 - m * x1;
    int x0 = static_cast<int>((0 - b) / m);
    int x3 = static_cast<int>((height - b) / m);
    return cv::Vec4i(x0, 0, x3, height);
}

/**
 * @brief Calculate the average of the lines if more than one line is detected
 * @details Get the average of the lines
 * @param lines lines vector to be averaged
 * @return cv::Vec4i average of the lines
 */
cv::Vec4i LineDetection::averageLines(std::vector<cv::Vec4i> lines) {
    float x1 = 0;
    float y1 = 0;
    float x2 = 0;
    float y2 = 0;
    for (cv::Vec4i line : lines) {
        x1 += static_cast<float>(line[0]);
        y1 += static_cast<float>(line[1]);
        x2 += static_cast<float>(line[2]);
        y2 += static_cast<float>(line[3]);
    }
    x1 /= static_cast<float>(lines.size());
    y1 /= static_cast<float>(lines.size());
    x2 /= static_cast<float>(lines.size());
    y2 /= static_cast<float>(lines.size());
    return cv::Vec4i(static_cast<int>(x1), static_cast<int>(y1),
                     static_cast<int>(x2), static_cast<int>(y2));
}