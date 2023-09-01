#include <Controller/CalibrationController.hpp>
#include <stdexcept>

CalibrationController::CalibrationController(ModelPtr sharedModel)
    : BaseControllerWithTouch(sharedModel) {
    panelID = currentPanelID;
}

CalibrationController::~CalibrationController() {}

void CalibrationController::e_RemoveCalibData(wxEvtHandler *parent) {
    try {
        checkPreCondition();
        shared->sessionData.removeCalibrationData();
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void CalibrationController::e_CalibrationCameraStart(wxEvtHandler *parent) {
    try {
        checkPreCondition();
        calibrationCameraStartHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void CalibrationController::e_CalibrationCameraEnd(wxEvtHandler *parent) {
    try {
        checkPreCondition();
        calibrationCameraEndHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void CalibrationController::e_CalibrationCaptureStart(wxEvtHandler *parent) {
    try {
        checkPreCondition();
        calibrationCaptureStartHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void CalibrationController::e_CalibrationCaptureEnd(wxEvtHandler *parent) {
    try {
        checkPreCondition();
        calibrationCaptureEndHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void CalibrationController::e_CalibrationPreviewCameraStart(
    wxEvtHandler *parent) {
    try {
        checkPreCondition();
        calibrationPreviewCameraStartHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void CalibrationController::e_CalibrationPreviewCameraEnd(
    wxEvtHandler *parent) {
    try {
        checkPreCondition();
        calibrationPreviewCameraEndHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void CalibrationController::e_CalibrationPreviewCaptureStart(
    wxEvtHandler *parent) {
    try {
        checkPreCondition();
        calibrationPreviewCaptureStartHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void CalibrationController::e_CalibrationPreviewCaptureEnd(
    wxEvtHandler *parent) {
    try {
        checkPreCondition();
        calibrationPreviewCaptureEndHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void CalibrationController::e_ChangeToManualPanel(wxEvtHandler *parent) {
    try {
        checkPreCondition();
        changeToManualPanelHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void CalibrationController::e_ChangeToColorPanel(wxEvtHandler *parent) {
    try {
        checkPreCondition();
        changeToColorPanelHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void CalibrationController::e_ClearPoint(wxEvtHandler *parent) {
    try {
        checkPreCondition();
        clearPointHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void CalibrationController::calibrationCameraStartHandler(
    wxEvtHandler *parent) {
    auto tc = shared->getThreadController();

    throwIfAnyThreadIsRunning();

    if (!shared->isCameraAvailable()) {
        throw std::runtime_error("Camera is not available");
    }

    auto camera = shared->getCamera();

    tc->startCalibrationCameraHandler(parent, camera, panelID);
}

void CalibrationController::calibrationCameraEndHandler(wxEvtHandler *parent) {
    auto tc = shared->getThreadController();

    if (tc->isThreadNullptr(THREAD_CALIBRATION_CAMERA)) {
        throw std::runtime_error("calibThread is not running");
    }

    if (!tc->isThreadOwner(THREAD_CALIBRATION_CAMERA, panelID)) {
        throw std::runtime_error("calibThread is not owned by this panel");
    }

    auto thread = tc->getCalibrationCameraThread();
    thread->Pause();

    saveCalibrationData(parent, thread);

    auto camera = thread->getCamera();
    shared->setCamera(camera);

    tc->endCalibrationCameraHandler();
}

void CalibrationController::calibrationCaptureStartHandler(
    wxEvtHandler *parent) {
    auto tc = shared->getThreadController();

    throwIfAnyThreadIsRunning();

    DataPtr data = shared->getSessionData();

    tc->startCalibrationCaptureHandler(parent, data, panelID);
}

void CalibrationController::calibrationCaptureEndHandler(wxEvtHandler *parent) {
    auto tc = shared->getThreadController();

    if (tc->isThreadNullptr(THREAD_CALIBRATION_CAPTURE)) {
        throw std::runtime_error("calibCaptureThread is not running");
    }

    if (!tc->isThreadOwner(THREAD_CALIBRATION_CAPTURE, panelID)) {
        throw std::runtime_error(
            "calibCaptureThread is not owned by this panel");
    }

    auto thread = tc->getCalibrationCaptureThread();
    thread->Pause();

    saveCalibrationData(parent, thread);

    tc->endCalibrationCaptureHandler();
}

void CalibrationController::calibrationPreviewCameraStartHandler(
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

void CalibrationController::calibrationPreviewCameraEndHandler(
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

void CalibrationController::calibrationPreviewCaptureStartHandler(
    wxEvtHandler *parent) {
    auto tc = shared->getThreadController();

    throwIfAnyThreadIsRunning();

    auto data = shared->getSessionData();

    if (data->isCaptureDataEmpty()) {
        throw std::runtime_error("capture data is empty");
    }

    tc->startCalibrationPreviewCaptureHandler(parent, data, panelID);
}

void CalibrationController::calibrationPreviewCaptureEndHandler(
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

void CalibrationController::saveCalibrationData(wxEvtHandler *parent,
                                                BaseCalibrationThread *thread) {
    auto calibData = thread->getCalibrationData();

    auto data = shared->getSessionData();
    data->setCalibrationData(calibData);
}

void CalibrationController::leftDownHandler(wxEvtHandler *parent,
                                            cv::Point point) {
    auto tc = shared->getThreadController();

    if (!tc->isCalibrationThreadRunning()) {
        throw std::runtime_error("calibration Thread is not running");
    }

    if (!tc->isCalibrationThreadOwner(panelID)) {
        throw std::runtime_error(
            "calibration Thread is not owned by this panel");
    }

    auto thread = tc->getRunningCalibrationThread();
    thread->setPoint(point);
}

void CalibrationController::leftMoveHandler(wxEvtHandler *parent,
                                            cv::Point point) {
    throw std::runtime_error("Blocked Endpoint");
}

void CalibrationController::leftUpHandler(wxEvtHandler *parent,
                                          cv::Point point) {
    throw std::runtime_error("Blocked Endpoint");
}

void CalibrationController::clearPointHandler(wxEvtHandler *parent) {
    auto tc = shared->getThreadController();

    if (!tc->isCalibrationThreadRunning()) {
        throw std::runtime_error("calibration Thread is not running");
    }

    if (!tc->isCalibrationThreadOwner(panelID)) {
        throw std::runtime_error(
            "calibration Thread is not owned by this panel");
    }

    auto thread = tc->getRunningCalibrationThread();
    thread->clearPoint();
}

void CalibrationController::throwIfAnyThreadIsRunning() {
    auto tc = shared->getThreadController();

    if (!tc->isThreadNullptr(THREAD_CALIBRATION_CAMERA)) {
        throw std::runtime_error("CalibrationThread is running");
    }

    if (!tc->isThreadNullptr(THREAD_CALIBRATION_CAPTURE)) {
        throw std::runtime_error("CalibrationCaptureThread is running");
    }

    if (!tc->isThreadNullptr(THREAD_CALIBRATION_PREVIEW_CAMERA)) {
        throw std::runtime_error("CalibrationPreviewThread is running");
    }

    if (!tc->isThreadNullptr(THREAD_CALIBRATION_PREVIEW_CAPTURE)) {
        throw std::runtime_error("CalibrationPreviewCaptureThread is running");
    }
}

void CalibrationController::killAllThreads(wxEvtHandler *parent) {
    auto tc = shared->getThreadController();

    if (!tc->isThreadNullptr(THREAD_CALIBRATION_CAMERA)) {
        calibrationCameraEndHandler(parent);
    }

    if (!tc->isThreadNullptr(THREAD_CALIBRATION_CAPTURE)) {
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

void CalibrationController::changeToManualPanelHandler(wxEvtHandler *parent) {
    if (shared->isSessionDataChanged()) {
        auto dialog = CancelDialog(nullptr);
        if (dialog.ShowModal() == wxID_NO) {
            return;
        }
    }

    // TODO: Add Dialog

    killAllThreads(parent);

    restoreSessionDataHandler(parent);

    ChangePanelData data(this->panelID, PanelID::PANEL_MANUAL_CALIBRATION);
    ChangePanelEvent::Submit(parent, data);
}

void CalibrationController::changeToColorPanelHandler(wxEvtHandler *parent) {
    if (shared->isSessionDataChanged()) {
        auto dialog = CancelDialog(nullptr);
        if (dialog.ShowModal() == wxID_NO) {
            return;
        }
    }

    // TODO: Add Dialog

    killAllThreads(parent);

    restoreSessionDataHandler(parent);

    ChangePanelData data(this->panelID, PanelID::PANEL_COLOR_CALIBRATION);
    ChangePanelEvent::Submit(parent, data);
}

void CalibrationController::panelShowHandler(wxEvtHandler *parent) {
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

    if (data->isCaptureDataEmpty())
        return calibrationCameraStartHandler(parent);

    calibrationCaptureStartHandler(parent);
}