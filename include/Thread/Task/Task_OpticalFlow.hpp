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

#include "Model/SessionData.hpp"
#include <Algorithm/object_detection/ObjectDetection.hpp>
#include <Thread/Task/Task.hpp>
#include <Utils/Config/AppConfig.hpp>
#include <Utils/DataStruct.hpp>
#include <Utils/Struct/D_OpticalFlow.hpp>

/**
 * @brief Task Implementation for Optical Flow Detection
 *
 */
class FlowTask : public Task {
  public:
    FlowTask(DataPtr data, OpticalFlowConfig config);
    void Execute() override;
    TaskProperty GetProperty() const override;
    std::string GetName() const override;

  private:
    const TaskProperty property;
    DataPtr data;

    OpticalFlowConfig config;
};

#endif