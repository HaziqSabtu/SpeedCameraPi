#include "Algorithm/speed_calculation/speedCalculation.hpp"
#include "Event/Event_Error.hpp"
#include "Event/Event_ProcessImage.hpp"
#include "Event/Event_UpdatePreview.hpp"
#include "Event/Event_UpdateState.hpp"
#include "Event/Event_UpdateStatus.hpp"
#include "Model/CalibrationData.hpp"
#include "Model/SessionData.hpp"
#include "Thread/ThreadPool.hpp"
#include "Utils/Config/AppConfig.hpp"
#include <Thread/Thread_Process.hpp>
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
        auto roiData = data->getTrackingData().trackedRoi;

        auto sensorConfig = c.GetSensorConfig();

        SpeedCalculation speedCalc;
        speedCalc.SetSensorWidth(sensorConfig.SensorWidth);
        speedCalc.SetFocalLength(sensorConfig.SensorFocalLength);

        auto measurementConfig = c.GetMeasurementConfig();
        speedCalc.SetLaneWidth(measurementConfig.ObjectWidth);

        auto allignData = data->getAllignData();

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

        speedCalc.runCalculation(allignImages, times, roiData, lines);

        auto speed = speedCalc.GetTrimmedAverageSpeed(20) * 3.6;

        auto speedList = speedCalc.GetRawSpeed();
        auto distanceFromCamera = speedCalc.GetDistanceFromCamera();
        auto intersectingLines = speedCalc.GetIntersectingLines();

        ResultData resultData;
        resultData.speed = speed;
        resultData.speedList = speedList;
        resultData.distanceFromCamera = distanceFromCamera;
        resultData.intersectingLines = intersectingLines;

        data->setResultData(resultData);

        std::string resultString = "Speed: " + std::to_string(speed) + " km/h";
        UpdateStatusEvent::Submit(parent, resultString);

        // TODO: temp
        Utils::FileReadWrite f;
        f.WriteFile(data);

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