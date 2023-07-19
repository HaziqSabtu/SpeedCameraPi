#include <Algorithm/hsv_filter/HSVFilter.hpp>

HSVFilter::HSVFilter() {}

cv::Mat HSVFilter::toHSV(cv::Mat &src) {
    cv::Mat hsv;
    cv::cvtColor(src, hsv, cv::COLOR_BGR2HSV);
    return hsv;
}

cv::Mat HSVFilter::filter(cv::Mat &hsv, cv::Scalar lower, cv::Scalar upper) {
    cv::Mat mask;
    cv::inRange(hsv, lower, upper, mask);
    return mask;
}

cv::Mat HSVFilter::redMask(cv::Mat &hsv) {
    cv::Mat mask1 = filter(hsv, lower_red1, upper_red1);
    cv::Mat mask2 = filter(hsv, lower_red2, upper_red2);
    cv::Mat mask = mask1 | mask2;
    return mask;
}

cv::Mat HSVFilter::yellowMask(cv::Mat &hsv) {
    cv::Mat mask = filter(hsv, lower_yellow, upper_yellow);
    return mask;
}

cv::Mat HSVFilter::blueMask(cv::Mat &hsv) {
    cv::Mat mask = filter(hsv, lower_blue, upper_blue);
    return mask;
}

void HSVFilter::setRed1(cv::Scalar lower_red, cv::Scalar upper_red) {
    this->lower_red1 = lower_red;
    this->upper_red1 = upper_red;
}

void HSVFilter::setRed2(cv::Scalar lower_red, cv::Scalar upper_red) {
    this->lower_red2 = lower_red;
    this->upper_red2 = upper_red;
}

void HSVFilter::setYellow(cv::Scalar lower_yellow, cv::Scalar upper_yellow) {
    this->lower_yellow = lower_yellow;
    this->upper_yellow = upper_yellow;
}

void HSVFilter::setBlue(cv::Scalar lower_blue, cv::Scalar upper_blue) {
    this->lower_blue = lower_blue;
    this->upper_blue = upper_blue;
}
