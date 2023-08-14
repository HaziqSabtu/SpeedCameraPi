/**
 * @file Thread_Speed.cpp
 * @author Haziq Sabtu (mhaziq.sabtu@gmail.com)
 * @brief Custom wxThread for calculating speed
 * @version 1.0.0
 * @date 2023-03-18
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <Thread/Thread_Speed.hpp>

/**
 * @brief Construct a new Speed Thread:: Speed Thread object
 *
 * @param parent parent window
 * @param pool pointer to ThreadPool
 * @param imgData pointer to vector of ImageData
 * @param selectedLine vector of selected line
 * @param sensorConfig SensorConfig
 */
SpeedThread::SpeedThread(wxEvtHandler *parent, ThreadPool *pool,
                         std::vector<ImageData> *imgData,
                         std::vector<Line> &selectedLine,
                         SensorConfig sensorConfig)
    : wxThread(wxTHREAD_JOINABLE), imgData(imgData), pool(pool),
      selectedLine(selectedLine), sensorConfig(sensorConfig) {
    this->m_parent = parent;
}

/**
 * @brief Destroy the Speed Thread:: Speed Thread object
 *
 */
SpeedThread::~SpeedThread() {}

/**
 * @brief Entry point of the thread
 * @details This function will be called when the thread is started
 * <ul>
 * <li>SpeedTask is created and added to the thread pool</li>
 * <li>Wait for the thread pool to finish calculating the speed</li>
 * <li>Post SpeedCalcEvent to parent window</li>
 * </ul>
 *
 * @return wxThread::ExitCode
 */
wxThread::ExitCode SpeedThread::Entry() {
    // std::cout << "Speed Calculation Thread Start" << std::endl;
    // std::unique_ptr<float> result;
    // SpeedTask *task =
    //     new SpeedTask(imgData, selectedLine, result, sensorConfig);
    // TaskProperty property = task->GetProperty();
    // pool->AddTask(task);
    // while (pool->isWorkerBusy(property) || pool->HasTasks(property)) {
    //     wxMilliSleep(100);
    // }

    // SpeedCalcEvent calcEvent(c_SPEED_CALC_EVENT, CALC_OK);
    // calcEvent.SetSpeed(*result);
    // wxPostEvent(m_parent, calcEvent);
    return 0;
}