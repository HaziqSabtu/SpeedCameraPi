#pragma once

#include <opencv2/opencv.hpp>

class IObjectTracker {
  public:
    virtual std::vector<cv::Rect> track(std::vector<cv::Mat> &images,
                                        cv::Rect rect) = 0;
};