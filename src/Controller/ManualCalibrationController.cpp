#include "Event/Event_UpdateStatus.hpp"
#include "Thread/Thread_ID.hpp"
#include "UI/Data/StatusData.hpp"
#include "UI/Dialog/RemoveCalibrationDialog.hpp"
#include <Controller/ManualCalibrationController.hpp>

ManualCalibrationController::ManualCalibrationController(ModelPtr sharedModel)
    : BaseControllerWithTouch(sharedModel) {
    panelID = currentPanelID;
}

ManualCalibrationController::~ManualCalibrationController() {}

void ManualCalibrationController::throwIfAnyThreadIsRunning() {
    auto tc = shared->getThreadController();

    if (!tc->isThreadNullptr(THREAD_MANUAL_CALIBRATION_CAMERA)) {
        throw std::runtime_error("manualCalibThread is running");
    }

    if (!tc->isThreadNullptr(THREAD_MANUAL_CALIBRATION_CAPTURE)) {
        throw std::runtime_error("manualCalibCapTureThread is running");
    }

    if (!tc->isThreadNullptr(THREAD_CALIBRATION_PREVIEW_CAPTURE)) {
        throw std::runtime_error("calibCapPrevThread is running");
    }

    if (!tc->isThreadNullptr(THREAD_CALIBRATION_PREVIEW_CAMERA)) {
        throw std::runtime_error("calibPrevThread is running");
    }
}

