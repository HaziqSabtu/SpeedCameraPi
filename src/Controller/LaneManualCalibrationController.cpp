#include <Controller/LaneManualCalibrationController.hpp>

#include <UI/Dialog/RemoveCalibrationDialog.hpp>

/**
 * @brief Construct a new Lane Manual Calibration Controller:: Lane Manual
 Calibration Controller object
 *
 * @param shared Shared pointer to SharedResource
 */
LaneManualCalibrationController::LaneManualCalibrationController(
    ResourcePtr shared)
    : BaseControllerWithTouch(shared) {
    panelID = currentPanelID;
}

/**
 * @brief Destroy the Lane Manual Calibration Controller:: Lane Manual
 * Calibration Controller object
 *
 */
LaneManualCalibrationController::~LaneManualCalibrationController() {}

/**
 * @brief throw an exception if any thread on ThreadController is running
 *
 */
void LaneManualCalibrationController::throwIfAnyThreadIsRunning() {
    auto tc = shared->getThreadController();

    if (!tc->isThreadNullptr(THREAD_LANE_MANUAL_CALIBRATION_CAMERA)) {
        throw std::runtime_error("manualCalibThread is running");
    }

    if (!tc->isThreadNullptr(THREAD_LANE_MANUAL_CALIBRATION_CAPTURE)) {
        throw std::runtime_error("manualCalibCapTureThread is running");
    }

    if (!tc->isThreadNullptr(THREAD_CALIBRATION_PREVIEW_CAPTURE)) {
        throw std::runtime_error("calibCapPrevThread is running");
    }

    if (!tc->isThreadNullptr(THREAD_CALIBRATION_PREVIEW_CAMERA)) {
        throw std::runtime_error("calibPrevThread is running");
    }
}

/**
 * @brief kill all running threads on ThreadController
 *
 * @param parent
 */
void LaneManualCalibrationController::killAllThreads(wxEvtHandler *parent) {
    auto tc = shared->getThreadController();

    if (!tc->isThreadNullptr(THREAD_LANE_MANUAL_CALIBRATION_CAMERA)) {
        manualCalibrationCameraEndHandler(parent);
    }

    if (!tc->isThreadNullptr(THREAD_LANE_MANUAL_CALIBRATION_CAPTURE)) {
        manualCalibrationCaptureEndHandler(parent);
    }

    if (!tc->isThreadNullptr(THREAD_CALIBRATION_PREVIEW_CAPTURE)) {
        calibrationPreviewCaptureEndHandler(parent);
    }

    if (!tc->isThreadNullptr(THREAD_CALIBRATION_PREVIEW_CAMERA)) {
        calibrationPreviewCameraEndHandler(parent);
    }

    throwIfAnyThreadIsRunning();
}

/**
 * @brief Endpoint for changing direction to MANUAL_LEFT
 *
 * @param parent wxEvtHandler
 */
