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
SpeedTask::SpeedTask(DataPtr data, SpeedCalcPtr speedCalc)
    : data(data), speedCalc(speedCalc) {
    property = TaskProperty(currentType);
    name = currentName;
}

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
    auto resultData = data->getResultData();
    auto roiData = resultData.trackedRoi;

    auto allignData = resultData.allignData;

    std::vector<cv::Mat> allignImages;
    for (auto d : allignData) {
        allignImages.push_back(d.image);
    }

    std::vector<HPTime> times;
    for (auto t : data->getCaptureData()) {
        times.push_back(t.time);
    }

    if (data->isCalibrationDataEmpty()) {
        throw std::runtime_error("Calibration Data is empty");
    }

    auto calibData = data->getCalibrationData();
    std::vector<Line> lines;
    lines.push_back(calibData.lineLeft);
    lines.push_back(calibData.lineRight);

    speedCalc->runCalculation(allignImages, times, roiData, lines);

    auto speed = speedCalc->GetSpeed() * 3.6;

    resultData.speed = speed;

    if (speedCalc->GetType() == SPEED_CALCULATION_LANE) {
        auto laneSpeedCalc =
            std::dynamic_pointer_cast<LaneSpeedCalculator>(speedCalc);
        auto intersectingLines = laneSpeedCalc->GetIntersectingLines();
        resultData.intersectingLines = intersectingLines;
    }

    data->setResultData(resultData);
}