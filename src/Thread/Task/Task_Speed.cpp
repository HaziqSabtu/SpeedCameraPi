/**
 * @file Task_Speed.cpp
 * @author Haziq Sabtu (mhaziq.sabtu@gmail.com)
 * @brief Task Implementation for Speed Calculation
 * @version 1.0.0
 * @date 2023-03-18
 *
 * @copyright Copyright (c) 2023
 *
 */
#include <Thread/Task/Task_Speed.hpp>

/**
 * @brief Construct a new Speed Task:: Speed Task object
 *
 * @param imgData pointer to ImageData Vector
 * @param selectedLine Selected Line
 * @param result Result of Speed Calculation
 * @param sensorConfig Sensor Configuration ... SensorConfig
 */
SpeedTask::SpeedTask(std::vector<ImageData> *imgData,
                     std::vector<Line> &selectedLine,
                     std::unique_ptr<float> &result, SensorConfig sensorConfig)
    : property(TaskType::TASK_SPEED), imgData(imgData), result(result),
      selectedLine(selectedLine), sensorConfig(sensorConfig) {}

/**
 * @brief Execute the Speed Calculation
 * @details This method will be called automatically by the thread worker
 * <ul>
 * <li> 1. Create SpeedCalculation object
 * <li> 2. Set Sensor Width, Sensor Focal Length, and Object Width
 * <li> 3. Set Image Width
 * <li> 4. Run SpeedCalculation::runCalculation()
 * <li> 5. Set the result to the result pointer
 * </ul>
 *
 */
void SpeedTask::Execute() {
    // SpeedCalculation speedCalc(sensorConfig.SensorWidth,
    //                            sensorConfig.SensorFocalLength,
    //                            sensorConfig.ObjectWidth);
    // speedCalc.SetImageWidth(imgData->at(0).image.cols);
    // speedCalc.runCalculation(imgData, selectedLine);
    // result.reset(new float(speedCalc.GetAvgSpeed()));
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