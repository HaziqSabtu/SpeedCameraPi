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

/**
 * @brief Construct a new Flow Task:: Flow Task object
 *
 * @param imgData pointer to vector of ImageData
 */
FlowTask::FlowTask(std::vector<ImageData> *imgData)
    : type(TaskType::TASK_FLOW), imgData(imgData) {}

/**
 * @brief Execute Flow Task
 * @details This method will be called automatically by the thread worker
 *
 */
void FlowTask::Execute() {
    Detection::OD objectDetection(1000);
    imgData->at(0).SetFlow(objectDetection.init(imgData->at(0).image));
    for (int i = 1; i < imgData->size(); i++) {
        imgData->at(i).SetFlow(
            objectDetection.updateFlow(imgData->at(i), imgData->at(i - 1)));
    }

    for (int i = 1; i < imgData->size(); i++) {
        Detection::OpticalFlowData prevData = imgData->at(i - 1).flow;
        Detection::OpticalFlowData currData = imgData->at(i).flow;

        imgData->at(i).SetDetection(currData.threshold(prevData, 0.2));
    }
}

/**
 * @brief Get the Type object
 *
 * @return TaskType
 */
TaskType FlowTask::GetType() const { return type; }

/**
 * @brief Get the Name object
 *
 * @return std::string
 */
std::string FlowTask::GetName() const { return "FlowTask"; }