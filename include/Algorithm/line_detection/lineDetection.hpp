#ifndef LINE_DETECTION_HPP
#define LINE_DETECTION_HPP

#include <opencv2/opencv.hpp>

class LineDetection {
  public:
    LineDetection();
    void SetImage(cv::Mat &image);
    static bool isPointOnLine(cv::Vec4i line, cv::Point2f point,
                              int tolerance = 1);
    static cv::Vec4i extrapolateLine(cv::Vec4i line, int height);

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
    double minLineLength = 50;
    double maxLineGap = 10;

    // private Methods
  private:
    void ProcessImage();
};

#endif