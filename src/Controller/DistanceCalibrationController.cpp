#include <Controller/DistanceCalibrationController.hpp>

#include <UI/Dialog/RemoveCalibrationDialog.hpp>

/**
 * @brief Construct a new Distance Calibration Controller:: Distance Calibration
 * Controller object
 *
 * @param shared
 */
DistanceCalibrationController::DistanceCalibrationController(ResourcePtr shared)
    : BaseControllerWithTouch(shared) {
    panelID = currentPanelID;
}

/**
 * @brief Destroy the Distance Calibration Controller:: Distance Calibration
 * Controller object
 *
 */
DistanceCalibrationController::~DistanceCalibrationController() {}

/**
 * @brief Throw exception if any thread from ThreadController is running
 *
 */
void DistanceCalibrationController::throwIfAnyThreadIsRunning() {
    auto tc = shared->getThreadController();

    if (!tc->isThreadNullptr(THREAD_DISTANCE_CALIBRATION_CAMERA)) {
        throw std::runtime_error("distanceCalibThread is running");
    }

    if (!tc->isThreadNullptr(THREAD_DISTANCE_CALIBRATION_CAPTURE)) {
        throw std::runtime_error("distanceCalibCapTureThread is running");
    }

    if (!tc->isThreadNullptr(THREAD_CALIBRATION_PREVIEW_CAPTURE)) {
        throw std::runtime_error("calibCapPrevThread is running");
    }

    if (!tc->isThreadNullptr(THREAD_CALIBRATION_PREVIEW_CAMERA)) {
        throw std::runtime_error("calibPrevThread is running");
    }
}

/**
 * @brief Kill all threads from ThreadController
 *
 * @param parent wxEvtHandler
 */
