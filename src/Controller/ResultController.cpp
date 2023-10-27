#include <Controller/ResultController.hpp>

/**
 * @brief Construct a new Result Controller:: Result Controller object
 *
 * @param shared Shared pointer to SharedResource
 */
ResultController::ResultController(ResourcePtr shared)
    : BaseController(shared) {
    panelID = currentPanelID;
}

/**
 * @brief Destroy the Result Controller:: Result Controller object
 *
 */
ResultController::~ResultController() {}

/**
 * @brief Endpoint for Stopping ProcessThread
 *
 * @param parent wxEvtHandler
 */
void ResultController::e_ProcessEnd(wxEvtHandler *parent) {
    try {
        checkPreCondition();
        processEndHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

/**
 * @brief Endpoint for Cancel Button
 *
 * @param parent wxEvtHandler
 */
void ResultController::e_CancelButtonHandler(wxEvtHandler *parent) {
    try {
        checkPreCondition();
        cancelButtonHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

/**
 * @brief Endpoint for initiating ProcessThread with OFTracker
 *
 * @param parent wxEvtHandler
 */
void ResultController::e_ProcessOFStart(wxEvtHandler *parent) {
    try {
        checkPreCondition();
        processOFStartHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

/**
 * @brief Endpoint for stopping ProcessThread with OFTracker
 *
 * @param parent wxEvtHandler
 */
void ResultController::e_ProcessOFEnd(wxEvtHandler *parent) {
    try {
        checkPreCondition();
        processThreadEndHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

/**
 * @brief Endpoint for initiating ProcessThread with CSRTTracker
 *
 * @param parent wxEvtHandler
 */
void ResultController::e_ProcessCSRTStart(wxEvtHandler *parent) {
    try {
        checkPreCondition();
        processCSRTStartHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

/**
 * @brief Endpoint for stopping ProcessThread with CSRTTracker
 *
 * @param parent wxEvtHandler
 */
void ResultController::e_ProcessCSRTEnd(wxEvtHandler *parent) {
    try {
        checkPreCondition();
        processThreadEndHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

/**
 * @brief Endpoint for initiating ProcessThread with OFTracker and
 * LaneSpeedCalculator
 *
 * @param parent wxEvtHandler
 */
void ResultController::e_ProcessLaneOFStart(wxEvtHandler *parent) {
    try {
        checkPreCondition();
        processLaneOFStartHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

/**
 * @brief Endpoint for stopping ProcessThread with OFTracker and
 * LaneSpeedCalculator
 *
 * @param parent wxEvtHandler
 */
void ResultController::e_ProcessLaneOFEnd(wxEvtHandler *parent) {
    try {
        checkPreCondition();
        processThreadEndHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

/**
 * @brief Endpoint for initiating ProcessThread with CSRTTracker and
 * LaneSpeedCalculator
 *
 * @param parent wxEvtHandler
 */
void ResultController::e_ProcessLaneCSRTStart(wxEvtHandler *parent) {
    try {
        checkPreCondition();
        processLaneCSRTStartHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

/**
 * @brief Endpoint for stopping ProcessThread with CSRTTracker and
 * LaneSpeedCalculator
 *
 * @param parent wxEvtHandler
 */
void ResultController::e_ProcessLaneCSRTEnd(wxEvtHandler *parent) {
    try {
        checkPreCondition();
        processThreadEndHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

/**
 * @brief Endpoint for initiating ProcessThread with OFTracker and
 * DistanceSpeedCalculator
 *
 * @param parent wxEvtHandler
 */
void ResultController::e_ProcessDistOFStart(wxEvtHandler *parent) {
    try {
        checkPreCondition();
        processDistOFStartHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

/**
 * @brief Endpoint for stopping ProcessThread with OFTracker and
 * DistanceSpeedCalculator
 *
 * @param parent wxEvtHandler
 */
void ResultController::e_ProcessDistOFEnd(wxEvtHandler *parent) {
    try {
        checkPreCondition();
        processThreadEndHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

/**
 * @brief Endpoint for initiating ProcessThread with CSRTTracker and
 * DistanceSpeedCalculator
 *
 * @param parent wxEvtHandler
 */
void ResultController::e_ProcessDistCSRTStart(wxEvtHandler *parent) {
    try {
        checkPreCondition();
        processDistCSRTStartHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

/**
 * @brief Endpoint for stopping ProcessThread with CSRTTracker and
 * DistanceSpeedCalculator
 *
 * @param parent wxEvtHandler
 */
void ResultController::e_ProcessDistCSRTEnd(wxEvtHandler *parent) {
    try {
        checkPreCondition();
        processThreadEndHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

/**
 * @brief Endpoint for initiating ResultPreviewThread
 *
 * @param parent wxEvtHandler
 */
void ResultController::e_ResultPreviewStart(wxEvtHandler *parent) {
    try {
        checkPreCondition();
        resultPreviewStartHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

/**
 * @brief Endpoint for stopping ResultPreviewThread
 *
 * @param parent wxEvtHandler
 */
void ResultController::e_ResultPreviewEnd(wxEvtHandler *parent) {
    try {
        checkPreCondition();
        resultPreviewEndHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

/**
 * @brief Endpoint for updating speed panel
 *
 * @param parent wxEvtHandler
 */
void ResultController::e_UpdateSpeedPanel(wxEvtHandler *parent) {
    try {
        checkPreCondition();
        updateSpeedPanelHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

/**
 * @brief Endpoint for toggling show bounding box on ResultPreviewPanel
 *
 * @param parent wxEvtHandler
 * @param show true if show, false if hide
 */
void ResultController::e_ToggleShowBox(wxEvtHandler *parent, bool show) {
    try {
        checkPreCondition();
        toggleShowBoxHandler(parent, show);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

/**
 * @brief Endpoint for toggling show intersection lines on ResultPreviewPanel
 *
 * @param parent wxEvtHandler
 * @param show true if show, false if hide
 */
void ResultController::e_ToggleShowLines(wxEvtHandler *parent, bool show) {
    try {
        checkPreCondition();
        toggleShowLinesHandler(parent, show);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

/**
 * @brief Endpoint for toggling show lanes on ResultPreviewPanel
 *
 * @param parent wxEvtHandler
 * @param show true if show, false if hide
 */
void ResultController::e_ToggleShowLanes(wxEvtHandler *parent, bool show) {
    try {
        checkPreCondition();
        toggleShowLanesHandler(parent, show);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

/**
 * @brief Endpoint for setting ResultPreviewPanel image index to 0 (replay)
 *
 * @param parent wxEvtHandler
 */
void ResultController::e_SetIndexToZero(wxEvtHandler *parent) {
    try {
        checkPreCondition();
        setIndexToZeroHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

/**
 * @brief throw exception if any thread is running on ThreadController
 */
void ResultController::throwIfAnyThreadIsRunning() {
    auto tc = shared->getThreadController();

    if (!tc->isThreadNullptr(THREAD_PROCESS)) {
        throw std::runtime_error("ProcessThread is still running");
    }

    if (!tc->isThreadNullptr(THREAD_RESULT_PREVIEW)) {
        throw std::runtime_error("ResultPreviewThread is still running");
    }
}

/**
 * @brief kill all threads on ThreadController
 *
 * @param parent wxEvtHandler
 */
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

/**
 * @brief Handler for initiating ProcessThread with OFTracker
 * @details Check current Mode, if Mode is MODE_LANE, initiate ProcessThread
 * with OFTracker and LaneSpeedCalculator otherwise initiate ProcessThread with
 * OFTracker and DistanceSpeedCalculator
 *
 * @param parent wxEvtHandler
 */
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

/**
 * @brief Handler for initiating ProcessThread with CSRTTracker
 * @details Check current Mode, if Mode is MODE_LANE, initiate ProcessThread
 * with CSRTTracker and LaneSpeedCalculator otherwise initiate ProcessThread
 * with CSRTTracker and DistanceSpeedCalculator
 *
 * @param parent wxEvtHandler
 */
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

/**
 * @brief Handler for initiating ProcessThread with OFTracker and
 * LaneSpeedCalculator
 *
 * @param parent wxEvtHandler
 */
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
    auto detector = AF::createFeatureDetector(c);
    auto tracker = AF::createOFTracker(c);
    auto speedCalc = AF::createLaneSpeedCalculator(c);

    tc->startProcessHandler(parent, pool, sessionData, detector, tracker,
                            speedCalc, panelID);
}

/**
 * @brief Handler for stopping ProcessThread
 *
 * @param parent wxEvtHandler
 */
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

/**
 * @brief Handler for initiating ProcessThread with CSRTTracker and
 * LaneSpeedCalculator
 *
 * @param parent wxEvtHandler
 */
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
    auto detector = AF::createFeatureDetector(c);
    auto tracker = AF::createCSRTTracker(c);
    auto speedCalc = AF::createLaneSpeedCalculator(c);

    tc->startProcessHandler(parent, pool, sessionData, detector, tracker,
                            speedCalc, panelID);
}

/**
 * @brief Handler for initiating ProcessThread with OFTracker and
 * DistanceSpeedCalculator
 *
 * @param parent wxEvtHandler
 */
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
    auto detector = AF::createFeatureDetector(c);
    auto tracker = AF::createOFTracker(c);
    auto speedCalc = AF::createDistanceSpeedCalculator(c);

    tc->startProcessHandler(parent, pool, sessionData, detector, tracker,
                            speedCalc, panelID);
}

/**
 * @brief Handler for initiating ProcessThread with CSRTTracker and
 * DistanceSpeedCalculator
 *
 * @param parent wxEvtHandler
 */
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
    auto detector = AF::createFeatureDetector(c);
    auto tracker = AF::createCSRTTracker(c);
    auto speedCalc = AF::createDistanceSpeedCalculator(c);

    tc->startProcessHandler(parent, pool, sessionData, detector, tracker,
                            speedCalc, panelID);
}

/**
 * @brief Handler for initiating ResultPreviewThread
 *
 * @param parent wxEvtHandler
 */
void ResultController::resultPreviewStartHandler(wxEvtHandler *parent) {
    auto tc = shared->getThreadController();

    throwIfAnyThreadIsRunning();

    auto sessionData = shared->getSessionData();

    auto pool = shared->getThreadPool();

    tc->startResultPreviewHandler(parent, sessionData, panelID);
}

/**
 * @brief Handler for stopping ResultPreviewThread
 *
 * @param parent wxEvtHandler
 */
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

/**
 * @brief Handler for toggling show bounding box on ResultPreviewPanel
 *
 * @param parent wxEvtHandler
 * @param show true if show, false if hide
 */
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

/**
 * @brief Handler for toggling show intersection lines on ResultPreviewPanel
 *
 * @param parent wxEvtHandler
 * @param show true if show, false if hide
 */
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

/**
 * @brief Handler for toggling show lanes on ResultPreviewPanel
 *
 * @param parent wxEvtHandler
 * @param show true if show, false if hide
 */
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

/**
 * @brief Handler for setting ResultPreviewPanel image index to 0 (replay)
 *
 * @param parent wxEvtHandler
 */
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

/**
 * @brief Blocked Endpoint
 * @details ResultPanel does not have OK button
 *
 * @param parent wxEvtHandler
 */
void ResultController::okButtonHandler(wxEvtHandler *parent) {
    throw std::runtime_error("Blocked Endpoint");
}

/**
 * @brief Endpoint for Cancel Button
 * @details Clear ResultData on SessionData and change panel to CapturePanel
 *
 * @param parent wxEvtHandler
 */
void ResultController::cancelButtonHandler(wxEvtHandler *parent) {
    killAllThreads(parent);

    auto sessionData = shared->getSessionData();
    sessionData->clearResultData();

    shared->setSessionData(*sessionData);

    ChangePanelData data(this->panelID, PanelID::PANEL_CAPTURE);
    ChangePanelEvent::Submit(parent, data);
}

/**
 * @brief Endpoint for updating speed panel
 * @details Get speed from ResultData on SessionData and submit it to
 * UpdateSpeedEvent
 *
 * @param parent wxEvtHandler
 */
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

/**
 * @brief Handler for stopping ProcessThread
 *
 * @param parent wxEvtHandler
 */
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

/**
 * @brief Handler for OnShow event
 * @details Check if autoResult is true on ThreadsConfig, if true, initiate
 * ProcessThread with OFTracker
 *
 * @param parent wxEvtHandler
 */
void ResultController::panelShowHandler(wxEvtHandler *parent) {

    AppConfig c;
    auto config = c.GetThreadsConfig();
    auto startThread = config.autoResult;

    if (!startThread) {
        return;
    }

    processOFStartHandler(parent);
}