void ManualCalibrationController::killAllThreads(wxEvtHandler *parent) {
    auto tc = shared->getThreadController();

    if (!tc->isThreadNullptr(THREAD_MANUAL_CALIBRATION_CAMERA)) {
        manualCalibrationCameraEndHandler(parent);
    }

    if (!tc->isThreadNullptr(THREAD_MANUAL_CALIBRATION_CAPTURE)) {
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

void ManualCalibrationController::e_ChangeToLeft(wxEvtHandler *parent) {
    try {
        checkPreCondition();
        changeToLeftHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void ManualCalibrationController::e_ChangeToRight(wxEvtHandler *parent) {
    try {
        checkPreCondition();
        changeToRightHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void ManualCalibrationController::e_ManualCalibrationStart(
    wxEvtHandler *parent) {
    try {
        checkPreCondition();
        manualCalibrationStartHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void ManualCalibrationController::e_ManualCalibrationEnd(wxEvtHandler *parent) {
    try {
        checkPreCondition();
        manualCalibrationEndHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void ManualCalibrationController::e_ManualCalibrationCameraStart(
    wxEvtHandler *parent) {
    try {
        checkPreCondition();
        manualCalibrationCameraStartHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void ManualCalibrationController::e_ManualCalibrationCameraEnd(
    wxEvtHandler *parent) {
    try {
        checkPreCondition();
        manualCalibrationCameraEndHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void ManualCalibrationController::e_ManualCalibrationCaptureStart(
    wxEvtHandler *parent) {
    try {
        checkPreCondition();
        manualCalibrationCaptureStartHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void ManualCalibrationController::e_ManualCalibrationCaptureEnd(
    wxEvtHandler *parent) {
    try {
        checkPreCondition();
        manualCalibrationCaptureEndHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void ManualCalibrationController::e_CalibrationPreviewStart(
    wxEvtHandler *parent) {
    try {
        checkPreCondition();
        calibrationPreviewStartHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void ManualCalibrationController::e_CalibrationPreviewEnd(
    wxEvtHandler *parent) {
    try {
        checkPreCondition();
        calibrationPreviewEndHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void ManualCalibrationController::e_CalibrationPreviewCameraStart(
    wxEvtHandler *parent) {
    try {
        checkPreCondition();
        calibrationPreviewCameraStartHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void ManualCalibrationController::e_CalibrationPreviewCameraEnd(
    wxEvtHandler *parent) {
    try {
        checkPreCondition();
        calibrationPreviewCameraEndHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void ManualCalibrationController::e_CalibrationPreviewCaptureStart(
    wxEvtHandler *parent) {
    try {
        checkPreCondition();
        calibrationPreviewCaptureStartHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void ManualCalibrationController::e_CalibrationPreviewCaptureEnd(
    wxEvtHandler *parent) {
    try {
        checkPreCondition();
        calibrationPreviewCaptureEndHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void ManualCalibrationController::e_RemoveLeft(wxEvtHandler *parent) {
    try {
        checkPreCondition();
        removeLeftHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void ManualCalibrationController::e_RemoveRight(wxEvtHandler *parent) {
    try {
        checkPreCondition();
        removeRightHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void ManualCalibrationController::e_RemoveCalibrationData(
    wxEvtHandler *parent) {
    try {
        checkPreCondition();
        removeCalibrationDataHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void ManualCalibrationController::changeToLeftHandler(wxEvtHandler *parent) {
    auto tc = shared->getThreadController();

    if (!tc->isManualCalibrationThreadRunning()) {
        throw std::runtime_error("Calibration thread is not running");
    }

    if (!tc->isManualCalibrationThreadOwner(panelID)) {
        throw std::runtime_error(
            "Calibration thread is not owned by this panel");
    }

    auto thread = tc->getRunningManualCalibrationThread();

    thread->setDirection(ManualDirection::MANUAL_LEFT);

    UpdateStatusEvent::Submit(parent, SC::STATUS_MANUAL_SELECTLEFT);
}

void ManualCalibrationController::changeToRightHandler(wxEvtHandler *parent) {
    auto tc = shared->getThreadController();

    if (!tc->isManualCalibrationThreadRunning()) {
        throw std::runtime_error("Calibration thread is not running");
    }

    if (!tc->isManualCalibrationThreadOwner(panelID)) {
        throw std::runtime_error(
            "Calibration thread is not owned by this panel");
    }

    auto thread = tc->getRunningManualCalibrationThread();

    thread->setDirection(ManualDirection::MANUAL_RIGHT);

    UpdateStatusEvent::Submit(parent, SC::STATUS_MANUAL_SELECTRIGHT);
}

void ManualCalibrationController::leftDownHandler(wxEvtHandler *parent,
                                                  cv::Point point) {
    auto tc = shared->getThreadController();

    if (!tc->isManualCalibrationThreadRunning()) {
        throw std::runtime_error("Calibration thread is not running");
    }

    if (!tc->isManualCalibrationThreadOwner(panelID)) {
        throw std::runtime_error(
            "Calibration thread is not owned by this panel");
    }

    auto thread = tc->getRunningManualCalibrationThread();

    thread->setPoint1(point);
}

void ManualCalibrationController::leftMoveHandler(wxEvtHandler *parent,
                                                  cv::Point point) {
    auto tc = shared->getThreadController();

    if (!tc->isManualCalibrationThreadRunning()) {
        throw std::runtime_error("Calibration thread is not running");
    }

    if (!tc->isManualCalibrationThreadOwner(panelID)) {
        throw std::runtime_error(
            "Calibration thread is not owned by this panel");
    }

    auto thread = tc->getRunningManualCalibrationThread();

    thread->setPoint2(point);
}

void ManualCalibrationController::leftUpHandler(wxEvtHandler *parent,
                                                cv::Point point) {
    auto tc = shared->getThreadController();

    if (!tc->isManualCalibrationThreadRunning()) {
        throw std::runtime_error("Calibration thread is not running");
    }

    if (!tc->isManualCalibrationThreadOwner(panelID)) {
        throw std::runtime_error(
            "Calibration thread is not owned by this panel");
    }

    auto thread = tc->getRunningManualCalibrationThread();

    thread->setPoint2AndExtend(point);

    auto dir = thread->getDirection();
    auto line = dir == MANUAL_LEFT ? thread->getRealLeftLine()
                                   : thread->getRealRightLine();

    auto data = shared->getSessionData();

    auto calibData = data->getCalibrationData();

    dir == MANUAL_LEFT ? calibData.lineLeft = line : calibData.lineRight = line;

    data->setCalibrationData(calibData);
}

void ManualCalibrationController::manualCalibrationStartHandler(
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

void ManualCalibrationController::manualCalibrationEndHandler(
    wxEvtHandler *parent) {
    auto tc = shared->getThreadController();

    if (!tc->isManualCalibrationThreadRunning()) {
        throw std::runtime_error("manualCalibThread is not running");
    }

    auto thread = tc->getRunningManualCalibrationThread();
    if (thread->getID() == THREAD_MANUAL_CALIBRATION_CAMERA) {
        manualCalibrationCameraEndHandler(parent);
    } else {
        manualCalibrationCaptureEndHandler(parent);
    }
}

void ManualCalibrationController::manualCalibrationCameraStartHandler(
    wxEvtHandler *parent) {
    auto tc = shared->getThreadController();

    throwIfAnyThreadIsRunning();

    if (!shared->isCameraAvailable()) {
        throw std::runtime_error("Camera is not available");
    }

    auto camera = shared->getCamera();

    tc->startManualCalibrationCameraHandler(parent, camera, panelID);
}

void ManualCalibrationController::manualCalibrationCameraEndHandler(
    wxEvtHandler *parent) {
    auto tc = shared->getThreadController();

    if (tc->isThreadNullptr(THREAD_MANUAL_CALIBRATION_CAMERA)) {
        throw std::runtime_error("manualCalibThread is not running");
    }

    if (!tc->isThreadOwner(THREAD_MANUAL_CALIBRATION_CAMERA, panelID)) {
        throw std::runtime_error(
            "manualCalibThread is not owned by this panel");
    }

    auto thread = tc->getManualCalibrationCameraThread();
    thread->Pause();

    auto camera = thread->getCamera();
    shared->setCamera(camera);

    tc->endManualCalibrationCameraHandler();
}

void ManualCalibrationController::manualCalibrationCaptureStartHandler(
    wxEvtHandler *parent) {
    auto tc = shared->getThreadController();

    throwIfAnyThreadIsRunning();

    DataPtr data = shared->getSessionData();

    tc->startManualCalibrationCaptureHandler(parent, data, panelID);
}

void ManualCalibrationController::manualCalibrationCaptureEndHandler(
    wxEvtHandler *parent) {
    auto tc = shared->getThreadController();

    if (tc->isThreadNullptr(THREAD_MANUAL_CALIBRATION_CAPTURE)) {
        throw std::runtime_error("manualCalibCaptureThread is not running");
    }

    if (!tc->isThreadOwner(THREAD_MANUAL_CALIBRATION_CAPTURE, panelID)) {
        throw std::runtime_error(
            "manualCalibCaptureThread is not owned by this panel");
    }

    auto thread = tc->getManualCalibrationCaptureThread();
    thread->Pause();

    tc->endManualCalibrationCaptureHandler();
}

void ManualCalibrationController::calibrationPreviewStartHandler(
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

void ManualCalibrationController::calibrationPreviewEndHandler(
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

void ManualCalibrationController::calibrationPreviewCameraStartHandler(
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

void ManualCalibrationController::calibrationPreviewCameraEndHandler(
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

void ManualCalibrationController::calibrationPreviewCaptureStartHandler(
    wxEvtHandler *parent) {
    auto tc = shared->getThreadController();

    throwIfAnyThreadIsRunning();

    auto data = shared->getSessionData();

    if (data->isCaptureDataEmpty()) {
        throw std::runtime_error("capture data is empty");
    }

    tc->startCalibrationPreviewCaptureHandler(parent, data, panelID);
}

void ManualCalibrationController::calibrationPreviewCaptureEndHandler(
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

void ManualCalibrationController::removeLeftHandler(wxEvtHandler *parent) {
    auto tc = shared->getThreadController();

    if (!tc->isManualCalibrationThreadRunning()) {
        throw std::runtime_error("Calibration thread is not running");
    }

    if (!tc->isManualCalibrationThreadOwner(panelID)) {
        throw std::runtime_error(
            "Calibration thread is not owned by this panel");
    }

    auto thread = tc->getRunningManualCalibrationThread();

    thread->setLeftLine(Line());

    auto data = shared->getSessionData();

    auto calibData = data->getCalibrationData();

    calibData.lineLeft = Line();

    data->setCalibrationData(calibData);

    UpdateStatusEvent::Submit(parent, SC::STATUS_MANUAL_REMOVELEFT);
}

void ManualCalibrationController::removeRightHandler(wxEvtHandler *parent) {
    auto tc = shared->getThreadController();

    if (!tc->isManualCalibrationThreadRunning()) {
        throw std::runtime_error("Calibration thread is not running");
    }

    if (!tc->isManualCalibrationThreadOwner(panelID)) {
        throw std::runtime_error(
            "Calibration thread is not owned by this panel");
    }

    auto thread = tc->getRunningManualCalibrationThread();

    thread->setRightLine(Line());

    auto data = shared->getSessionData();

    auto calibData = data->getCalibrationData();

    calibData.lineRight = Line();

    data->setCalibrationData(calibData);

    UpdateStatusEvent::Submit(parent, SC::STATUS_MANUAL_REMOVERIGHT);
}

void ManualCalibrationController::removeCalibrationDataHandler(
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

void ManualCalibrationController::panelShowHandler(wxEvtHandler *parent) {
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

    if (data->isCaptureDataEmpty())
        return manualCalibrationCameraStartHandler(parent);

    manualCalibrationCaptureStartHandler(parent);
}
