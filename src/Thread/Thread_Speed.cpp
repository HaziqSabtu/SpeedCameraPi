#include <Thread/Thread_Speed.hpp>

SpeedThread::SpeedThread(wxEvtHandler *parent, ThreadPool *pool,
                         std::vector<ImageData> *imgData,
                         std::vector<Detection::Line> &selectedLine)
    : wxThread(wxTHREAD_JOINABLE), imgData(imgData), pool(pool),
      selectedLine(selectedLine) {
    this->m_parent = parent;
}

SpeedThread::~SpeedThread() {}

wxThread::ExitCode SpeedThread::Entry() {
    std::cout << "Speed Calculation Thread Start" << std::endl;
    std::unique_ptr<float> result;
    SpeedTask *task = new SpeedTask(imgData, selectedLine, result);
    TaskProperty property = task->GetProperty();
    pool->AddTask(task);
    while (pool->isWorkerBusy(property) || pool->HasTasks2(property)) {
        wxMilliSleep(100);
    }

    SpeedCalcEvent e(c_SPEED_CALC_EVENT, CALC_OK);
    e.SetSpeed(*result);
    wxPostEvent(m_parent, e);
    return 0;
}