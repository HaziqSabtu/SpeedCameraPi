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