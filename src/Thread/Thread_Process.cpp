#include "Algorithm/speed_calculation/speedCalculation.hpp"
#include "Event/Event_Error.hpp"
#include "Event/Event_UpdatePreview.hpp"
#include "Event/Event_UpdateState.hpp"
#include "Event/Event_UpdateStatus.hpp"
#include "Model/CalibrationData.hpp"
#include "Model/SessionData.hpp"
#include "Thread/ThreadPool.hpp"
#include "Utils/Config/AppConfig.hpp"
#include <Thread/Thread_Process.hpp>
#include <vector>
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

        auto roi = data->getRoiData().roi;
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

        auto roiData = data->getRoiData().trackedRoi;
        // for every rect, cerr the position
        for (int i = 0; i < roiData.size(); i++) {
            if (roiData.at(i).area() <= 0) {
                std::cerr << "ROI " << i << " is empty" << std::endl;
                continue;
            }
            std::cerr << roiData.at(i) << std::endl;
        }

        auto sensorConfig = c.GetSensorConfig();
        SpeedCalculation speedCalc(sensorConfig.SensorWidth,
                                   sensorConfig.SensorFocalLength,
                                   sensorConfig.ObjectWidth);

        auto allignData = data->getAllignData();
        speedCalc.SetImageWidth(allignData.at(0).image.cols);

        std::vector<cv::Mat> allignImages;
        for (auto d : allignData) {
            allignImages.push_back(d.image);
        }

        std::vector<HPTime> times;
        for (auto t : data->getCaptureData()) {
            times.push_back(t.time);
        }

        if (data->isCalibDataEmpty()) {
            throw std::runtime_error("Calibration Data is empty");
        }

        auto calibData = data->getCalibData();
        std::vector<Detection::Line> lines;
        lines.push_back(calibData.lineLeft);
        lines.push_back(calibData.lineRight);

        speedCalc.runCalculation2(allignImages, times, roiData, lines);

        auto speed = speedCalc.GetAvgSpeed();

        std::cerr << "Speed: " << speed << " m/s" << std::endl;

        std::string resultString = "Speed: " + std::to_string(speed) + " m/s, ";
        UpdateStatusEvent::Submit(parent, resultString);

    } catch (const std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }

    // UpdateStatusEvent::Submit(parent, "Stop Process Thread");

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