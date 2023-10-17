#include <Event/Event.hpp>
#include <Thread/Task/Task_Sift.hpp>
#include <Thread/Task/Task_Speed.hpp>
#include <Thread/Task/Task_Track.hpp>
#include <Thread/Thread_Process.hpp>

ProcessThread::ProcessThread(wxEvtHandler *parent, DataPtr data,
                             DetectorPtr detector, TrackerPtr tracker,
                             SpeedCalcPtr speedCalc, POOLPtr threadPool)
    : BaseThread(parent, data), pool(threadPool), detector(detector),
      tracker(tracker), speedCalc(speedCalc) {}

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

        // FeatureDetector detector = FeatureDetector(DetectorType::SIFT);

        detector->Init(data->getCaptureData().at(0).image);

        for (int i = 0; i < MAX_FRAME; i++) {
            DetectorPtr d =
                std::make_shared<FeatureDetector>(detector->clone());
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
            std::make_unique<TrackTask>(data, tracker);
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
            std::make_unique<SpeedTask>(data, speedCalc);
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