void DistanceCalibrationController::killAllThreads(wxEvtHandler *parent) {
    auto tc = shared->getThreadController();

    if (!tc->isThreadNullptr(THREAD_DISTANCE_CALIBRATION_CAMERA)) {
        distanceCalibrationCameraEndHandler(parent);
    }

    if (!tc->isThreadNullptr(THREAD_DISTANCE_CALIBRATION_CAPTURE)) {
        distanceCalibrationCaptureEndHandler(parent);
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
 * @brief Endpoint to change calibration type to DISTANCE_BOTTOM
 *
 * @param parent wxEvtHandler
 */
void DistanceCalibrationController::e_ChangeToBottom(wxEvtHandler *parent) {
    try {
        checkPreCondition();
        changeToBottomHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

/**
 * @brief Endpoint to change calibration type to DISTANCE_TOP
 *
 * @param parent wxEvtHandler
 */
void DistanceCalibrationController::e_ChangeToTop(wxEvtHandler *parent) {
    try {
        checkPreCondition();
        changeToTopHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

/**
 * @brief Endpoint to start distance calibration
 * (DistanceCalibrationCameraThread or DistanceCalibrationCaptureThread)
 *
 * @param parent wxEvtHandler
 */
void DistanceCalibrationController::e_DistanceCalibrationStart(
    wxEvtHandler *parent) {
    try {
        checkPreCondition();
        distanceCalibrationStartHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

/**
 * @brief Endpoint to end distance calibration (DistanceCalibrationCameraThread
 * or DistanceCalibrationCaptureThread)
 *
 * @param parent wxEvtHandler
 */
void DistanceCalibrationController::e_DistanceCalibrationEnd(
    wxEvtHandler *parent) {
    try {
        checkPreCondition();
        distanceCalibrationEndHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

/**
 * @brief Endpoint to start distance calibration using camera
 * (DistanceCalibrationCameraThread)
 *
 * @param parent wxEvtHandler
 */
void DistanceCalibrationController::e_DistanceCalibrationCameraStart(
    wxEvtHandler *parent) {
    try {
        checkPreCondition();
        distanceCalibrationCameraStartHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

/**
 * @brief Endpoint to end distance calibration using camera
 * (DistanceCalibrationCameraThread)
 *
 * @param parent wxEvtHandler
 */
void DistanceCalibrationController::e_DistanceCalibrationCameraEnd(
    wxEvtHandler *parent) {
    try {
        checkPreCondition();
        distanceCalibrationCameraEndHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

/**
 * @brief Endpoint to start distance calibration using capture
 * (DistanceCalibrationCaptureThread)
 *
 * @param parent wxEvtHandler
 */
void DistanceCalibrationController::e_DistanceCalibrationCaptureStart(
    wxEvtHandler *parent) {
    try {
        checkPreCondition();
        distanceCalibrationCaptureStartHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

/**
 * @brief Endpoint to end distance calibration using capture
 * (DistanceCalibrationCaptureThread)
 *
 * @param parent wxEvtHandler
 */
void DistanceCalibrationController::e_DistanceCalibrationCaptureEnd(
    wxEvtHandler *parent) {
    try {
        checkPreCondition();
        distanceCalibrationCaptureEndHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

/**
 * @brief Endpoint to start calibration preview
 * (CalibrationPreviewCameraThread or CalibrationPreviewCaptureThread)
 *
 * @param parent wxEvtHandler
 */
void DistanceCalibrationController::e_CalibrationPreviewStart(
    wxEvtHandler *parent) {
    try {
        checkPreCondition();
        calibrationPreviewStartHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

/**
 * @brief Endpoint to end calibration preview (CalibrationPreviewCameraThread or
 * CalibrationPreviewCaptureThread)
 *
 * @param parent wxEvtHandler
 */
void DistanceCalibrationController::e_CalibrationPreviewEnd(
    wxEvtHandler *parent) {
    try {
        checkPreCondition();
        calibrationPreviewEndHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

/**
 * @brief Endpoint to start calibration preview using camera
 * (CalibrationPreviewCameraThread)
 *
 * @param parent wxEvtHandler
 */
void DistanceCalibrationController::e_CalibrationPreviewCameraStart(
    wxEvtHandler *parent) {
    try {
        checkPreCondition();
        calibrationPreviewCameraStartHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

/**
 * @brief Endpoint to end calibration preview using camera
 * (CalibrationPreviewCameraThread)
 *
 * @param parent wxEvtHandler
 */
void DistanceCalibrationController::e_CalibrationPreviewCameraEnd(
    wxEvtHandler *parent) {
    try {
        checkPreCondition();
        calibrationPreviewCameraEndHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

/**
 * @brief Endpoint to start calibration preview using capture
 * (CalibrationPreviewCaptureThread)
 *
 * @param parent wxEvtHandler
 */
void DistanceCalibrationController::e_CalibrationPreviewCaptureStart(
    wxEvtHandler *parent) {
    try {
        checkPreCondition();
        calibrationPreviewCaptureStartHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

/**
 * @brief Endpoint to end calibration preview using capture
 * (CalibrationPreviewCaptureThread)
 *
 * @param parent wxEvtHandler
 */
void DistanceCalibrationController::e_CalibrationPreviewCaptureEnd(
    wxEvtHandler *parent) {
    try {
        checkPreCondition();
        calibrationPreviewCaptureEndHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

/**
 * @brief Endpoint to remove bottom line
 *
 * @param parent wxEvtHandler
 */
void DistanceCalibrationController::e_RemoveBottom(wxEvtHandler *parent) {
    try {
        checkPreCondition();
        removeBottomHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

/**
 * @brief Endpoint to remove top line
 *
 * @param parent wxEvtHandler
 */
void DistanceCalibrationController::e_RemoveTop(wxEvtHandler *parent) {
    try {
        checkPreCondition();
        removeTopHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

/**
 * @brief Endpoint to remove calibration data
 *
 * @param parent wxEvtHandler
 */
void DistanceCalibrationController::e_RemoveCalibrationData(
    wxEvtHandler *parent) {
    try {
        checkPreCondition();
        removeCalibrationDataHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

/**
 * @brief Handle request to change calibraton type to DISTANCE_BOTTOM
 *
 * @param parent wxEvtHandler
 */
void DistanceCalibrationController::changeToBottomHandler(
    wxEvtHandler *parent) {
    auto tc = shared->getThreadController();

    if (!tc->isDistanceCalibrationThreadRunning()) {
        throw std::runtime_error("Calibration thread is not running");
    }

    if (!tc->isDistanceCalibrationThreadOwner(panelID)) {
        throw std::runtime_error(
            "Calibration thread is not owned by this panel");
    }

    auto thread = tc->getRunningDistanceCalibrationThread();

    thread->setDirection(DistanceDirection::DISTANCE_BOTTOM);

    UpdateStatusEvent::Submit(parent, SC::STATUS_DISTANCE_SELECTBOTTOM);
}

/**
 * @brief Handle request to change calibraton type to DISTANCE_TOP
 *
 * @param parent wxEvtHandler
 */
void DistanceCalibrationController::changeToTopHandler(wxEvtHandler *parent) {
    auto tc = shared->getThreadController();

    if (!tc->isDistanceCalibrationThreadRunning()) {
        throw std::runtime_error("Calibration thread is not running");
    }

    if (!tc->isDistanceCalibrationThreadOwner(panelID)) {
        throw std::runtime_error(
            "Calibration thread is not owned by this panel");
    }

    auto thread = tc->getRunningDistanceCalibrationThread();

    thread->setDirection(DistanceDirection::DISTANCE_TOP);

    UpdateStatusEvent::Submit(parent, SC::STATUS_DISTANCE_SELECTTOP);
}

/**
 * @brief Handle left down event
 * @details When left down set point and extend line in running calibration
 * thread
 * @param parent wxEvtHandler
 * @param point cv::Point point
 */
void DistanceCalibrationController::leftDownHandler(wxEvtHandler *parent,
                                                    cv::Point point) {
    auto tc = shared->getThreadController();

    if (!tc->isDistanceCalibrationThreadRunning()) {
        throw std::runtime_error("Calibration thread is not running");
    }

    if (!tc->isDistanceCalibrationThreadOwner(panelID)) {
        throw std::runtime_error(
            "Calibration thread is not owned by this panel");
    }

    auto thread = tc->getRunningDistanceCalibrationThread();

    thread->setPointAndExtend(point);
}

/**
 * @brief Handle left move event
 * @details DO the same as DistanceCalibrationController::leftDownHandler. But
 * by enabling this, it allows user to draw cursor freely, wich enables user to
 * select more accurate line
 *
 * @param parent wxEvtHandler
 * @param point cv::Point point
 */
void DistanceCalibrationController::leftMoveHandler(wxEvtHandler *parent,
                                                    cv::Point point) {
    // throw std::runtime_error("Blocked Endpoint");
    leftDownHandler(parent, point);
}

/**
 * @brief Handle left up event
 * @details When left up set point and extend line in running calibration
 * thread. Also save line to calibration data
 * @param parent wxEvtHandler
 * @param point cv::Point point
 */
void DistanceCalibrationController::leftUpHandler(wxEvtHandler *parent,
                                                  cv::Point point) {
    auto tc = shared->getThreadController();

    if (!tc->isDistanceCalibrationThreadRunning()) {
        throw std::runtime_error("Calibration thread is not running");
    }

    if (!tc->isDistanceCalibrationThreadOwner(panelID)) {
        throw std::runtime_error(
            "Calibration thread is not owned by this panel");
    }

    auto thread = tc->getRunningDistanceCalibrationThread();

    thread->setPointAndExtend(point);

    auto dir = thread->getDirection();
    auto line = dir == DISTANCE_TOP ? thread->getRealTopLine()
                                    : thread->getRealBottomLine();

    auto data = shared->getSessionData();

    auto calibData = data->getCalibrationData();

    dir == DISTANCE_TOP ? calibData.lineRight = line
                        : calibData.lineLeft = line;

    data->setCalibrationData(calibData);
}

/**
 * @brief Handle request to start distance calibration
 * (DistanceCalibrationCameraThread or DistanceCalibrationCaptureThread)
 *
 * @param parent wxEvtHandler
 */
void DistanceCalibrationController::distanceCalibrationStartHandler(
    wxEvtHandler *parent) {
    auto tc = shared->getThreadController();

    throwIfAnyThreadIsRunning();

    auto data = shared->getSessionData();

    if (data->isCaptureDataEmpty()) {
        distanceCalibrationCameraStartHandler(parent);
    } else {
        distanceCalibrationCaptureStartHandler(parent);
    }
}

/**
 * @brief Handle request to end distance calibration
 * (DistanceCalibrationCameraThread or DistanceCalibrationCaptureThread)
 *
 * @param parent wxEvtHandler
 */
void DistanceCalibrationController::distanceCalibrationEndHandler(
    wxEvtHandler *parent) {
    auto tc = shared->getThreadController();

    if (!tc->isDistanceCalibrationThreadRunning()) {
        throw std::runtime_error("CalibrationThread is not running");
    }

    auto thread = tc->getRunningDistanceCalibrationThread();
    if (thread->getID() == THREAD_DISTANCE_CALIBRATION_CAMERA) {
        distanceCalibrationCameraEndHandler(parent);
    } else {
        distanceCalibrationCaptureEndHandler(parent);
    }
}

/**
 * @brief Handle request to start distance calibration using camera
 * (DistanceCalibrationCameraThread)
 *
 * @param parent wxEvtHandler
 */
void DistanceCalibrationController::distanceCalibrationCameraStartHandler(
    wxEvtHandler *parent) {
    auto tc = shared->getThreadController();

    throwIfAnyThreadIsRunning();

    if (!shared->isCameraAvailable()) {
        throw std::runtime_error("Camera is not available");
    }

    auto camera = shared->getCamera();

    tc->startDistaneCalibrationCameraHandler(parent, camera, panelID);
}

/**
 * @brief Handle request to end distance calibration using camera
 * (DistanceCalibrationCameraThread)
 *
 * @param parent wxEvtHandler
 */
void DistanceCalibrationController::distanceCalibrationCameraEndHandler(
    wxEvtHandler *parent) {
    auto tc = shared->getThreadController();

    if (tc->isThreadNullptr(THREAD_DISTANCE_CALIBRATION_CAMERA)) {
        throw std::runtime_error("CalibThread is not running");
    }

    if (!tc->isThreadOwner(THREAD_DISTANCE_CALIBRATION_CAMERA, panelID)) {
        throw std::runtime_error("CalibThread is not owned by this panel");
    }

    auto thread = tc->getDistanceCalibrationCameraThread();
    thread->Pause();

    auto camera = thread->getCamera();
    shared->setCamera(camera);

    tc->endDistanceCalibrationCameraHandler();
}

/**
 * @brief Handle request to start distance calibration using capture
 * (DistanceCalibrationCaptureThread)
 *
 * @param parent wxEvtHandler
 */
void DistanceCalibrationController::distanceCalibrationCaptureStartHandler(
    wxEvtHandler *parent) {
    auto tc = shared->getThreadController();

    throwIfAnyThreadIsRunning();

    DataPtr data = shared->getSessionData();

    tc->startDistanceCalibrationCaptureHandler(parent, data, panelID);
}

/**
 * @brief Handle request to end distance calibration using capture
 * (DistanceCalibrationCaptureThread)
 *
 * @param parent wxEvtHandler
 */
void DistanceCalibrationController::distanceCalibrationCaptureEndHandler(
    wxEvtHandler *parent) {
    auto tc = shared->getThreadController();

    if (tc->isThreadNullptr(THREAD_DISTANCE_CALIBRATION_CAPTURE)) {
        throw std::runtime_error("CalibCaptureThread is not running");
    }

    if (!tc->isThreadOwner(THREAD_DISTANCE_CALIBRATION_CAPTURE, panelID)) {
        throw std::runtime_error(
            "CalibCaptureThread is not owned by this panel");
    }

    auto thread = tc->getDistanceCalibrationCaptureThread();
    thread->Pause();

    tc->endDistanceCalibrationCaptureHandler();
}

/**
 * @brief Handle request to start calibration preview
 * (CalibrationPreviewCameraThread or CalibrationPreviewCaptureThread)
 *
 * @param parent wxEvtHandler
 */
void DistanceCalibrationController::calibrationPreviewStartHandler(
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
 * @brief Handle request to end calibration preview
 * (CalibrationPreviewCameraThread or CalibrationPreviewCaptureThread)
 *
 * @param parent wxEvtHandler
 */
void DistanceCalibrationController::calibrationPreviewEndHandler(
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
 * @brief Handle request to start calibration preview using camera
 * (CalibrationPreviewCameraThread)
 *
 * @param parent wxEvtHandler
 */
void DistanceCalibrationController::calibrationPreviewCameraStartHandler(
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
 * @brief Handle request to end calibration preview using camera
 * (CalibrationPreviewCameraThread)
 *
 * @param parent wxEvtHandler
 */
void DistanceCalibrationController::calibrationPreviewCameraEndHandler(
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
 * @brief Handle request to start calibration preview using capture
 * (CalibrationPreviewCaptureThread)
 *
 * @param parent wxEvtHandler
 */
void DistanceCalibrationController::calibrationPreviewCaptureStartHandler(
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
 * @brief Handle request to end calibration preview using capture
 * (CalibrationPreviewCaptureThread)
 *
 * @param parent wxEvtHandler
 */
void DistanceCalibrationController::calibrationPreviewCaptureEndHandler(
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
 * @brief Handle request to remove bottom line
 *
 * @param parent wxEvtHandler
 */
void DistanceCalibrationController::removeBottomHandler(wxEvtHandler *parent) {
    auto tc = shared->getThreadController();

    if (!tc->isDistanceCalibrationThreadRunning()) {
        throw std::runtime_error("Calibration thread is not running");
    }

    if (!tc->isDistanceCalibrationThreadOwner(panelID)) {
        throw std::runtime_error(
            "Calibration thread is not owned by this panel");
    }

    auto thread = tc->getRunningDistanceCalibrationThread();

    thread->setBottomLine(Line());

    auto data = shared->getSessionData();

    auto calibData = data->getCalibrationData();

    calibData.lineLeft = Line();

    data->setCalibrationData(calibData);

    UpdateStatusEvent::Submit(parent, SC::STATUS_DISTANCE_REMOVEBOTTOM);
}

/**
 * @brief Handle request to remove top line
 *
 * @param parent wxEvtHandler
 */
void DistanceCalibrationController::removeTopHandler(wxEvtHandler *parent) {
    auto tc = shared->getThreadController();

    if (!tc->isDistanceCalibrationThreadRunning()) {
        throw std::runtime_error("Calibration thread is not running");
    }

    if (!tc->isDistanceCalibrationThreadOwner(panelID)) {
        throw std::runtime_error(
            "Calibration thread is not owned by this panel");
    }

    auto thread = tc->getRunningDistanceCalibrationThread();

    thread->setTopLine(Line());

    auto data = shared->getSessionData();

    auto calibData = data->getCalibrationData();

    calibData.lineRight = Line();

    data->setCalibrationData(calibData);

    UpdateStatusEvent::Submit(parent, SC::STATUS_DISTANCE_REMOVETOP);
}

/**
 * @brief Handle request to remove calibration data
 *
 * @param parent wxEvtHandler
 */
void DistanceCalibrationController::removeCalibrationDataHandler(
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
 * @brief Handle request to show panel
 * @details Override BaseControllerWithTouch::panelShowHandler. Add features to
 * automatically start calibration thread. This variable can be change in
 * SettingsPanel
 *
 * @param parent wxEvtHandler
 */
void DistanceCalibrationController::panelShowHandler(wxEvtHandler *parent) {
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

    distanceCalibrationCameraStartHandler(parent);
}
