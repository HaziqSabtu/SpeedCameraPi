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
FlowTask::FlowTask(std::vector<ImageData> *imgData, const int maxPoints,
                   double threshold)
    : property(TaskType::TASK_FLOW), imgData(imgData), maxPoints(maxPoints),
      threshold(threshold) {}

/**
 * @brief Execute Flow Task
 * @details This method will be called automatically by the thread worker
 *
 */
void FlowTask::Execute() {
    Detection::OD objectDetection(maxPoints);
    imgData->at(0).SetFlow(objectDetection.init(imgData->at(0).image));
    for (int i = 1; i < imgData->size(); i++) {
        imgData->at(i).SetFlow(
            objectDetection.updateFlow(imgData->at(i), imgData->at(i - 1)));
    }

    // * IDEA: Imagine Point moving in 3D space
    // * The moving points can be seen clearly ?
    // * Seperate with KNN CLustering
    std::vector<int> ids;
    for (int i = 0; i < imgData->at(0).flow.GetPoints().size(); i++) {
        ids.push_back(i);
    }

    for (int i = 1; i < imgData->size(); i++) {
        imgData->at(i).flow.thresholdPointsId(ids, imgData->at(i - 1).flow,
                                              threshold);
    }

    for (int i = 0; i < imgData->size(); i++) {
        imgData->at(i).SetDetection(imgData->at(i).flow.GetPointsById(ids));
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