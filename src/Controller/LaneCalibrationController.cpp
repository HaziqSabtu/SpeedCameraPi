#include <Controller/LaneCalibrationController.hpp>

#include <UI/Dialog/RemoveCalibrationDialog.hpp>

LaneCalibrationController::LaneCalibrationController(ResourcePtr shared)
    : BaseControllerWithTouch(shared) {
    panelID = currentPanelID;
}

LaneCalibrationController::~LaneCalibrationController() {}

void LaneCalibrationController::e_RemoveCalibrationData(wxEvtHandler *parent) {
    try {
        checkPreCondition();
        removeCalibrationDataHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void LaneCalibrationController::e_CalibrationStart(wxEvtHandler *parent) {
    try {
        checkPreCondition();
        calibrationStartHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void LaneCalibrationController::e_CalibrationEnd(wxEvtHandler *parent) {
    try {
        checkPreCondition();
        calibrationEndHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void LaneCalibrationController::e_CalibrationCameraStart(wxEvtHandler *parent) {
    try {
        checkPreCondition();
        calibrationCameraStartHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void LaneCalibrationController::e_CalibrationCameraEnd(wxEvtHandler *parent) {
    try {
        checkPreCondition();
        calibrationCameraEndHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void LaneCalibrationController::e_CalibrationCaptureStart(
    wxEvtHandler *parent) {
    try {
        checkPreCondition();
        calibrationCaptureStartHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void LaneCalibrationController::e_CalibrationCaptureEnd(wxEvtHandler *parent) {
    try {
        checkPreCondition();
        calibrationCaptureEndHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void LaneCalibrationController::e_CalibrationPreviewStart(
    wxEvtHandler *parent) {
    try {
        checkPreCondition();
        calibrationPreviewStartHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void LaneCalibrationController::e_CalibrationPreviewEnd(wxEvtHandler *parent) {
    try {
        checkPreCondition();
        calibrationPreviewEndHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void LaneCalibrationController::e_CalibrationPreviewCameraStart(
    wxEvtHandler *parent) {
    try {
        checkPreCondition();
        calibrationPreviewCameraStartHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void LaneCalibrationController::e_CalibrationPreviewCameraEnd(
    wxEvtHandler *parent) {
    try {
        checkPreCondition();
        calibrationPreviewCameraEndHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void LaneCalibrationController::e_CalibrationPreviewCaptureStart(
    wxEvtHandler *parent) {
    try {
        checkPreCondition();
        calibrationPreviewCaptureStartHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void LaneCalibrationController::e_CalibrationPreviewCaptureEnd(
    wxEvtHandler *parent) {
    try {
        checkPreCondition();
        calibrationPreviewCaptureEndHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void LaneCalibrationController::e_ChangeToManualPanel(wxEvtHandler *parent) {
    try {
        checkPreCondition();
        changeToManualPanelHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void LaneCalibrationController::e_ChangeToColorPanel(wxEvtHandler *parent) {
    try {
        checkPreCondition();
        changeToColorPanelHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void LaneCalibrationController::e_ClearPoint(wxEvtHandler *parent) {
    try {
        checkPreCondition();
        clearPointHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void LaneCalibrationController::e_SaveData(wxEvtHandler *parent) {
    try {
        checkPreCondition();
        saveDataHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void LaneCalibrationController::calibrationStartHandler(wxEvtHandler *parent) {
    auto tc = shared->getThreadController();

    throwIfAnyThreadIsRunning();

    auto data = shared->getSessionData();

    if (data->isCaptureDataEmpty()) {
        calibrationCameraStartHandler(parent);
    } else {
        calibrationCaptureStartHandler(parent);
    }
}

void LaneCalibrationController::calibrationEndHandler(wxEvtHandler *parent) {
    auto tc = shared->getThreadController();

    if (!tc->isLaneCalibrationThreadRunning()) {
        throw std::runtime_error("calibrationThread is not running");
    }

    auto thread = tc->getRunningLaneCalibrationThread();
    if (thread->getID() == THREAD_LANE_CALIBRATION_CAMERA) {
        calibrationCameraEndHandler(parent);
    } else {
        calibrationCaptureEndHandler(parent);
    }
}

void LaneCalibrationController::calibrationCameraStartHandler(
    wxEvtHandler *parent) {
    auto tc = shared->getThreadController();

    throwIfAnyThreadIsRunning();

    if (!shared->isCameraAvailable()) {
        throw std::runtime_error("Camera is not available");
    }

    auto camera = shared->getCamera();
    auto data = shared->getSessionData();

    AppConfig c;
    auto hsvFilter = AF::createHSVFilter(c);
    auto bfs = AF::createBFS(c);
    auto ransac = AF::createRansacLine(c);

    tc->startLaneCalibrationCameraHandler(parent, data, camera, hsvFilter, bfs,
                                          ransac, panelID);
}

void LaneCalibrationController::calibrationCameraEndHandler(
    wxEvtHandler *parent) {
    auto tc = shared->getThreadController();

    if (tc->isThreadNullptr(THREAD_LANE_CALIBRATION_CAMERA)) {
        throw std::runtime_error("calibThread is not running");
    }

    if (!tc->isThreadOwner(THREAD_LANE_CALIBRATION_CAMERA, panelID)) {
        throw std::runtime_error("calibThread is not owned by this panel");
    }

    auto thread = tc->getLaneCalibrationCameraThread();
    thread->Pause();

    saveCalibrationData(parent, thread);

    auto camera = thread->getCamera();
    shared->setCamera(camera);

    tc->endLaneCalibrationCameraHandler();
}

void LaneCalibrationController::calibrationCaptureStartHandler(
    wxEvtHandler *parent) {
    auto tc = shared->getThreadController();

    throwIfAnyThreadIsRunning();

    DataPtr data = shared->getSessionData();

    AppConfig c;
    auto hsvFilter = AF::createHSVFilter(c);
    auto bfs = AF::createBFS(c);
    auto ransac = AF::createRansacLine(c);

    tc->startLaneCalibrationCaptureHandler(parent, data, hsvFilter, bfs, ransac,
                                           panelID);
}

void LaneCalibrationController::calibrationCaptureEndHandler(
    wxEvtHandler *parent) {
    auto tc = shared->getThreadController();

    if (tc->isThreadNullptr(THREAD_LANE_CALIBRATION_CAPTURE)) {
        throw std::runtime_error("calibCaptureThread is not running");
    }

    if (!tc->isThreadOwner(THREAD_LANE_CALIBRATION_CAPTURE, panelID)) {
        throw std::runtime_error(
            "calibCaptureThread is not owned by this panel");
    }

    auto thread = tc->getLaneCalibrationCaptureThread();
    thread->Pause();

    saveCalibrationData(parent, thread);

    tc->endLaneCalibrationCaptureHandler();
}

void LaneCalibrationController::calibrationPreviewStartHandler(
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

void LaneCalibrationController::calibrationPreviewEndHandler(
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

void LaneCalibrationController::calibrationPreviewCameraStartHandler(
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

void LaneCalibrationController::calibrationPreviewCameraEndHandler(
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

void LaneCalibrationController::calibrationPreviewCaptureStartHandler(
    wxEvtHandler *parent) {
    auto tc = shared->getThreadController();

    throwIfAnyThreadIsRunning();

    auto data = shared->getSessionData();

    if (data->isCaptureDataEmpty()) {
        throw std::runtime_error("capture data is empty");
    }

    tc->startCalibrationPreviewCaptureHandler(parent, data, panelID);
}

void LaneCalibrationController::calibrationPreviewCaptureEndHandler(
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

void LaneCalibrationController::saveCalibrationData(
    wxEvtHandler *parent, BaseLaneCalibrationThread *thread) {
    auto calibData = thread->getCalibrationData();

    auto data = shared->getSessionData();
    data->setCalibrationData(calibData);
}

void LaneCalibrationController::leftDownHandler(wxEvtHandler *parent,
                                                cv::Point point) {
    auto tc = shared->getThreadController();

    if (!tc->isLaneCalibrationThreadRunning()) {
        throw std::runtime_error("calibration Thread is not running");
    }

    if (!tc->isLaneCalibrationThreadOwner(panelID)) {
        throw std::runtime_error(
            "calibration Thread is not owned by this panel");
    }

    auto thread = tc->getRunningLaneCalibrationThread();
    thread->setPoint(point);

    UpdateStatusEvent::Submit(parent,
                              SC::STATUS_LANE_CALIBRATION_POINTSELECTED);
}

void LaneCalibrationController::saveDataHandler(wxEvtHandler *parent) {
    auto tc = shared->getThreadController();

    if (!tc->isLaneCalibrationThreadRunning()) {
        throw std::runtime_error("calibration Thread is not running");
    }

    if (!tc->isLaneCalibrationThreadOwner(panelID)) {
        throw std::runtime_error(
            "calibration Thread is not owned by this panel");
    }

    auto thread = tc->getRunningLaneCalibrationThread();

    saveCalibrationData(parent, thread);
}

void LaneCalibrationController::leftMoveHandler(wxEvtHandler *parent,
                                                cv::Point point) {
    throw std::runtime_error("Blocked Endpoint");
}

void LaneCalibrationController::leftUpHandler(wxEvtHandler *parent,
                                              cv::Point point) {
    throw std::runtime_error("Blocked Endpoint");
}

void LaneCalibrationController::clearPointHandler(wxEvtHandler *parent) {
    auto tc = shared->getThreadController();

    if (!tc->isLaneCalibrationThreadRunning()) {
        throw std::runtime_error("calibration Thread is not running");
    }

    if (!tc->isLaneCalibrationThreadOwner(panelID)) {
        throw std::runtime_error(
            "calibration Thread is not owned by this panel");
    }

    auto thread = tc->getRunningLaneCalibrationThread();
    thread->clearPoint();

    UpdateStatusEvent::Submit(parent, SC::STATUS_LANE_CALIBRATION_POINTREMOVED);
}

void LaneCalibrationController::removeCalibrationDataHandler(
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

void LaneCalibrationController::throwIfAnyThreadIsRunning() {
    auto tc = shared->getThreadController();

    if (!tc->isThreadNullptr(THREAD_LANE_CALIBRATION_CAMERA)) {
        throw std::runtime_error("CalibrationThread is running");
    }

    if (!tc->isThreadNullptr(THREAD_LANE_CALIBRATION_CAPTURE)) {
        throw std::runtime_error("CalibrationCaptureThread is running");
    }

    if (!tc->isThreadNullptr(THREAD_CALIBRATION_PREVIEW_CAMERA)) {
        throw std::runtime_error("CalibrationPreviewThread is running");
    }

    if (!tc->isThreadNullptr(THREAD_CALIBRATION_PREVIEW_CAPTURE)) {
        throw std::runtime_error("CalibrationPreviewCaptureThread is running");
    }
}

void LaneCalibrationController::killAllThreads(wxEvtHandler *parent) {
    auto tc = shared->getThreadController();

    if (!tc->isThreadNullptr(THREAD_LANE_CALIBRATION_CAMERA)) {
        calibrationCameraEndHandler(parent);
    }

    if (!tc->isThreadNullptr(THREAD_LANE_CALIBRATION_CAPTURE)) {
        calibrationCaptureEndHandler(parent);
    }

    if (!tc->isThreadNullptr(THREAD_CALIBRATION_PREVIEW_CAMERA)) {
        calibrationPreviewCameraEndHandler(parent);
    }

    if (!tc->isThreadNullptr(THREAD_CALIBRATION_PREVIEW_CAPTURE)) {
        calibrationPreviewCaptureEndHandler(parent);
    }

    throwIfAnyThreadIsRunning();
}

void LaneCalibrationController::changeToManualPanelHandler(
    wxEvtHandler *parent) {
    if (shared->isSessionDataChanged()) {
        auto wx = wxTheApp->GetTopWindow();
        auto dialog = CancelDialog(wx);
        if (dialog.ShowModal() == wxID_NO) {
            return;
        }
    }

    killAllThreads(parent);

    restoreSessionDataHandler(parent);

    ChangePanelData data(this->panelID, PanelID::PANEL_LANE_MANUAL_CALIBRATION);
    ChangePanelEvent::Submit(parent, data);
}

void LaneCalibrationController::changeToColorPanelHandler(
    wxEvtHandler *parent) {
    if (shared->isSessionDataChanged()) {
        auto dialog = CancelDialog(nullptr);
        if (dialog.ShowModal() == wxID_NO) {
            return;
        }
    }

    killAllThreads(parent);

    restoreSessionDataHandler(parent);

    ChangePanelData data(this->panelID, PanelID::PANEL_COLOR_CALIBRATION);
    ChangePanelEvent::Submit(parent, data);
}

void LaneCalibrationController::panelShowHandler(wxEvtHandler *parent) {
    createTempSessionDataHandler(parent);

    auto data = shared->getSessionData();

    if (!data->isCalibrationDataEmpty()) {
        return;
    }

    AppConfig c;
    auto config = c.GetThreadsConfig();
    auto startThread = config.autoCalibration;

    if (!startThread) {
        return;
    }

    calibrationStartHandler(parent);
}