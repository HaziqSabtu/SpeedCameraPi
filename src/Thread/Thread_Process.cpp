#include <Thread/Thread_Process.hpp>

ProcessThread::ProcessThread(wxEvtHandler *parent, ThreadPool *threadPool,
                             std::vector<ImageData> *imgData)
    : wxThread(wxTHREAD_JOINABLE), parent(parent), pool(threadPool),
      imgData(imgData) {}

ProcessThread::~ProcessThread() {}

wxThread::ExitCode ProcessThread::Entry() {
    try {
        for (int i = 1; i < imgData->size(); i++) {
            pool->AddTask(new SiftTask(imgData, i));
        }

        // TODO: Update Waiting
        while (pool->isWorkerBusy() || pool->HasTasks(TaskType::TASK_SIFT)) {
            wxMilliSleep(100);
        }

        pool->AddTask(new FlowTask(imgData));
        while (pool->isWorkerBusy() || pool->HasTasks(TaskType::TASK_FLOW)) {
            wxMilliSleep(100);
        }

    } catch (const std::exception &e) {
        std::cout << "ProcessThread::Entry() - Error: \n"
                  << e.what() << std::endl;
    }
    return 0;
}