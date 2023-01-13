#include <Algorithm/object_tracker/ObjectTracker.hpp>

OBJECTTRACKER::OBJECTTRACKER(std::string type = "CSRT") : trackerType(type) {
    if (trackerType == "MIL") {
        std::cout << "Using MIL tracker" << std::endl;
        tracker = cv::TrackerMIL::create();
    }

    if (trackerType == "KCF") {
        std::cout << "Using KCF tracker" << std::endl;
        tracker = cv::TrackerKCF::create();
    }

    if (trackerType == "GOTURN") {
        std::cout << "Using GOTURN tracker" << std::endl;
        tracker = cv::TrackerGOTURN::create();
    }

    if (trackerType == "CSRT") {
        std::cout << "Using CSRT tracker" << std::endl;
        tracker = cv::TrackerCSRT::create();
    }
}

void OBJECTTRACKER::InitTracker(cv::Mat &frame, cv::Rect roi) {
    tracker->init(frame, roi);
}

OBJECTTRACKER::~OBJECTTRACKER() {}

cv::Rect OBJECTTRACKER::UpdateTracker(cv::Mat &frame) {
    tracker->update(frame, frameRoi);
    return frameRoi;
}