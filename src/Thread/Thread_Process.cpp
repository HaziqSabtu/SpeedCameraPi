/**
 * @file Thread_Process.cpp
 * @author Haziq Sabtu (mhaziq.sabtu@gmail.com)
 * @brief Custom wxThread for processing ImageData
 * @version 1.0.0
 * @date 2023-03-18
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <Thread/Thread_Process.hpp>

/**
 * @brief Construct a new Process Thread:: Process Thread object
 *
 * @param parent parent wxEvtHandler
 * @param threadPool pointer to ThreadPool
 * @param imgData pointer to ImageData vector
 * @param ofConfig OpticalFlowConfig
 */
ProcessThread::ProcessThread(wxEvtHandler *parent, ThreadPool *threadPool,
                             std::vector<ImageData> *imgData,
                             OpticalFlowConfig ofConfig)
    : wxThread(wxTHREAD_JOINABLE), parent(parent), pool(threadPool),
      imgData(imgData), ofConfig(ofConfig) {}

/**
 * @brief Destroy the Process Thread:: Process Thread object
 *
 */
ProcessThread::~ProcessThread() {}

/**
 * @brief Entry point of the thread
 * @details This function will be called when the thread is started
 * <ul>
 * <li>For each ImageData in the vector, SiftTask is created and added to the
 * thread pool</li>
 * <li>Wait for the thread pool to finish processing the ImageData</li>
 * <li>FlowTask is created and added to the thread pool</li>
 * <li>Wait for the thread pool to finish processing the ImageData</li>
 * </ul>
 *
 * @return wxThread::ExitCode
 */
wxThread::ExitCode ProcessThread::Entry() {
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
    while (pool->isWorkerBusy(flowProperty) || pool->HasTasks(flowProperty)) {
        wxMilliSleep(100);
    }

    wxCommandEvent processImageEvent(c_PROCESS_IMAGE_EVENT, PROCESS_END);
    wxPostEvent(parent, processImageEvent);

    return 0;
}