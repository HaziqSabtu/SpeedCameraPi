#include "Algorithm/object_tracker/CSRTTracker.hpp"
#include "Algorithm/speed_calculation/H_speedCalculation.hpp"
#include "Algorithm/speed_calculation/speedCalculation.hpp"
#include "Event/Event_UpdateStatus.hpp"
#include "Thread/Thread_ID.hpp"
#include "UI/Data/StatusData.hpp"
#include <Controller/ResultController.hpp>
#include <wx/event.h>

ResultController::ResultController(ModelPtr sharedModel)
    : BaseController(sharedModel) {
    panelID = currentPanelID;
}

ResultController::~ResultController() {}

void ResultController::e_ProcessEnd(wxEvtHandler *parent) {
    try {
        checkPreCondition();
        processEndHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void ResultController::e_CancelButtonHandler(wxEvtHandler *parent) {
    try {
        checkPreCondition();
        cancelButtonHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void ResultController::e_ProcessOFStart(wxEvtHandler *parent) {
    try {
        checkPreCondition();
        processOFStartHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void ResultController::e_ProcessOFEnd(wxEvtHandler *parent) {
    try {
        checkPreCondition();
        processThreadEndHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void ResultController::e_ProcessCSRTStart(wxEvtHandler *parent) {
    try {
        checkPreCondition();
        processCSRTStartHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void ResultController::e_ProcessCSRTEnd(wxEvtHandler *parent) {
    try {
        checkPreCondition();
        processThreadEndHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void ResultController::e_ProcessLaneOFStart(wxEvtHandler *parent) {
    try {
        checkPreCondition();
        processLaneOFStartHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void ResultController::e_ProcessLaneOFEnd(wxEvtHandler *parent) {
    try {
        checkPreCondition();
        processThreadEndHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void ResultController::e_ProcessLaneCSRTStart(wxEvtHandler *parent) {
    try {
        checkPreCondition();
        processLaneCSRTStartHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void ResultController::e_ProcessLaneCSRTEnd(wxEvtHandler *parent) {
    try {
        checkPreCondition();
        processThreadEndHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void ResultController::e_ProcessDistOFStart(wxEvtHandler *parent) {
    try {
        checkPreCondition();
        processDistOFStartHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void ResultController::e_ProcessDistOFEnd(wxEvtHandler *parent) {
    try {
        checkPreCondition();
        processThreadEndHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void ResultController::e_ProcessDistCSRTStart(wxEvtHandler *parent) {
    try {
        checkPreCondition();
        processDistCSRTStartHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void ResultController::e_ProcessDistCSRTEnd(wxEvtHandler *parent) {
    try {
        checkPreCondition();
        processThreadEndHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void ResultController::e_ResultPreviewStart(wxEvtHandler *parent) {
    try {
        checkPreCondition();
        resultPreviewStartHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void ResultController::e_ResultPreviewEnd(wxEvtHandler *parent) {
    try {
        checkPreCondition();
        resultPreviewEndHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void ResultController::e_UpdateSpeedPanel(wxEvtHandler *parent) {
    try {
        checkPreCondition();
        updateSpeedPanelHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void ResultController::e_ToggleShowBox(wxEvtHandler *parent, bool show) {
    try {
        checkPreCondition();
        toggleShowBoxHandler(parent, show);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void ResultController::e_ToggleShowLines(wxEvtHandler *parent, bool show) {
    try {
        checkPreCondition();
        toggleShowLinesHandler(parent, show);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void ResultController::e_ToggleShowLanes(wxEvtHandler *parent, bool show) {
    try {
        checkPreCondition();
        toggleShowLanesHandler(parent, show);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void ResultController::e_SetIndexToZero(wxEvtHandler *parent) {
    try {
        checkPreCondition();
        setIndexToZeroHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void ResultController::throwIfAnyThreadIsRunning() {
    auto tc = shared->getThreadController();

    if (!tc->isThreadNullptr(THREAD_PROCESS)) {
        throw std::runtime_error("ProcessThread is still running");
    }

    if (!tc->isThreadNullptr(THREAD_RESULT_PREVIEW)) {
        throw std::runtime_error("ResultPreviewThread is still running");
    }
}

void ResultController::killAllThreads(wxEvtHandler *parent) {
    auto tc = shared->getThreadController();

    if (!tc->isThreadNullptr(THREAD_PROCESS)) {
        processThreadEndHandler(parent);
    }

    if (!tc->isThreadNullptr(THREAD_RESULT_PREVIEW)) {
        resultPreviewEndHandler(parent);
    }

    throwIfAnyThreadIsRunning();
}

void ResultController::processOFStartHandler(wxEvtHandler *parent) {
    auto data = shared->getSessionData();

    if (data->getMode() == Mode::MODE_LANE) {
        processLaneOFStartHandler(parent);
    } else if (data->getMode() == Mode::MODE_DISTANCE) {
        processDistOFStartHandler(parent);
    } else {
        throw std::runtime_error("Invalid mode");
    }
}

void ResultController::processCSRTStartHandler(wxEvtHandler *parent) {
    auto data = shared->getSessionData();

    if (data->getMode() == Mode::MODE_LANE) {
        processLaneCSRTStartHandler(parent);
    } else if (data->getMode() == Mode::MODE_DISTANCE) {
        processDistCSRTStartHandler(parent);
    } else {
        throw std::runtime_error("Invalid mode");
    }
}

void ResultController::processLaneOFStartHandler(wxEvtHandler *parent) {
    auto tc = shared->getThreadController();

    throwIfAnyThreadIsRunning();

    auto sessionData = shared->getSessionData();

    if (!sessionData->isResultDataEmpty()) {
        sessionData->clearResultData();
        shared->setSessionData(*sessionData);
    }

    auto pool = shared->getThreadPool();

    AppConfig c;
    auto ofConfig = c.GetOpticalFlowConfig();
    auto sConfig = c.GetSensorConfig();
    auto mConfig = c.GetMeasurementConfig();

    DetectorPtr detector =
        std::make_shared<FeatureDetector>(DetectorType::SIFT);

    auto tracker = std::make_shared<OFTracker>();
    tracker->SetMaxCorners(ofConfig.maxCorners);
    tracker->SetQualityLevel(ofConfig.qualityLevel);
    tracker->SetMinDistance(ofConfig.minDistance);
    tracker->SetBlockSize(ofConfig.blockSize);
    tracker->SetUseHarrisDetector(ofConfig.useHarrisDetector);
    tracker->SetK(ofConfig.k);
    tracker->SetMinPointDistance(ofConfig.minPointDistance);
    tracker->SetThreshold(ofConfig.threshold);

    auto speedCalc = std::make_shared<LaneSpeedCalculation>();
    speedCalc->SetSensorWidth(sConfig.SensorWidth);
    speedCalc->SetFocalLength(sConfig.SensorFocalLength);
    speedCalc->SetLaneWidth(mConfig.ObjectWidth);

    tc->startProcessHandler(parent, pool, sessionData, detector, tracker,
                            speedCalc, panelID);
}

void ResultController::processThreadEndHandler(wxEvtHandler *parent) {
    auto tc = shared->getThreadController();

    if (tc->isThreadNullptr(ThreadID::THREAD_PROCESS)) {
        throw std::runtime_error("ProcessThread is already stopped");
    }

    if (!tc->isThreadOwner(ThreadID::THREAD_PROCESS, panelID)) {
        throw std::runtime_error("ProcessThread is not owned by "
                                 "this controller");
    }

    tc->endProcessHandler();
}

void ResultController::processLaneCSRTStartHandler(wxEvtHandler *parent) {

    auto tc = shared->getThreadController();

    throwIfAnyThreadIsRunning();

    auto sessionData = shared->getSessionData();

    if (!sessionData->isResultDataEmpty()) {
        sessionData->clearResultData();
        shared->setSessionData(*sessionData);
    }

    auto pool = shared->getThreadPool();

    AppConfig c;
    auto sConfig = c.GetSensorConfig();
    auto mConfig = c.GetMeasurementConfig();

    DetectorPtr detector =
        std::make_shared<FeatureDetector>(DetectorType::SIFT);

    auto tracker = std::make_shared<CSRTTracker>();

    auto speedCalc = std::make_shared<LaneSpeedCalculation>();
    speedCalc->SetSensorWidth(sConfig.SensorWidth);
    speedCalc->SetFocalLength(sConfig.SensorFocalLength);
    speedCalc->SetLaneWidth(mConfig.ObjectWidth);

    tc->startProcessHandler(parent, pool, sessionData, detector, tracker,
                            speedCalc, panelID);
}

void ResultController::processDistOFStartHandler(wxEvtHandler *parent) {
    auto tc = shared->getThreadController();

    throwIfAnyThreadIsRunning();

    auto sessionData = shared->getSessionData();

    if (!sessionData->isResultDataEmpty()) {
        sessionData->clearResultData();
        shared->setSessionData(*sessionData);
    }

    auto pool = shared->getThreadPool();

    AppConfig c;
    auto ofConfig = c.GetOpticalFlowConfig();
    auto mConfig = c.GetMeasurementConfig();

    DetectorPtr detector =
        std::make_shared<FeatureDetector>(DetectorType::SIFT);

    auto tracker = std::make_shared<OFTracker>();
    tracker->SetMaxCorners(ofConfig.maxCorners);
    tracker->SetQualityLevel(ofConfig.qualityLevel);
    tracker->SetMinDistance(ofConfig.minDistance);
    tracker->SetBlockSize(ofConfig.blockSize);
    tracker->SetUseHarrisDetector(ofConfig.useHarrisDetector);
    tracker->SetK(ofConfig.k);
    tracker->SetMinPointDistance(ofConfig.minPointDistance);
    tracker->SetThreshold(ofConfig.threshold);

    auto speedCalc = std::make_shared<DistanceSpeedCalculation>();
    speedCalc->setObjectLength(mConfig.ObjectHeight);

    tc->startProcessHandler(parent, pool, sessionData, detector, tracker,
                            speedCalc, panelID);
}

void ResultController::processDistCSRTStartHandler(wxEvtHandler *parent) {
    auto tc = shared->getThreadController();

    throwIfAnyThreadIsRunning();

    auto sessionData = shared->getSessionData();

    if (!sessionData->isResultDataEmpty()) {
        sessionData->clearResultData();
        shared->setSessionData(*sessionData);
    }

    auto pool = shared->getThreadPool();

    AppConfig c;
    auto mConfig = c.GetMeasurementConfig();

    DetectorPtr detector =
        std::make_shared<FeatureDetector>(DetectorType::SIFT);

    auto tracker = std::make_shared<CSRTTracker>();

    auto speedCalc = std::make_shared<DistanceSpeedCalculation>();
    speedCalc->setObjectLength(mConfig.ObjectHeight);

    tc->startProcessHandler(parent, pool, sessionData, detector, tracker,
                            speedCalc, panelID);
}

void ResultController::resultPreviewStartHandler(wxEvtHandler *parent) {
    auto tc = shared->getThreadController();

    throwIfAnyThreadIsRunning();

    auto sessionData = shared->getSessionData();

    auto pool = shared->getThreadPool();

    tc->startResultPreviewHandler(parent, sessionData, panelID);
}

void ResultController::resultPreviewEndHandler(wxEvtHandler *parent) {
    auto tc = shared->getThreadController();

    if (tc->isThreadNullptr(ThreadID::THREAD_RESULT_PREVIEW)) {
        throw std::runtime_error("ResultPreviewThread is already stopped");
    }

    if (!tc->isThreadOwner(ThreadID::THREAD_RESULT_PREVIEW, panelID)) {
        throw std::runtime_error("ResultPreviewThread is not owned by "
                                 "this controller");
    }

    tc->endResultPreviewHandler();
}

void ResultController::toggleShowBoxHandler(wxEvtHandler *parent, bool show) {
    auto tc = shared->getThreadController();
    if (tc->isThreadNullptr(THREAD_RESULT_PREVIEW)) {
        throw std::runtime_error("ResultPreviewThread is not running");
    }

    if (!tc->isThreadOwner(THREAD_RESULT_PREVIEW, panelID)) {
        throw std::runtime_error(
            "ResultPreviewThread is not owned by this controller");
    }

    auto thread = tc->getResultPreviewThread();
    thread->SetShowBox(show);

    show ? UpdateStatusEvent::Submit(parent,
                                     SC::STATUS_RESULT_PREVIEW_SHOWBOX_ON)
         : UpdateStatusEvent::Submit(parent,
                                     SC::STATUS_RESULT_PREVIEW_SHOWBOX_OFF);
}

void ResultController::toggleShowLinesHandler(wxEvtHandler *parent, bool show) {
    auto tc = shared->getThreadController();
    if (tc->isThreadNullptr(THREAD_RESULT_PREVIEW)) {
        throw std::runtime_error("ResultPreviewThread is not running");
    }

    if (!tc->isThreadOwner(THREAD_RESULT_PREVIEW, panelID)) {
        throw std::runtime_error(
            "ResultPreviewThread is not owned by this controller");
    }

    auto thread = tc->getResultPreviewThread();
    thread->SetShowIntersection(show);

    show ? UpdateStatusEvent::Submit(parent,
                                     SC::STATUS_RESULT_PREVIEW_SHOWLINES_ON)
         : UpdateStatusEvent::Submit(parent,
                                     SC::STATUS_RESULT_PREVIEW_SHOWLINES_OFF);
}

void ResultController::toggleShowLanesHandler(wxEvtHandler *parent, bool show) {
    auto tc = shared->getThreadController();
    if (tc->isThreadNullptr(THREAD_RESULT_PREVIEW)) {
        throw std::runtime_error("ResultPreviewThread is not running");
    }

    if (!tc->isThreadOwner(THREAD_RESULT_PREVIEW, panelID)) {
        throw std::runtime_error(
            "ResultPreviewThread is not owned by this controller");
    }

    auto thread = tc->getResultPreviewThread();
    thread->SetShowLanes(show);

    show ? UpdateStatusEvent::Submit(parent,
                                     SC::STATUS_RESULT_PREVIEW_SHOWLANES_ON)
         : UpdateStatusEvent::Submit(parent,
                                     SC::STATUS_RESULT_PREVIEW_SHOWLANES_OFF);
}

void ResultController::setIndexToZeroHandler(wxEvtHandler *parent) {
    auto tc = shared->getThreadController();
    if (tc->isThreadNullptr(THREAD_RESULT_PREVIEW)) {
        throw std::runtime_error("ResultPreviewThread is not running");
    }

    if (!tc->isThreadOwner(THREAD_RESULT_PREVIEW, panelID)) {
        throw std::runtime_error(
            "ResultPreviewThread is not owned by this controller");
    }

    auto thread = tc->getResultPreviewThread();
    thread->SetImageIndex(0);

    UpdateStatusEvent::Submit(parent, SC::STATUS_RESULT_PREVIEW_REPLAY);
}

void ResultController::okButtonHandler(wxEvtHandler *parent) {
    throw std::runtime_error("Blocked Endpoint");
}

void ResultController::cancelButtonHandler(wxEvtHandler *parent) {
    killAllThreads(parent);

    auto sessionData = shared->getSessionData();
    sessionData->clearResultData();

    shared->setSessionData(*sessionData);

    ChangePanelData data(this->panelID, PanelID::PANEL_CAPTURE);
    ChangePanelEvent::Submit(parent, data);
}

void ResultController::updateSpeedPanelHandler(wxEvtHandler *parent) {
    auto data = shared->getSessionData();

    if (data->isResultDataEmpty()) {
        throw std::runtime_error("Result Data is empty");
    }

    auto resultData = data->getResultData();
    auto speed = resultData.speed;

    if (speed < 0) {
        throw std::runtime_error("Invalid speed");
    }

    UpdateSpeedEvent::Submit(parent, speed);
}

void ResultController::processEndHandler(wxEvtHandler *parent) {
    auto tc = shared->getThreadController();

    if (!tc->isProcessThreadRunning()) {
        throw std::runtime_error("Process thread is not running");
    }

    if (!tc->isProcessThreadOwner(panelID)) {
        throw std::runtime_error("Process thread is not owned by this panel");
    }

    auto thread = tc->getRunningProcessThread();

    if (thread->getID() == THREAD_PROCESS) {
        processThreadEndHandler(parent);
        return;
    }

    throw std::runtime_error("Invalid thread ID");
}

void ResultController::panelShowHandler(wxEvtHandler *parent) {

    AppConfig c;
    auto config = c.GetThreadsConfig();
    auto startThread = config.autoResult;

    if (!startThread) {
        return;
    }

    processOFStartHandler(parent);
}
