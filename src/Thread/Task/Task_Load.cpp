/**
 * @file Task_Load.cpp
 * @author Haziq Sabtu (mhaziq.sabtu@gmail.com)
 * @brief Task Implementation for Loading H264 to ImageData
 * @version 1.0.0
 * @date 2023-03-06
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <Thread/Task/Task_Load.hpp>

/**
 * @brief Construct a new Load Task:: Load Task object
 *
 * @param imgData pointer to vector of ImageData
 * @param path path to h264 file
 * @param maxCapture maximum number of capture to load
 */
LoadTask::LoadTask(std::vector<ImageData> *imgData, wxString path,
                   const int maxCapture)
    : property(TaskType::TASK_LOAD), imgData(imgData), path(path),
      maxCapture(maxCapture) {}

/**
 * @brief Execute Load Task
 * @details This method will be called automatically by the thread worker
 *
 */
void LoadTask::Execute() { FILEH264::ReadFile(path, imgData); }

/**
 * @brief Get the Type object
 *
 * @return TaskType
 */
TaskProperty LoadTask::GetProperty() const { return property; }

/**
 * @brief Get the Name object
 *
 * @return std::string
 */
std::string LoadTask::GetName() const { return "LoadTask"; }