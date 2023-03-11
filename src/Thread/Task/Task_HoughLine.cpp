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
HoughTask::HoughTask(ImageData &imgData, Detection::HoughData *houghData)
    : property(TaskType::TASK_HOUGHLINE), imgData(imgData),
      houghData(houghData) {}

/**
 * @brief Execute Hough Task
 * @details This method will be called automatically by the thread worker
 *
 */
void HoughTask::Execute() {
    LineDetection lineDetection;
    lineDetection.SetImage(imgData.image);
    Detection::HoughData h = lineDetection.GetHoughData();
    std::cout << "in task: " << std::endl;
    if (h.canny.empty()) {
        std::cout << "Canny is Empty" << std::endl;
    } else {
        std::cout << "Canny is not Empty" << std::endl;
    }
    houghData = &h;
    // imgData.SetHough(lineDetection.GetHoughData());
}

/**
 * @brief Get the TaskProperty of the task
 *
 * @return TaskProperty
 */
TaskProperty HoughTask::GetProperty() const { return property; }

/**
 * @brief Get the Name object
 *
 * @return std::string
 */
std::string HoughTask::GetName() const { return "HoughTask"; }