void LaneManualCalibrationController::e_ChangeToLeft(wxEvtHandler *parent) {
    try {
        checkPreCondition();
        changeToLeftHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

/**
 * @brief Endpoint for changing direction to MANUAL_RIGHT
 *
 * @param parent wxEvtHandler
 */
void LaneManualCalibrationController::e_ChangeToRight(wxEvtHandler *parent) {
    try {
        checkPreCondition();
        changeToRightHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

/**
 * @brief Endpoint for starting manual calibration
 * (ManualLaneCalibrationCameraThread or ManualLaneCalibrationCaptureThread)
 *
 * @param parent wxEvtHandler
 */
void LaneManualCalibrationController::e_ManualCalibrationStart(
    wxEvtHandler *parent) {
    try {
        checkPreCondition();
        manualCalibrationStartHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

/**
 * @brief Endpoint for ending manual calibration
 * (ManualLaneCalibrationCameraThread or ManualLaneCalibrationCaptureThread)
 *
 * @param parent wxEvtHandler
 */
void LaneManualCalibrationController::e_ManualCalibrationEnd(
    wxEvtHandler *parent) {
    try {
        checkPreCondition();
        manualCalibrationEndHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

/**
 * @brief Endpoint for starting ManualLaneCalibrationCameraThread
 *
 * @param parent wxEvtHandler
 */
void LaneManualCalibrationController::e_ManualCalibrationCameraStart(
    wxEvtHandler *parent) {
    try {
        checkPreCondition();
        manualCalibrationCameraStartHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

/**
 * @brief Endpoint for ending ManualLaneCalibrationCameraThread
 *
 * @param parent wxEvtHandler
 */
void LaneManualCalibrationController::e_ManualCalibrationCameraEnd(
    wxEvtHandler *parent) {
    try {
        checkPreCondition();
        manualCalibrationCameraEndHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

/**
 * @brief Endpoint for starting ManualLaneCalibrationCaptureThread
 *
 * @param parent wxEvtHandler
 */
void LaneManualCalibrationController::e_ManualCalibrationCaptureStart(
    wxEvtHandler *parent) {
    try {
        checkPreCondition();
        manualCalibrationCaptureStartHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

/**
 * @brief Endpoint for ending ManualLaneCalibrationCaptureThread
 *
 * @param parent wxEvtHandler
 */
void LaneManualCalibrationController::e_ManualCalibrationCaptureEnd(
    wxEvtHandler *parent) {
    try {
        checkPreCondition();
        manualCalibrationCaptureEndHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

/**
 * @brief Endpoint for starting CalibrationPreviewThread
 * (CalibrationPreviewCameraThread or CalibrationPreviewCaptureThread)
 *
 * @param parent wxEvtHandler
 */
void LaneManualCalibrationController::e_CalibrationPreviewStart(
    wxEvtHandler *parent) {
    try {
        checkPreCondition();
        calibrationPreviewStartHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

/**
 * @brief Endpoint for ending CalibrationPreviewThread
 * (CalibrationPreviewCameraThread or CalibrationPreviewCaptureThread)
 *
 * @param parent wxEvtHandler
 */
void LaneManualCalibrationController::e_CalibrationPreviewEnd(
    wxEvtHandler *parent) {
    try {
        checkPreCondition();
        calibrationPreviewEndHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

/**
 * @brief Endpoint for starting CalibrationPreviewCameraThread
 *
 * @param parent wxEvtHandler
 */
void LaneManualCalibrationController::e_CalibrationPreviewCameraStart(
    wxEvtHandler *parent) {
    try {
        checkPreCondition();
        calibrationPreviewCameraStartHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

/**
 * @brief Endpoint for ending CalibrationPreviewCameraThread
 *
 * @param parent wxEvtHandler
 */
void LaneManualCalibrationController::e_CalibrationPreviewCameraEnd(
    wxEvtHandler *parent) {
    try {
        checkPreCondition();
        calibrationPreviewCameraEndHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

/**
 * @brief Endpoint for starting CalibrationPreviewCaptureThread
 *
 * @param parent wxEvtHandler
 */
void LaneManualCalibrationController::e_CalibrationPreviewCaptureStart(
    wxEvtHandler *parent) {
    try {
        checkPreCondition();
        calibrationPreviewCaptureStartHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

/**
 * @brief Endpoint for ending CalibrationPreviewCaptureThread
 *
 * @param parent wxEvtHandler
 */
void LaneManualCalibrationController::e_CalibrationPreviewCaptureEnd(
    wxEvtHandler *parent) {
    try {
        checkPreCondition();
        calibrationPreviewCaptureEndHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

/**
 * @brief Endpoint for removing calibrated left Line
 *
 * @param parent wxEvtHandler
 */
void LaneManualCalibrationController::e_RemoveLeft(wxEvtHandler *parent) {
    try {
        checkPreCondition();
        removeLeftHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

/**
 * @brief Endpoint for removing calibrated right Line
 *
 * @param parent wxEvtHandler
 */
void LaneManualCalibrationController::e_RemoveRight(wxEvtHandler *parent) {
    try {
        checkPreCondition();
        removeRightHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

/**
 * @brief Endpoint for removing CalibrationData
 *
 * @param parent wxEvtHandler
 */
void LaneManualCalibrationController::e_RemoveCalibrationData(
    wxEvtHandler *parent) {
    try {
        checkPreCondition();
        removeCalibrationDataHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

/**
 * @brief Handler for changing direction to MANUAL_LEFT
 *
 * @param parent wxEvtHandler
 */
void LaneManualCalibrationController::changeToLeftHandler(
    wxEvtHandler *parent) {
    auto tc = shared->getThreadController();

    if (!tc->isLaneManualCalibrationThreadRunning()) {
        throw std::runtime_error("Calibration thread is not running");
    }

    if (!tc->isLaneManualCalibrationThreadOwner(panelID)) {
        throw std::runtime_error(
            "Calibration thread is not owned by this panel");
    }

    auto thread = tc->getRunningLaneManualCalibrationThread();

    thread->setDirection(ManualDirection::MANUAL_LEFT);

    UpdateStatusEvent::Submit(parent, SC::STATUS_MANUAL_SELECTLEFT);
}

/**
 * @brief Handler for changing direction to MANUAL_RIGHT
 *
 * @param parent wxEvtHandler
 */
void LaneManualCalibrationController::changeToRightHandler(
    wxEvtHandler *parent) {
    auto tc = shared->getThreadController();

    if (!tc->isLaneManualCalibrationThreadRunning()) {
        throw std::runtime_error("Calibration thread is not running");
    }

    if (!tc->isLaneManualCalibrationThreadOwner(panelID)) {
        throw std::runtime_error(
            "Calibration thread is not owned by this panel");
    }

    auto thread = tc->getRunningLaneManualCalibrationThread();

    thread->setDirection(ManualDirection::MANUAL_RIGHT);

    UpdateStatusEvent::Submit(parent, SC::STATUS_MANUAL_SELECTRIGHT);
}

/**
 * @brief Handler for Left Down event
 * @details Select stating point for Line
 *
 * @param parent wxEvtHandler
 * @param point cv::Point
 */
void LaneManualCalibrationController::leftDownHandler(wxEvtHandler *parent,
                                                      cv::Point point) {
    auto tc = shared->getThreadController();

    if (!tc->isLaneManualCalibrationThreadRunning()) {
        throw std::runtime_error("Calibration thread is not running");
    }

    if (!tc->isLaneManualCalibrationThreadOwner(panelID)) {
        throw std::runtime_error(
            "Calibration thread is not owned by this panel");
    }

    auto thread = tc->getRunningLaneManualCalibrationThread();

    thread->setPoint1(point);
}

/**
 * @brief Handler for Left Move event
 * @details Select ending point for Line
 *
 * @param parent wxEvtHandler
 * @param point cv::Point
 */
void LaneManualCalibrationController::leftMoveHandler(wxEvtHandler *parent,
                                                      cv::Point point) {
    auto tc = shared->getThreadController();

    if (!tc->isLaneManualCalibrationThreadRunning()) {
        throw std::runtime_error("Calibration thread is not running");
    }

    if (!tc->isLaneManualCalibrationThreadOwner(panelID)) {
        throw std::runtime_error(
            "Calibration thread is not owned by this panel");
    }

    auto thread = tc->getRunningLaneManualCalibrationThread();

    thread->setPoint2(point);
}

/**
 * @brief Handler for Left Up event
 * @details Select ending point for Line and extend it
 *
 * @param parent wxEvtHandler
 * @param point cv::Point
 */
void LaneManualCalibrationController::leftUpHandler(wxEvtHandler *parent,
                                                    cv::Point point) {
    auto tc = shared->getThreadController();

    if (!tc->isLaneManualCalibrationThreadRunning()) {
        throw std::runtime_error("Calibration thread is not running");
    }

    if (!tc->isLaneManualCalibrationThreadOwner(panelID)) {
        throw std::runtime_error(
            "Calibration thread is not owned by this panel");
    }

    auto thread = tc->getRunningLaneManualCalibrationThread();

    thread->setPoint2AndExtend(point);

    auto dir = thread->getDirection();
    auto line = dir == MANUAL_LEFT ? thread->getRealLeftLine()
                                   : thread->getRealRightLine();

    auto data = shared->getSessionData();

    auto calibData = data->getCalibrationData();

    dir == MANUAL_LEFT ? calibData.lineLeft = line : calibData.lineRight = line;

    data->setCalibrationData(calibData);
}

/**
 * @brief Handler for starting manual calibration
 * (ManualLaneCalibrationCameraThread or ManualLaneCalibrationCaptureThread)
 * @details If capture data is empty, start ManualLaneCalibrationCameraThread.
 * else start ManualLaneCalibrationCaptureThread
 *
 * @param parent wxEvtHandler
 */
void LaneManualCalibrationController::manualCalibrationStartHandler(
    wxEvtHandler *parent) {
    auto tc = shared->getThreadController();

    throwIfAnyThreadIsRunning();

    auto data = shared->getSessionData();

    if (data->isCaptureDataEmpty()) {
        manualCalibrationCameraStartHandler(parent);
    } else {
        manualCalibrationCaptureStartHandler(parent);
    }
}

/**
 * @brief Handler for ending manual calibration
 * (ManualLaneCalibrationCameraThread or ManualLaneCalibrationCaptureThread)
 *
 * @param parent wxEvtHandler
 */
void LaneManualCalibrationController::manualCalibrationEndHandler(
    wxEvtHandler *parent) {
    auto tc = shared->getThreadController();

    if (!tc->isLaneManualCalibrationThreadRunning()) {
        throw std::runtime_error("manualCalibThread is not running");
    }

    auto thread = tc->getRunningLaneManualCalibrationThread();
    if (thread->getID() == THREAD_LANE_MANUAL_CALIBRATION_CAMERA) {
        manualCalibrationCameraEndHandler(parent);
    } else {
        manualCalibrationCaptureEndHandler(parent);
    }
}

/**
 * @brief Handler for starting ManualLaneCalibrationCameraThread
 *
 * @param parent wxEvtHandler
 */
void LaneManualCalibrationController::manualCalibrationCameraStartHandler(
    wxEvtHandler *parent) {
    auto tc = shared->getThreadController();

    throwIfAnyThreadIsRunning();

    if (!shared->isCameraAvailable()) {
        throw std::runtime_error("Camera is not available");
    }

    auto camera = shared->getCamera();

    tc->startLaneManualCalibrationCameraHandler(parent, camera, panelID);
}

/**
 * @brief Handler for ending ManualLaneCalibrationCameraThread
 *
 * @param parent wxEvtHandler
 */
void LaneManualCalibrationController::manualCalibrationCameraEndHandler(
    wxEvtHandler *parent) {
    auto tc = shared->getThreadController();

    if (tc->isThreadNullptr(THREAD_LANE_MANUAL_CALIBRATION_CAMERA)) {
        throw std::runtime_error("manualCalibThread is not running");
    }

    if (!tc->isThreadOwner(THREAD_LANE_MANUAL_CALIBRATION_CAMERA, panelID)) {
        throw std::runtime_error(
            "manualCalibThread is not owned by this panel");
    }

    auto thread = tc->getLaneManualCalibrationCameraThread();
    thread->Pause();

    auto camera = thread->getCamera();
    shared->setCamera(camera);

    tc->endLaneManualCalibrationCameraHandler();
}

/**
 * @brief Handler for starting ManualLaneCalibrationCaptureThread
 *
 * @param parent wxEvtHandler
 */
void LaneManualCalibrationController::manualCalibrationCaptureStartHandler(
    wxEvtHandler *parent) {
    auto tc = shared->getThreadController();

    throwIfAnyThreadIsRunning();

    DataPtr data = shared->getSessionData();

    tc->startManualCalibrationCaptureHandler(parent, data, panelID);
}

/**
 * @brief Handler for ending ManualLaneCalibrationCaptureThread
 *
 * @param parent wxEvtHandler
 */
void LaneManualCalibrationController::manualCalibrationCaptureEndHandler(
    wxEvtHandler *parent) {
    auto tc = shared->getThreadController();

    if (tc->isThreadNullptr(THREAD_LANE_MANUAL_CALIBRATION_CAPTURE)) {
        throw std::runtime_error("manualCalibCaptureThread is not running");
    }

    if (!tc->isThreadOwner(THREAD_LANE_MANUAL_CALIBRATION_CAPTURE, panelID)) {
        throw std::runtime_error(
            "manualCalibCaptureThread is not owned by this panel");
    }

    auto thread = tc->getLaneManualCalibrationCaptureThread();
    thread->Pause();

    tc->endManualCalibrationCaptureHandler();
}

/**
 * @brief Handler for starting CalibrationPreviewThread
 * (CalibrationPreviewCameraThread or CalibrationPreviewCaptureThread)
 * @details If capture data is empty, start CalibrationPreviewCameraThread.
 * else start CalibrationPreviewCaptureThread
 *
 * @param parent wxEvtHandler
 */
void LaneManualCalibrationController::calibrationPreviewStartHandler(
    wxEvtHandler *parent) {
    auto tc = shared->getThreadController();

    throwIfAnyThreadIsRunning();

    auto data = shared->getSessionData();

    if (data->isCaptureDataEmpty()) {
        calibrationPreviewCameraStartHandler(parent);
    } else {
        calibrationPreviewCaptureStartHandler(parent);
    }
}

/**
 * @brief Handler for ending CalibrationPreviewThread
 * (CalibrationPreviewCameraThread or CalibrationPreviewCaptureThread)
 *
 * @param parent wxEvtHandler
 */
void LaneManualCalibrationController::calibrationPreviewEndHandler(
    wxEvtHandler *parent) {
    auto tc = shared->getThreadController();

    if (!tc->isCalibPreviewThreadRunning()) {
        throw std::runtime_error("calibPrevThread is not running");
    }

    auto thread = tc->getRunningCalibPreviewThread();
    if (thread->getID() == THREAD_CALIBRATION_PREVIEW_CAMERA) {
        calibrationPreviewCameraEndHandler(parent);
    } else {
        calibrationPreviewCaptureEndHandler(parent);
    }
}

/**
 * @brief Handler for starting CalibrationPreviewCameraThread
 *
 * @param parent wxEvtHandler
 */
void LaneManualCalibrationController::calibrationPreviewCameraStartHandler(
    wxEvtHandler *parent) {
    auto tc = shared->getThreadController();

    throwIfAnyThreadIsRunning();

    auto camera = shared->getCamera();

    if (camera == nullptr) {
        throw std::runtime_error("camera is nullptr");
    }

    DataPtr data = shared->getSessionData();

    tc->startCalibrationPreviewCameraHandler(parent, camera, data, panelID);
}

/**
 * @brief Handler for ending CalibrationPreviewCameraThread
 *
 * @param parent wxEvtHandler
 */
void LaneManualCalibrationController::calibrationPreviewCameraEndHandler(
    wxEvtHandler *parent) {
    auto tc = shared->getThreadController();

    if (tc->isThreadNullptr(THREAD_CALIBRATION_PREVIEW_CAMERA)) {
        throw std::runtime_error("calibPrevThread is not running");
    }

    if (!tc->isThreadOwner(THREAD_CALIBRATION_PREVIEW_CAMERA, panelID)) {
        throw std::runtime_error("calibPrevThread is not owned by this panel");
    }

    auto thread = tc->getCalibrationPreviewCameraThread();
    thread->Pause();

    auto camera = thread->getCamera();
    shared->setCamera(camera);

    tc->endCalibrationPreviewCameraHandler();
}

/**
 * @brief Handler for starting CalibrationPreviewCaptureThread
 *
 * @param parent wxEvtHandler
 */
void LaneManualCalibrationController::calibrationPreviewCaptureStartHandler(
    wxEvtHandler *parent) {
    auto tc = shared->getThreadController();

    throwIfAnyThreadIsRunning();

    auto data = shared->getSessionData();

    if (data->isCaptureDataEmpty()) {
        throw std::runtime_error("capture data is empty");
    }

    tc->startCalibrationPreviewCaptureHandler(parent, data, panelID);
}

/**
 * @brief Handler for ending CalibrationPreviewCaptureThread
 *
 * @param parent wxEvtHandler
 */
void LaneManualCalibrationController::calibrationPreviewCaptureEndHandler(
    wxEvtHandler *parent) {
    auto tc = shared->getThreadController();

    if (tc->isThreadNullptr(THREAD_CALIBRATION_PREVIEW_CAPTURE)) {
        throw std::runtime_error("calibCapPrevThread is not running");
    }

    if (!tc->isThreadOwner(THREAD_CALIBRATION_PREVIEW_CAPTURE, panelID)) {
        throw std::runtime_error(
            "calibCapPrevThread is not owned by this panel");
    }

    auto thread = tc->getCalibrationPreviewCaptureThread();
    thread->Pause();

    tc->endCalibrationPreviewCaptureHandler();
}

/**
 * @brief Handler for removing calibrated left Line
 *
 * @param parent wxEvtHandler
 */
void LaneManualCalibrationController::removeLeftHandler(wxEvtHandler *parent) {
    auto tc = shared->getThreadController();

    if (!tc->isLaneManualCalibrationThreadRunning()) {
        throw std::runtime_error("Calibration thread is not running");
    }

    if (!tc->isLaneManualCalibrationThreadOwner(panelID)) {
        throw std::runtime_error(
            "Calibration thread is not owned by this panel");
    }

    auto thread = tc->getRunningLaneManualCalibrationThread();

    thread->setLeftLine(Line());

    auto data = shared->getSessionData();

    auto calibData = data->getCalibrationData();

    calibData.lineLeft = Line();

    data->setCalibrationData(calibData);

    UpdateStatusEvent::Submit(parent, SC::STATUS_MANUAL_REMOVELEFT);
}

/**
 * @brief Handler for removing calibrated right Line
 *
 * @param parent wxEvtHandler
 */
void LaneManualCalibrationController::removeRightHandler(wxEvtHandler *parent) {
    auto tc = shared->getThreadController();

    if (!tc->isLaneManualCalibrationThreadRunning()) {
        throw std::runtime_error("Calibration thread is not running");
    }

    if (!tc->isLaneManualCalibrationThreadOwner(panelID)) {
        throw std::runtime_error(
            "Calibration thread is not owned by this panel");
    }

    auto thread = tc->getRunningLaneManualCalibrationThread();

    thread->setRightLine(Line());

    auto data = shared->getSessionData();

    auto calibData = data->getCalibrationData();

    calibData.lineRight = Line();

    data->setCalibrationData(calibData);

    UpdateStatusEvent::Submit(parent, SC::STATUS_MANUAL_REMOVERIGHT);
}

/**
 * @brief Handler for removing CalibrationData
 *
 * @param parent wxEvtHandler
 */
void LaneManualCalibrationController::removeCalibrationDataHandler(
    wxEvtHandler *parent) {
    throwIfAnyThreadIsRunning();

    auto wx = wxTheApp->GetTopWindow();
    auto dialog = RemoveCalibrationDialog(wx);
    if (dialog.ShowModal() == wxID_NO) {
        return;
    }

    shared->sessionData.removeCalibrationData();

    UpdateStatusEvent::Submit(parent, SC::STATUS_REMOVE_CALIBRATION_OK);
}

/**
 * @brief Handler for OnShow event
 * @details If auto thread is enabled, start manual calibration
 *
 * @param parent wxEvtHandler
 */
void LaneManualCalibrationController::panelShowHandler(wxEvtHandler *parent) {
    createTempSessionDataHandler(parent);

    auto data = shared->getSessionData();

    if (!data->isCalibrationDataEmpty()) {
        return;
    }

    AppConfig c;
    auto config = c.GetThreadsConfig();
    auto startThread = config.autoManualCalibration;

    if (!startThread) {
        return;
    }

    manualCalibrationStartHandler(parent);
}
