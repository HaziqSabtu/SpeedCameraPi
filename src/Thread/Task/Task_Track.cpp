/**
 * @file Task_OpticalFlow.cpp
 * @author Haziq Sabtu (mhaziq.sabtu@gmail.com)
 * @brief Task Implementation for Optical Flow Detection
 * @version 1.0.0
 * @date 2023-03-08
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <Thread/Task/Task_Track.hpp>

TrackTask::TrackTask(DataPtr data, TrackerPtr tracker)
    : data(data), tracker(tracker) {
    property = TaskProperty(currentType);
    name = currentName;
}

void TrackTask::Execute() {

    auto resultData = data->getResultData();

    std::vector<cv::Mat> allignImages;
    auto allignData = resultData.allignData;
    if (allignData.size() == 0) {
        throw std::runtime_error("No Allign Data"
                                 " available");
    }

    for (auto aD : allignData) {
        allignImages.push_back(aD.image);
    }

    auto roiData = data->getTrackingData();
    auto roi = roiData.roi;

    auto obj = tracker->track(allignImages, roi);

    resultData.trackedRoi = obj;
    data->setResultData(resultData);
}