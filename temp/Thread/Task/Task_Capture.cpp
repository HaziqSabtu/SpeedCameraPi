/**
 * @file Task_Capture.cpp
 * @author Haziq Sabtu (mhaziq.sabtu@gmail.com)
 * @brief Task Implementation for Capturing Image from Camera to ImageData
 * @version 1.0.0
 * @date 2023-03-06
 *
 * @copyright Copyright (c) 2023
 *
 */
#include <Thread/Task/Task_Capture.hpp>

/**
 * @brief Construct a new Capture Task:: Capture Task object
 * @details Update Required!
 * @param imgData pointer to vector of ImageData
 * @param cap pointer to VideoCapture
 * @param maxCapture maximum number of capture to load
 */
CaptureTask::CaptureTask(std::vector<ImageData> *imgData, cv::VideoCapture *cap,
                         const int maxCapture)
    : property(TaskType::TASK_CAPTURE), imgData(imgData), cap(cap),
      maxCapture(maxCapture) {}

/**
 * @brief Execute Capture Task
 @details This method will be called automatically by the thread worker
 *
 */
void CaptureTask::Execute() {
    for (int i = 0; i < maxCapture; i++) {
        cv::Mat frame;
        cap->read(frame);
        imgData->push_back(ImageData(frame.clone()));
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
}

/**
 * @brief Get the Type object
 *
 * @return TaskType
 */
TaskProperty CaptureTask::GetProperty() const { return property; }

/**
 * @brief Get the Name object
 *
 * @return std::string
 */
std::string CaptureTask::GetName() const { return "CaptureTask"; }