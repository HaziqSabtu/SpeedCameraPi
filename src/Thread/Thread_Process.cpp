#include "Event/Event_Error.hpp"
#include "Event/Event_UpdatePreview.hpp"
#include "Event/Event_UpdateState.hpp"
#include "Event/Event_UpdateStatus.hpp"
#include "Model/CalibrationData.hpp"
#include "Model/SessionData.hpp"
#include "Thread/ThreadPool.hpp"
#include <Thread/Thread_Process.hpp>
#include <wx/utils.h>

ProcessThread::ProcessThread(wxEvtHandler *parent, POOLPtr threadPool,
                             DataPtr data)
    : wxThread(wxTHREAD_JOINABLE), parent(parent), pool(threadPool),
      data(data) {}

ProcessThread::~ProcessThread() {}

wxThread::ExitCode ProcessThread::Entry() {
    UpdateStatusEvent::Submit(parent, "Starting Process Thread");
    try {

        if (data->isCaptureDataEmpty()) {
            throw std::runtime_error("Capture Data is empty");
        }

        if (!data->isAllignDataEmpty()) {
            throw std::runtime_error("Allign Data already exists");
        }

        data->initAllignData();

        std::vector<TaskProperty> taskProperties;

        const int MAX_FRAME = data->getCaptureData().size();

        for (int i = 0; i < MAX_FRAME; i++) {
            std::unique_ptr<Task> task = std::make_unique<SiftTask>(data, i);
            taskProperties.push_back(task->GetProperty());
            pool->AddTask(task);
        }

        int count;
        while ((count = pool->countTasks(taskProperties)) > 0) {
            UpdateStatusEvent::Submit(
                parent, "Waiting for " + std::to_string(count) + " tasks");
            wxMilliSleep(500);
        }

    } catch (const std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }

    UpdateStatusEvent::Submit(parent, "Stop Process Thread");

    // for (int i = 0; i < imgData->size(); i++) {
    //     cv::Mat frame = imgData->at(i).allign.image;
    //     UpdatePreviewEvent updatePreviewEvent(c_UPDATE_PREVIEW_EVENT,
    //                                           UPDATE_PREVIEW);
    //     updatePreviewEvent.SetImage(frame);
    //     wxPostEvent(parent, updatePreviewEvent);
    //     wxMilliSleep(200);
    // }

    // FlowTask *flowTask = new FlowTask(imgData, ofConfig);
    // TaskProperty flowProperty = flowTask->GetProperty();
    // pool->AddTask(flowTask);
    // while (pool->isWorkerBusy(flowProperty) ||
    // pool->HasTasks(flowProperty)) {
    //     wxMilliSleep(100);
    // }

    // wxCommandEvent processImageEvent(c_PROCESS_IMAGE_EVENT,
    // PROCESS_END); wxPostEvent(parent, processImageEvent);

    return 0;
}

ThreadID ProcessThread::getID() const { return threadID; }