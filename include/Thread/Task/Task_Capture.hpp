#ifndef CAPTURE_TASK_HPP
#define CAPTURE_TASK_HPP

#include <Thread/Task/Task.hpp>
#include <Utils/DataStruct.hpp>
#include <chrono>
#include <thread>

class CaptureTask : public Task {
  public:
    CaptureTask(std::vector<ImageData> *imgData, cv::VideoCapture *cap,
                const int maxCapture);
    void Execute() override;
    TaskType GetType() const override;

  private:
    const TaskType type;
    const int maxCapture;
    cv::VideoCapture *cap;
    std::vector<ImageData> *imgData;
};

#endif