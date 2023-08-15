/**
 * @file Task_Capture.hpp
 * @author Haziq Sabtu (mhaziq.sabtu@gmail.com)
 * @brief Task Implementation for Capturing Image from Camera to ImageData
 * @version 1.0.0
 * @date 2023-03-06
 *
 * @copyright Copyright (c) 2023
 *
 */
#ifndef CAPTURE_TASK_HPP
#define CAPTURE_TASK_HPP

#include <Thread/Task/Task.hpp>
#include <chrono>
#include <thread>

/**
 * @brief Task Implementation for Capturing Image from Camera to ImageData
 *
 */

class CaptureTask : public Task {
  public:
    CaptureTask(std::vector<ImageData> *imgData, cv::VideoCapture *cap,
                const int maxCapture);
    void Execute() override;
    TaskProperty GetProperty() const override;
    std::string GetName() const override;

  private:
    const TaskProperty property;
    const int maxCapture;
    cv::VideoCapture *cap;
    std::vector<ImageData> *imgData;
};

#endif