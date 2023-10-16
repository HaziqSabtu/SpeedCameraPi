#pragma once

#include <opencv2/opencv.hpp>

#define TrackerPtr std::shared_ptr<ObjectTracker>

class ObjectTracker {
  public:
    virtual std::vector<cv::Rect> track(std::vector<cv::Mat> &images,
                                        cv::Rect rect) = 0;
};