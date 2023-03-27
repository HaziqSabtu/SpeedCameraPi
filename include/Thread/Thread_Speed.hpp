/**
 * @file Thread_Speed.hpp
 * @author Haziq Sabtu (mhaziq.sabtu@gmail.com)
 * @brief Custom wxThread for calculating speed
 * @version 1.0.0
 * @date 2023-03-18
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef SPEED_CALCULATION_THREAD_HPP
#define SPEED_CALCULATION_THREAD_HPP

#include <Event/Event_Speed.hpp>
#include <Thread/Task/Task_Speed.hpp>
#include <Thread/ThreadPool.hpp>
#include <Utils/Config/AppConfig.hpp>
#include <Utils/DataStruct.hpp>
#include <Utils/Struct/D_Line.hpp>
#include <opencv2/opencv.hpp>
#include <string>
#include <wx/thread.h>

/**
 * @brief Custom wxThread for calculating speed
 *
 */
class SpeedThread : public wxThread {
  public:
    SpeedThread(wxEvtHandler *parent, ThreadPool *pool,
                std::vector<ImageData> *imgData,
                std::vector<Detection::Line> &selectedLine,
                SensorConfig sensorConfig);
    ~SpeedThread();

  protected:
    virtual ExitCode Entry();

  private:
    wxEvtHandler *m_parent;
    std::vector<ImageData> *imgData;
    ThreadPool *pool;
    std::vector<Detection::Line> selectedLine;
    SensorConfig sensorConfig;
};

#endif