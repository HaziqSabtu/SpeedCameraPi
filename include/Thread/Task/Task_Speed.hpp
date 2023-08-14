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

#include <Algorithm/speed_calculation/speedCalculation.hpp>
#include <Thread/Task/Task.hpp>
#include <Utils/Config/AppConfig.hpp>
#include <Utils/DataStruct.hpp>
#include <Utils/Struct/D_Line.hpp>

/**
 * @brief Task Implementation for Speed Calculation
 *
 */
class SpeedTask : public Task {
  public:
    SpeedTask(std::vector<ImageData> *imgData, std::vector<Line> &selectedLine,
              std::unique_ptr<float> &result, SensorConfig sensorConfig);
    void Execute() override;
    TaskProperty GetProperty() const override;
    std::string GetName() const override;

  private:
    const TaskProperty property;

    std::vector<ImageData> *imgData;
    std::vector<Line> selectedLine;
    std::unique_ptr<float> &result;
    SensorConfig sensorConfig;
};

#endif