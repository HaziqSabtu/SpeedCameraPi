#pragma once

#include "Algorithm/object_tracker/ObjectTracker.hpp"
#include <opencv2/opencv.hpp>
#include <opencv2/tracking/tracking.hpp>
#include <vector>

/**
 * @brief Class for Tracking Objects from Image using CSRT methods. This method will act as alternative to OpticalFlow implementation (see OFTracker)
 * 
 */
class CSRTTracker : public ObjectTracker {
  public:
    CSRTTracker();

    std::vector<cv::Rect> track(std::vector<cv::Mat> &images,
                                cv::Rect rect) override;

  private:
    cv::Ptr<cv::TrackerCSRT> tracker;
};
