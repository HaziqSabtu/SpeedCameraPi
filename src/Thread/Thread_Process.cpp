#include <Thread/Thread_Process.hpp>

ProcessThread::ProcessThread(wxEvtHandler *parent, ThreadPool *threadPool,
                             std::vector<ImageData> *imgData,
                             OpticalFlowConfig ofConfig)
    : wxThread(wxTHREAD_JOINABLE), parent(parent), pool(threadPool),
      imgData(imgData), ofConfig(ofConfig) {}

ProcessThread::~ProcessThread() {}

wxThread::ExitCode ProcessThread::Entry() {
    try {
        std::vector<TaskProperty> taskProperties;
        for (int i = 1; i < imgData->size(); i++) {
            SiftTask *task = new SiftTask(imgData, i);
            taskProperties.push_back(task->GetProperty());
            pool->AddTask(task);
            task = NULL;
        }

        // TODO: Update Waiting
        while (pool->isWorkerBusy(taskProperties) ||
               pool->HasTasks(taskProperties)) {
            wxMilliSleep(100);
        }

        FlowTask *flowTask = new FlowTask(imgData, ofConfig);
        TaskProperty flowProperty = flowTask->GetProperty();
        pool->AddTask(flowTask);
        while (pool->isWorkerBusy(flowProperty) ||
               pool->HasTasks(flowProperty)) {
            wxMilliSleep(100);
        }

    } catch (const std::exception &e) {
        std::cout << "ProcessThread::Entry() - Error: \n"
                  << e.what() << std::endl;
    }

    wxCommandEvent processImageEvent(c_PROCESS_IMAGE_EVENT, PROCESS_END);
    wxPostEvent(parent, processImageEvent);
    return 0;
}