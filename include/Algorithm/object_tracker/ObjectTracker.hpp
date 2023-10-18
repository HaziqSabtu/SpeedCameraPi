#pragma once

#include <opencv2/opencv.hpp>

/**
 * @brief Alias for a shared pointer to an ObjectTracker.
 */
#define TrackerPtr std::shared_ptr<ObjectTracker>

/**
 * @brief Interface for object tracking algorithms.
 *
 * This class defines an interface for object tracking algorithms. Subclasses
 * of ObjectTracker must implement the track() method, which takes a vector
 * of images and a region of interest (ROI) and returns a vector of rectangles
 * representing the tracked objects.
 */
class ObjectTracker {
  public:
    /**
     * @brief Track objects in a sequence of images.
     *
     * @param images A vector of images representing the video frames.
     * @param rect The initial region of interest (ROI) to track.
     * @return A vector of rectangles representing the tracked objects.
     */
    virtual std::vector<cv::Rect> track(std::vector<cv::Mat> &images,
                                        cv::Rect rect) = 0;
};
