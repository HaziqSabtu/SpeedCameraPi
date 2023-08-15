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

#include <Thread/Task/Task_OpticalFlow.hpp>

FlowTask::FlowTask(DataPtr data, OpticalFlowConfig config)
    : property(TaskType::TASK_FLOW), data(data), config(config) {}

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

    std::vector<cv::Mat> allignImages;
    for (auto aD : data->getAllignData()) {
        allignImages.push_back(aD.image);
    }

    //TODO: Add Redundant Tracker

    auto roiData = data->getTrackingData();
    auto roi = roiData.roi;

    auto obj = ofTracker.track(allignImages, roi);

    roiData.trackedRoi = obj;
    data->setTrackingData(roiData);
}

/**
 * @brief Get the Type object
 *
 * @return TaskType
 */
TaskProperty FlowTask::GetProperty() const { return property; }

/**
 * @brief Get the Name object
 *
 * @return std::string
 */
std::string FlowTask::GetName() const { return "FlowTask"; }