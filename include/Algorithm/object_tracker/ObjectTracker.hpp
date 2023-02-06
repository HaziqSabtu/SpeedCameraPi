#ifndef OCJECT_TRACKER_HPP
#define OCJECT_TRACKER_HPP

#include <opencv2/core/ocl.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/tracking.hpp>

class OBJECTTRACKER {
  private:
    /* data */
    cv::Ptr<cv::Tracker> tracker;
    cv::Rect frameRoi;

  public:
    OBJECTTRACKER(std::string type);
    ~OBJECTTRACKER();
    cv::Rect UpdateTracker(cv::Mat &frame);
    void InitTracker(cv::Mat &frame, cv::Rect roi);

  private:
    std::string trackerType;
};

#endif