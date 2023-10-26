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

#include <Thread/Task/Task.hpp>
#include <Utils/Config/AppConfig.hpp>

/**
 * @brief Task Implementation for Tracking
 *
 */
class TrackTask : public Task {
  public:
    TrackTask(DataPtr data, TrackerPtr tracker);
    void Execute() override;

  private:
    DataPtr data;
    TrackerPtr tracker;

    const std::string currentName = "TrackTask";
    const TaskType currentType = TaskType::TASK_TRACK;
};

#endif