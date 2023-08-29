#include "Algorithm/image_allign/FeatureDetector.hpp"
#include "Algorithm/speed_calculation/speedCalculation.hpp"
#include "Event/Event_Error.hpp"
#include "Event/Event_ProcessImage.hpp"
#include "Event/Event_UpdatePreview.hpp"
#include "Event/Event_UpdateState.hpp"
#include "Event/Event_UpdateStatus.hpp"
#include "Model/CalibrationData.hpp"
#include "Model/SessionData.hpp"
#include "Thread/Task/Task_Speed.hpp"
#include "Thread/ThreadPool.hpp"
#include "Utils/Config/AppConfig.hpp"
#include <Thread/Thread_Process.hpp>
#include <memory>
#include <vector>
#include <wx/event.h>
#include <wx/utils.h>

ProcessThread::ProcessThread(wxEvtHandler *parent, POOLPtr threadPool,
                             DataPtr data)
    : wxThread(wxTHREAD_JOINABLE), parent(parent), pool(threadPool),
      data(data) {}

ProcessThread::~ProcessThread() {}

wxThread::ExitCode ProcessThread::Entry() {
    wxCommandEvent startProcessEvent(c_PROCESS_IMAGE_EVENT, PROCESS_BEGIN);
    wxPostEvent(parent, startProcessEvent);

    UpdateStatusEvent::Submit(parent, "Starting Process Thread");
    try {

        if (data->isCaptureDataEmpty()) {
            throw std::runtime_error("Capture Data is empty");
        }

        if (!data->isResultDataEmpty()) {
            throw std::runtime_error("Result Data already exists");
        }

        auto captureSize = data->getCaptureData().size();
        data->initAllignData(captureSize);

        std::vector<TaskProperty> taskProperties;

        const int MAX_FRAME = data->getCaptureData().size();

        FeatureDetector detector = FeatureDetector(DetectorType::SIFT);

        detector.Init(data->getCaptureData().at(0).image);

        for (int i = 0; i < MAX_FRAME; i++) {
            FeatureDetector d = detector.clone();
            std::unique_ptr<Task> task = std::make_unique<SiftTask>(d, data, i);
            taskProperties.push_back(task->GetProperty());
            pool->AddTask(task);
        }

        int count;
        while ((count = pool->countTasks(taskProperties)) > 0) {
            UpdateStatusEvent::Submit(
                parent, "Waiting for " + std::to_string(count) + " tasks");
            wxMilliSleep(500);
        }

        // Speed Calculation
        auto roi = data->getTrackingData().roi;
        if (roi.area() <= 0) {
            throw std::runtime_error("ROI is not set");
        }

        AppConfig c;
        OpticalFlowConfig ofConfig = c.GetOpticalFlowConfig();

        std::unique_ptr<Task> flowTask =
            std::make_unique<FlowTask>(data, ofConfig);
        TaskProperty flowProperty = flowTask->GetProperty();

        pool->AddTask(flowTask);
        while (pool->isWorkerBusy(flowProperty) ||
               pool->HasTasks(flowProperty)) {
            UpdateStatusEvent::Submit(parent, "Waiting for Flow Task");
            wxMilliSleep(100);
        }

        // Speed Calculation

        if (data->isCalibrationDataEmpty()) {
            throw std::runtime_error("Calibration Data is empty");
        }

        SensorConfig sConfig = c.GetSensorConfig();
        MeasurementConfig mConfig = c.GetMeasurementConfig();

        std::unique_ptr<Task> speedTask =
            std::make_unique<SpeedTask>(data, sConfig, mConfig);
        TaskProperty speedProperty = speedTask->GetProperty();

        pool->AddTask(speedTask);
        while (pool->isWorkerBusy(speedProperty) ||
               pool->HasTasks(speedProperty)) {
            UpdateStatusEvent::Submit(parent, "Waiting for Speed Task");
            wxMilliSleep(100);
        }

        auto speed = data->getResultData().speed;
        std::string resultString = "Speed: " + std::to_string(speed) + " km/h";
        UpdateStatusEvent::Submit(parent, resultString);
    } catch (const std::exception &e) {
        wxCommandEvent errorProcessEvent(c_PROCESS_IMAGE_EVENT, PROCESS_ERROR);
        wxPostEvent(parent, errorProcessEvent);

        ErrorEvent::Submit(parent, e.what());
    }

    wxCommandEvent endProcessEvent(c_PROCESS_IMAGE_EVENT, PROCESS_END);
    wxPostEvent(parent, endProcessEvent);

    return 0;
}

ThreadID ProcessThread::getID() const { return threadID; }