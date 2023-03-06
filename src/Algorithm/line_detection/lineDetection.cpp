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
    cv::Mat cannyRGB;
    cv::cvtColor(cannyImage, cannyRGB, cv::COLOR_GRAY2BGR);
    return cannyRGB;
}

/**
 * @brief Return the Result of Hough Line in cv::Vec4i format
 * @details return the lines detected by Hough Line Transform. The result will
 * be an array of Vec4i object indicating detected Lines on the images.
 * @return std::vector<cv::Vec4i> lines detected by Hough Line Transform
 */
std::vector<cv::Vec4i> &LineDetection::GetLinesP() { return linesP; }

/**
 * @brief Return the lines detected by Hough Line Transform in Detection::Line
 * format
 * @details return the lines detected by Hough Line Transform. The result will
 * be an array of Line object indicating detected Lines on the images.
 * @return std::vector<Detection::Line>
 */
std::vector<Detection::Line> LineDetection::GetLines() {
    std::vector<Detection::Line> lines;
    for (auto line : linesP) {
        lines.push_back(Detection::Line(line));
    }
    return lines;
}

/**
 * @brief Get the Hough Data object
 *
 * @return Detection::HoughData
 */
Detection::HoughData LineDetection::GetHoughData() {
    return Detection::HoughData(cannyImage.clone(), GetLines());
}
