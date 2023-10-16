#pragma once

#include "Algorithm/object_tracker/ObjectTracker.hpp"
#include <opencv2/opencv.hpp>
#include <opencv2/tracking/tracking.hpp>
#include <vector>

class CSRTTracker : public ObjectTracker {
  public:
    CSRTTracker();

    std::vector<cv::Rect> track(std::vector<cv::Mat> &images,
                                cv::Rect rect) override;

  private:
    cv::Ptr<cv::TrackerCSRT> tracker;
};
