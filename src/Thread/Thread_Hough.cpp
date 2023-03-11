#include <Thread/Thread_Hough.hpp>

HoughThread::HoughThread(wxEvtHandler *parent, ThreadPool *pool,
                         ImageData &imgData)
    : wxThread(wxTHREAD_JOINABLE), m_parent(parent), imgData(imgData),
      pool(pool) {}

HoughThread::~HoughThread() {}

wxThread::ExitCode HoughThread::Entry() {
    HoughEvent startHoughEvent(c_HOUGH_EVENT, HOUGH_START);
    wxPostEvent(m_parent, startHoughEvent);

    Detection::HoughData *houghData = new Detection::HoughData();
    Task *task = new HoughTask(imgData, houghData);
    TaskProperty prop = task->GetProperty();
    pool->AddTaskFront(task);
    while (pool->isWorkerBusy(prop) || pool->HasTasks2(prop)) {
        wxMilliSleep(30);
    }
    HoughEvent endHoughEvent(c_HOUGH_EVENT, HOUGH_END);
    endHoughEvent.SetHoughData(houghData);
    wxPostEvent(m_parent, endHoughEvent);
    task = NULL;
    houghData = NULL;
    return 0;
}