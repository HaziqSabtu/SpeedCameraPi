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
    Detection::ObjectDetection objectDetection(config.maxCorners);
    objectDetection.SetDetectionParams(config.maxCorners, config.qualityLevel,
                                       config.minDistance, config.blockSize,
                                       config.useHarrisDetector, config.k,
                                       config.minPointDistance);

    std::vector<Detection::OpticalFlowData> flowData;

    auto aDVector = data->getAllignData();

    auto roiData = data->getRoiData();

    cv::Rect roi = roiData.roi;

    // create mask for ROI
    cv::Mat mask = cv::Mat::zeros(aDVector.at(0).image.size(), CV_8UC1);
    mask(roi).setTo(255);

    flowData.push_back(objectDetection.init(aDVector.at(0).image, mask));

    // imgData->at(0).SetFlow(objectDetection.init(imgData->at(0).image));
    for (int i = 1; i < aDVector.size(); i++) {
        flowData.push_back(objectDetection.updateFlow(aDVector.at(i).image,
                                                      flowData.at(i - 1)));
    }

    // * IDEA: Imagine Point moving in 3D space
    // * The moving points can be seen clearly ?
    // * Seperate with KNN CLustering
    std::vector<int> ids;
    for (int i = 0; i < flowData.at(0).GetPoints().size(); i++) {
        ids.push_back(i);
    }

    for (int i = 1; i < aDVector.size(); i++) {
        flowData.at(i).thresholdPointsId(ids, flowData.at(i - 1),
                                         config.threshold);
    }

    for (int i = 0; i < aDVector.size(); i++) {
        auto points = flowData.at(i).GetPointsById(ids);

        //fit rectangle
        std::vector<cv::Point2f> ps;

        for (auto p : points) {
            ps.push_back(p.point);
        }

        cv::Rect rect = cv::boundingRect(ps);
        roiData.trackedRoi.push_back(rect);

        data->setRoiData(roiData);
        //flowData.at(i).SetDetection(imgData->at(i).flow.GetPointsById(ids));
    }
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