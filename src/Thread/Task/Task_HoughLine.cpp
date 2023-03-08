/**
 * @file Task_HoughLine.cpp
 * @author Haziq Sabtu (mhaziq.sabtu@gmail.com)
 * @brief Task Implementation for Hough Line Detection
 * @version 1.0.0
 * @date 2023-03-07
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <Thread/Task/Task_HoughLine.hpp>

/**
 * @brief Construct a new Hough Task:: Hough Task object
 *
 * @param imgData pointer to vector of ImageData
 * @param id index of target image in vector
 */
HoughTask::HoughTask(std::vector<ImageData> *imgData, int id)
    : type(TaskType::TASK_FLOW), imgData(imgData), id(id) {}

/**
 * @brief Execute Hough Task
 * @details This method will be called automatically by the thread worker
 *
 */
void HoughTask::Execute() {
    ImageData target = (*imgData)[id];
    LineDetection lineDetection;
    lineDetection.SetImage(target.image);
    imgData->at(id).SetHough(lineDetection.GetHoughData());
}

/**
 * @brief Get the Type object
 *
 * @return TaskType
 */
TaskType HoughTask::GetType() const { return type; }

/**
 * @brief Get the Name object
 *
 * @return std::string
 */
std::string HoughTask::GetName() const { return "HoughTask"; }