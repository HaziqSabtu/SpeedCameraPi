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

#include "Algorithm/object_tracker/CSRTTracker.hpp"
#include <Thread/Task/Task_OpticalFlow.hpp>

FlowTask::FlowTask(DataPtr data, OpticalFlowConfig config)
    : data(data), config(config) {
    property = TaskProperty(currentType);
    name = currentName;
}

void FlowTask::Execute() {
    OFTracker ofTracker;
    ofTracker.SetMaxCorners(config.maxCorners);
    ofTracker.SetQualityLevel(config.qualityLevel);
    ofTracker.SetMinDistance(config.minDistance);
    ofTracker.SetBlockSize(config.blockSize);
    ofTracker.SetUseHarrisDetector(config.useHarrisDetector);
    ofTracker.SetK(config.k);
    ofTracker.SetMinPointDistance(config.minPointDistance);
    ofTracker.SetThreshold(config.threshold);

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

    auto obj = ofTracker.track(allignImages, roi);

    resultData.trackedRoi = obj;
    data->setResultData(resultData);
}

CsrtTask::CsrtTask(DataPtr data) : data(data) {
    property = TaskProperty(currentType);
    name = currentName;
}

void CsrtTask::Execute() {
    CSRTTracker tracker;

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

    auto obj = tracker.track(allignImages, roi);

    resultData.trackedRoi = obj;
    data->setResultData(resultData);
}