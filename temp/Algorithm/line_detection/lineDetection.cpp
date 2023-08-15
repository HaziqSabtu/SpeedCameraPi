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

#include <>

/**
 * @brief Construct a new Line Detection:: Line Detection object
 *
 */
LineDetection::LineDetection() {}

/**
 * @brief Process the image to get the canny and lines
 * @details
 * <ul>
 * <li>Convert the image to grayscale</li>
 * <li>Apply Canny Edge Detection</li>
 * <li>Apply Hough Line Transform</li>
 * </ul>
 */
void LineDetection::ProcessImage() {
    cv::cvtColor(image, grayImage, cv::COLOR_BGR2GRAY);
    cv::Canny(grayImage, cannyImage, threshold1, threshold2, apertureSize,
              L2gradient);
    cv::HoughLinesP(cannyImage, linesP, rho, theta, threshold, minLineLength,
                    maxLineGap);
}

/**
 * @brief Set the Canny Parameters
 *
 * @param threshold1 lower threshold for the hysteresis procedure
 * @param threshold2 upper threshold for the hysteresis procedure
 * @param apertureSize aperture size for the Sobel operator
 * @param L2gradient a flag, indicating whether a more accurate L_2 norm
    * should be used to calculate the image gradient magnitude ( L2gradient=true
 ),
    * or whether the default L_1 norm is enough ( L2gradient=false ).

 */
void LineDetection::SetCannyParameters(double threshold1, double threshold2,
                                       int apertureSize, bool L2gradient) {
    this->threshold1 = threshold1;
    this->threshold2 = threshold2;
    this->apertureSize = apertureSize;
    this->L2gradient = L2gradient;
}

/**
 * @brief Set the Hough Lines Parameters
 *
 * @param rho distance resolution of the accumulator
 * @param theta angle resolution of the accumulator
 * @param threshold threshold for line segments. Line segments with less than
    that are rejected.
 * @param minLineLength minimum length of line. Line segments shorter than that
    are rejected.
 * @param maxLineGap maximum allowed gap between points on the same line to link
    them
 */
void LineDetection::SetHoughLinesPParameters(double rho, double theta,
                                             int threshold,
                                             double minLineLength,
                                             double maxLineGap) {
    this->rho = rho;
    this->theta = theta;
    this->threshold = threshold;
    this->minLineLength = minLineLength;
    this->maxLineGap = maxLineGap;
}

/**
 * @brief Set the Image object
 * @details the image parsed will be processed to get the canny and lines
 * the method ProcessImage() will be called here
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
 * @brief Return the lines detected by Hough Line Transform in Line
 * format
 * @details return the lines detected by Hough Line Transform. The result will
 * be an array of Line object indicating detected Lines on the images.
 * @return std::vector<Line>
 */
std::vector<Line> LineDetection::GetLines() {
    std::vector<Line> lines;
    for (auto line : linesP) {
        lines.push_back(Line(line));
    }
    return lines;
}

/**
 * @brief Get the Hough Data object
 *
 * @return Detection::HoughData
 */
Detection::HoughData LineDetection::GetHoughData() {
    return Detection::HoughData(GetCanny(), GetLines());
}
