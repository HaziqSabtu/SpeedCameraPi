/**
 * @file Task_OpticalFlow.hpp
 * @author Haziq Sabtu (mhaziq.sabtu@gmail.com)
 * @brief Task Implementation for Optical Flow Detection
 * @version 1.0.0
 * @date 2023-03-08
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef OPTICAL_FLOW_TASK_HPP
#define OPTICAL_FLOW_TASK_HPP

#include <Algorithm/object_detection/ObjectDetection2.hpp>
#include <Thread/Task/Task.hpp>
#include <Utils/DataStruct.hpp>
#include <Utils/Struct/D_OpticalFlow.hpp>

class FlowTask : public Task {
  public:
    FlowTask(std::vector<ImageData> *imgData);
    void Execute() override;
    TaskType GetType() const override;
    std::string GetName() const override;

  private:
    const TaskType type;
    std::vector<ImageData> *imgData;
};

#endif