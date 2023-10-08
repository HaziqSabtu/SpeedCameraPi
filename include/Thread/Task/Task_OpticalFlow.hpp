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

#include "Algorithm/object_tracker/ObjectTracker.hpp"
#include "Model/SessionData.hpp"
#include <Algorithm/object_tracker/OpticalFlowData.hpp>
#include <Algorithm/object_tracker/OpticalFlowTracker.hpp>
#include <Thread/Task/Task.hpp>
#include <Utils/Config/AppConfig.hpp>

/**
 * @brief Task Implementation for Optical Flow Detection
 *
 */
//TODO: Rename
class FlowTask : public Task {
  public:
    FlowTask(DataPtr data, TrackerPtr tracker);
    void Execute() override;

  private:
    DataPtr data;
    TrackerPtr tracker;

    const std::string currentName = "FlowTask";
    const TaskType currentType = TaskType::TASK_FLOW;
};

// TODO: Remove
class CsrtTask : public Task {
  public:
    CsrtTask(DataPtr data);
    void Execute() override;

  private:
    DataPtr data;

    const std::string currentName = "CsrtTask";
    const TaskType currentType = TaskType::TASK_CSRT;
};

#endif