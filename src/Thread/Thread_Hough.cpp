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
    std::cout << "Hough Thread 0" << std::endl;
    if (houghData->canny.empty()) {
        std::cout << "Canny is Empty" << std::endl;
    } else {
        std::cout << "Canny is not Empty" << std::endl;
    }
    pool->AddTaskFront(new HoughTask(imgData, houghData));
    while (pool->isWorkerBusy() || pool->HasTasks(TaskType::TASK_HOUGHLINE)) {
        // std::cout << "waiting for hough to finish" << std::endl;
        wxMilliSleep(30);
    }
    std::cout << "Hough Thread 1" << std::endl;
    if (houghData->canny.empty()) {
        std::cout << "Canny is Empty" << std::endl;
    } else {
        std::cout << "Canny is not Empty" << std::endl;
    }
    HoughEvent endHoughEvent(c_HOUGH_EVENT, HOUGH_END);
    wxPostEvent(m_parent, endHoughEvent);
    return 0;
}