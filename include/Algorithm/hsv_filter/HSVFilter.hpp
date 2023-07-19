#pragma once

#include <opencv2/core/base.hpp>
#include <opencv2/core/mat.hpp>
#include <opencv2/core/types.hpp>
#include <opencv2/imgproc.hpp>

class HSVFilter {
  private:
    cv::Scalar lower_red1 = cv::Scalar(0, 100, 100);
    cv::Scalar upper_red1 = cv::Scalar(5, 255, 255);

    cv::Scalar lower_red2 = cv::Scalar(175, 100, 100);
    cv::Scalar upper_red2 = cv::Scalar(179, 255, 255);

    cv::Scalar lower_yellow = cv::Scalar(20, 100, 100);
    cv::Scalar upper_yellow = cv::Scalar(35, 255, 255);

    cv::Scalar lower_blue = cv::Scalar(100, 100, 100);
    cv::Scalar upper_blue = cv::Scalar(130, 255, 255);

  public:
    HSVFilter();

    cv::Mat toHSV(cv::Mat &src);

    cv::Mat filter(cv::Mat &hsv, cv::Scalar lower, cv::Scalar upper);

    cv::Mat redMask(cv::Mat &hsv);

    cv::Mat yellowMask(cv::Mat &hsv);

    cv::Mat blueMask(cv::Mat &hsv);

    void setRed1(cv::Scalar lower_red, cv::Scalar upper_red);

    void setRed2(cv::Scalar lower_red, cv::Scalar upper_red);

    void setYellow(cv::Scalar lower_yellow, cv::Scalar upper_yellow);

    void setBlue(cv::Scalar lower_blue, cv::Scalar upper_blue);
};
