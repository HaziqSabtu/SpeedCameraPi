#include <Thread/Task/Task_Speed.hpp>

SpeedTask::SpeedTask(std::vector<ImageData> *imgData,
                     std::vector<Detection::Line> &selectedLine,
                     std::unique_ptr<float> &result, SensorConfig sensorConfig)
    : property(TaskType::TASK_SPEED), imgData(imgData), result(result),
      selectedLine(selectedLine), sensorConfig(sensorConfig) {}

void SpeedTask::Execute() {
    SpeedCalculation speedCalc(sensorConfig.SensorWidth,
                               sensorConfig.SensorFocalLength,
                               sensorConfig.ObjectWidth);
    speedCalc.SetImageWidth(imgData->at(0).image.cols);
    speedCalc.runCalculation(imgData, selectedLine);
    result.reset(new float(speedCalc.GetAvgSpeed()));
}

/**
 * @brief Get the Type object
 *
 * @return TaskType
 */
TaskProperty SpeedTask::GetProperty() const { return property; }

/**
 * @brief Get the Name object
 *
 * @return std::string
 */
std::string SpeedTask::GetName() const { return "SpeedTask"; }