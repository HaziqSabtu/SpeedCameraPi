#include <Algorithm/object_tracker/CSRTTracker.hpp>

CSRTTracker::CSRTTracker() { tracker = cv::TrackerCSRT::create(); }

std::vector<cv::Rect> CSRTTracker::track(std::vector<cv::Mat> &images,
                                         cv::Rect rect) {
    std::vector<cv::Rect> trackedRectangles;

    // Initialize the CSRT tracker
    tracker->init(images[0], rect);

    trackedRectangles.push_back(rect);

    // Loop through the images to track the object
    for (size_t i = 1; i < images.size(); ++i) {
        // Update the tracker with the current image
        bool success = tracker->update(images[i], rect);

        if (success) {
            trackedRectangles.push_back(rect);
        } else {
            trackedRectangles.push_back(trackedRectangles.back());
        }
    }

    return trackedRectangles;
}
