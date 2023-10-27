/**
 * @file Task_Speed.hpp
 * @author Haziq Sabtu (mhaziq.sabtu@gmail.com)
 * @brief Task Implementation for Speed Calculation
 * @version 1.0.0
 * @date 2023-03-18
 *
 * @copyright Copyright (c) 2023
 *
 */
#ifndef SPEED_TASK_HPP
#define SPEED_TASK_HPP

#include <Thread/Task/Task.hpp>
/**
 * @brief Task Implementation for Speed Calculation
 *
 */
class SpeedTask : public Task {
  public:
    SpeedTask(DataPtr data, SpeedCalcPtr speedCalc);
    void Execute() override;

  private:
    DataPtr data;
    SpeedCalcPtr speedCalc;

    const std::string currentName = "SpeedTask";
    const TaskType currentType = TaskType::TASK_SPEED;
};

#endif