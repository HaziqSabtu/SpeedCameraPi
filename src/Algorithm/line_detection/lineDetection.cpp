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
    // check if the point in on the line and dont extrapolate it

    float x1 = static_cast<float>(line[0]);
    float y1 = static_cast<float>(line[1]);
    float x2 = static_cast<float>(line[2]);
    float y2 = static_cast<float>(line[3]);
    float m = (y2 - y1) / (x2 - x1);
    float b = y1 - m * x1;
    float y = m * point.x + b;
    return abs(point.y - y) <= tolerance && point.x >= x1 && point.x <= x2;
}

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