/**
 * @file lineDetection.hpp
 * @author Haziq Sabtu (mhaziq.sabtu@gmail.com)
 * @brief Class for Detecting Lines from Image using Hough Line Transform
 * @version 1.0.0
 * @date 2023-03-01
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef LINE_DETECTION_HPP
#define LINE_DETECTION_HPP

#include <Utils/DataStruct.hpp>
#include <Utils/Struct/D_Line.hpp>
#include <opencv2/opencv.hpp>

/**
 * @brief Class for Detecting Lines from Image using Hough Line Transform
 *
 */
class LineDetection {
  public:
    LineDetection();
    void SetImage(cv::Mat &image);
    void SetCannyParameters(double threshold1, double threshold2,
                            int apertureSize, bool L2gradient);
    void SetHoughLinesPParameters(double rho, double theta, int threshold,
                                  double minLineLength, double maxLineGap);
    cv::Mat GetCanny();
    std::vector<cv::Vec4i> &GetLinesP();
    std::vector<Detection::Line> GetLines();
    Detection::HoughData GetHoughData();
    void ProcessImage();

  private:
    cv::Mat image;
    cv::Mat grayImage;
    cv::Mat cannyImage;

    // canny Parameters
    double threshold1 = 50;
    double threshold2 = 100;
    int apertureSize = 3;
    bool L2gradient = false;

    // HoughLinesP Parameters
    std::vector<cv::Vec4i> linesP;
    double rho = 1;
    double theta = CV_PI / 180;
    int threshold = 50;
    double minLineLength = 25;
    double maxLineGap = 10;
};

#endif