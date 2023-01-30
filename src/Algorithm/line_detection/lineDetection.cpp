#include <Algorithm/line_detection/lineDetection.hpp>

LineDetection::LineDetection() {}

void LineDetection::ProcessImage() {
    cv::cvtColor(image, grayImage, cv::COLOR_BGR2GRAY);
    cv::Canny(grayImage, cannyImage, threshold1, threshold2, apertureSize,
              L2gradient);
    cv::HoughLinesP(cannyImage, linesP, rho, theta, threshold, minLineLength,
                    maxLineGap);
}

void LineDetection::SetImage(cv::Mat &image) {
    this->image = image;
    this->ProcessImage();
}

cv::Mat LineDetection::GetCanny() {
    // return canny in rgb format
    cv::Mat cannyRGB;
    cv::cvtColor(cannyImage, cannyRGB, cv::COLOR_GRAY2BGR);
    return cannyRGB;
}

std::vector<cv::Vec4i> LineDetection::GetLinesP() { return linesP; }

bool LineDetection::isPointOnLine(cv::Vec4i line, cv::Point2f point,
                                  int tolerance) {
    float x1 = line[0], y1 = line[1], x2 = line[2], y2 = line[3];
    float m = (y2 - y1) / (x2 - x1);
    float b = y1 - m * x1;
    float y = m * point.x + b;
    return abs(point.y - y) <= tolerance;
}

cv::Vec4i LineDetection::extrapolateLine(cv::Vec4i line, int height) {
    float x1 = line[0], y1 = line[1], x2 = line[2], y2 = line[3];
    float m = (y2 - y1) / (x2 - x1);
    float b = y1 - m * x1;
    int x0 = (0 - b) / m;
    int x3 = (height - b) / m;
    return cv::Vec4i(x0, 0, x3, height);
}