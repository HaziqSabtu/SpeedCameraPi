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

#include "Utils/Config/ConfigStruct.hpp"
#include <Algorithm/Struct/D_Line.hpp>

#include <Algorithm/speed_calculation/speedCalculation.hpp>
#include <Thread/Task/Task.hpp>
#include <Utils/Config/AppConfig.hpp>
/**
 * @brief Task Implementation for Speed Calculation
 *
 */
class SpeedTask : public Task {
  public:
    SpeedTask(DataPtr data, SpeedPtr speedCalc);
    void Execute() override;

  private:
    DataPtr data;
    SpeedPtr speedCalc;

    const std::string currentName = "SpeedTask";
    const TaskType currentType = TaskType::TASK_SPEED;
};

#endif