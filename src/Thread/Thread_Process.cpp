#include "Algorithm/image_allign/FeatureDetector.hpp"
#include "Algorithm/speed_calculation/H_speedCalculation.hpp"
#include "Algorithm/speed_calculation/speedCalculation.hpp"
#include "Event/Event_Error.hpp"
#include "Event/Event_ProcessImage.hpp"
#include "Event/Event_UpdatePreview.hpp"
#include "Event/Event_UpdateState.hpp"
#include "Event/Event_UpdateStatus.hpp"
#include "Model/CalibrationData.hpp"
#include "Model/SessionData.hpp"
#include "Thread/Task/Task_OpticalFlow.hpp"
#include "Thread/Task/Task_Speed.hpp"
#include "Thread/ThreadPool.hpp"
#include "Utils/Config/AppConfig.hpp"
#include <Thread/Thread_Process.hpp>
#include <memory>
#include <vector>
#include <wx/event.h>
#include <wx/utils.h>

ProcessThread::ProcessThread(wxEvtHandler *parent, DataPtr data,
                             POOLPtr threadPool)
    : BaseThread(parent, data), pool(threadPool) {}

ProcessThread::~ProcessThread() {}

wxThread::ExitCode ProcessThread::Entry() {
    wxCommandEvent startProcessEvent(c_PROCESS_IMAGE_EVENT, PROCESS_START);
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

        // Track Calculation
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

ProcessRedundantThread::ProcessRedundantThread(wxEvtHandler *parent,
                                               DataPtr data, POOLPtr threadPool)
    : BaseThread(parent, data), pool(threadPool) {}

ProcessRedundantThread::~ProcessRedundantThread() {}

wxThread::ExitCode ProcessRedundantThread::Entry() {
    wxCommandEvent startProcessEvent(c_PROCESS_IMAGE_EVENT, PROCESS_START);
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

        // Track Calculation
        auto roi = data->getTrackingData().roi;
        if (roi.area() <= 0) {
            throw std::runtime_error("ROI is not set");
        }

        std::unique_ptr<Task> csrtTask = std::make_unique<CsrtTask>(data);
        TaskProperty csrtProperty = csrtTask->GetProperty();

        pool->AddTask(csrtTask);
        while (pool->isWorkerBusy(csrtProperty) ||
               pool->HasTasks(csrtProperty)) {
            UpdateStatusEvent::Submit(parent, "Waiting for CSRT Task");
            wxMilliSleep(100);
        }

        // Speed Calculation

        if (data->isCalibrationDataEmpty()) {
            throw std::runtime_error("Calibration Data is empty");
        }

        AppConfig c;
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

ThreadID ProcessRedundantThread::getID() const { return threadID; }

ProcessHorizontalThread::ProcessHorizontalThread(wxEvtHandler *parent,
                                                 DataPtr data,
                                                 POOLPtr threadPool)
    : BaseThread(parent, data), pool(threadPool) {}

ProcessHorizontalThread::~ProcessHorizontalThread() {}

wxThread::ExitCode ProcessHorizontalThread::Entry() {
    wxCommandEvent startProcessEvent(c_PROCESS_IMAGE_EVENT, PROCESS_START);
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

            if (pool->isTaskError(taskProperties)) {
                auto errorData = pool->getErrorData(taskProperties);
                std::string errorString = "Error in Task " +
                                          std::to_string(errorData.threadId) +
                                          " " + errorData.error;

                throw std::runtime_error(errorString);
            }
            wxMilliSleep(500);
        }

        // Track Calculation
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

            if (pool->isTaskError(flowProperty)) {
                auto errorData = pool->getErrorData(flowProperty);
                std::string errorString = "Error in Task " +
                                          std::to_string(errorData.threadId) +
                                          " " + errorData.error;

                throw std::runtime_error(errorString);
            }
            wxMilliSleep(100);
        }

        // Speed Calculation

        if (data->isCalibrationDataEmpty()) {
            throw std::runtime_error("Calibration Data is empty");
        }

        // AppConfig c;
        // SensorConfig sConfig = c.GetSensorConfig();
        // MeasurementConfig mConfig = c.GetMeasurementConfig();

        // std::unique_ptr<Task> speedTask =
        //     std::make_unique<SpeedTask>(data, sConfig, mConfig);
        // TaskProperty speedProperty = speedTask->GetProperty();

        // pool->AddTask(speedTask);
        // while (pool->isWorkerBusy(speedProperty) ||
        //        pool->HasTasks(speedProperty)) {
        //     UpdateStatusEvent::Submit(parent, "Waiting for Speed Task");
        //     wxMilliSleep(100);
        // }

        auto resultData = data->getResultData();
        auto roiData = resultData.trackedRoi;
        auto allignData = resultData.allignData;
        std::vector<cv::Mat> allignImages;
        for (auto d : allignData) {
            allignImages.push_back(d.image);
        }

        std::vector<HPTime> times;
        for (auto t : data->getCaptureData()) {
            times.push_back(t.time);
        }

        if (data->isCalibrationDataEmpty()) {
            throw std::runtime_error("Calibration Data is empty");
        }

        auto calibData = data->getCalibrationData();
        std::vector<Line> lines;
        lines.push_back(calibData.lineLeft);
        lines.push_back(calibData.lineRight);

        HorizontalSpeedCalculation hsc;
        hsc.runCalculation(allignImages, times, roiData, lines);

        // auto speed = data->getResultData().speed;
        auto speed = hsc.GetSpeed() * 3.6;
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

ThreadID ProcessHorizontalThread::getID() const { return threadID; }