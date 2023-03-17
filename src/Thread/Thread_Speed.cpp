#include <Thread/Thread_Speed.hpp>

SpeedThread::SpeedThread(wxEvtHandler *parent, ThreadPool *pool,
                         std::vector<ImageData> *imgData,
                         std::vector<Detection::Line> &selectedLine,
                         SensorConfig sensorConfig)
    : wxThread(wxTHREAD_JOINABLE), imgData(imgData), pool(pool),
      selectedLine(selectedLine), sensorConfig(sensorConfig) {
    this->m_parent = parent;
}

SpeedThread::~SpeedThread() {}

wxThread::ExitCode SpeedThread::Entry() {
    std::cout << "Speed Calculation Thread Start" << std::endl;
    std::unique_ptr<float> result;
    SpeedTask *task =
        new SpeedTask(imgData, selectedLine, result, sensorConfig);
    TaskProperty property = task->GetProperty();
    pool->AddTask(task);
    while (pool->isWorkerBusy(property) || pool->HasTasks(property)) {
        wxMilliSleep(100);
    }

    SpeedCalcEvent calcEvent(c_SPEED_CALC_EVENT, CALC_OK);
    calcEvent.SetSpeed(*result);
    wxPostEvent(m_parent, calcEvent);
    return 0;
}