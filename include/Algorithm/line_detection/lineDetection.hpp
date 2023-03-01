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

#include <opencv2/opencv.hpp>

class LineDetection {
  public:
    LineDetection();
    void SetImage(cv::Mat &image);
    cv::Mat GetCanny();
    // std::vector<cv::Vec4i> GetLinesP();
    std::vector<cv::Vec4i> &GetLinesP();
    static bool isPointOnLine(cv::Vec4i line, cv::Point2f point,
                              int tolerance = 1);
    static cv::Vec4i extrapolateLine(cv::Vec4i line, int height);
    static cv::Vec4i averageLines(std::vector<cv::Vec4i> lines);

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

    // private Methods
  private:
    void ProcessImage();
};

#endif