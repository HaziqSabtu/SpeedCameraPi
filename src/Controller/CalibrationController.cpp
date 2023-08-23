#include "Algorithm/hsv_filter/BFS.hpp"
#include "Algorithm/hsv_filter/HSVFilter.hpp"
#include "Algorithm/ransac_line/RansacLine.hpp"
#include "Event/Event_UpdateState.hpp"
#include <Controller/CalibrationController.hpp>

#include "Model/SessionData.hpp"
#include "Thread/ThreadPool.hpp"
#include "Thread/Thread_Calibration.hpp"
#include "Thread/Thread_Capture.hpp"
#include "Thread/Thread_ID.hpp"
#include "Thread/Thread_LoadFile.hpp"
#include "UI/Dialog/CancelDialog.hpp"
#include "Utils/Camera/CameraBase.hpp"
#include "Utils/Config/AppConfig.hpp"
#include "Utils/Config/ConfigStruct.hpp"
#include <memory>
#include <vector>
#include <wx/event.h>
#include <wx/object.h>

CalibrationController::CalibrationController(ModelPtr sharedModel)
    : shared(sharedModel) {}

CalibrationController::~CalibrationController() {}

void CalibrationController::e_UpdateState(wxEvtHandler *parent) {
    try {
        AppState state(shared);
        UpdateStateEvent::Submit(parent, state);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void CalibrationController::e_PanelShow(wxEvtHandler *parent) {
    try {
        checkPreCondition();

        panelShowHandler(parent);

        e_UpdateState(parent);

    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void CalibrationController::e_CreateTempSessionData(wxEvtHandler *parent) {
    try {
        checkPreCondition();

        createTempSessionDataHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void CalibrationController::e_RestoreSessionData(wxEvtHandler *parent) {
    try {
        checkPreCondition();

        restoreSessionDataHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void CalibrationController::e_SaveSessionData(wxEvtHandler *parent) {
    try {
        checkPreCondition();

        saveSessionDataHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void CalibrationController::e_RemoveCalibData(wxEvtHandler *parent) {
    try {
        checkPreCondition();

        shared->sessionData.removeCalibrationData();
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void CalibrationController::e_CalibrationStart(wxEvtHandler *parent) {
    try {
        checkPreCondition();

        calibrationStartHandler(parent);

    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void CalibrationController::e_CalibrationEnd(wxEvtHandler *parent) {
    try {
        checkPreCondition();

        calibrationEndHandler(parent);

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

void CalibrationController::e_CalibrationPreviewStart(wxEvtHandler *parent) {
    try {
        checkPreCondition();

        calibrationPreviewStartHandler(parent);

    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void CalibrationController::e_CalibrationPreviewEnd(wxEvtHandler *parent) {
    try {
        checkPreCondition();

        calibrationPreviewEndHandler(parent);

    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void CalibrationController::e_CalibrationCapturePreviewStart(
    wxEvtHandler *parent) {
    try {
        checkPreCondition();

        calibrationCapturePreviewStartHandler(parent);

    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void CalibrationController::e_CalibrationCapturePreviewEnd(
    wxEvtHandler *parent) {
    try {
        checkPreCondition();

        calibrationCapturePreviewEndHandler(parent);

    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void CalibrationController::e_OKButtonHandler(wxEvtHandler *parent) {
    try {
        checkPreCondition();

        okButtonHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void CalibrationController::e_CancelButtonHandler(wxEvtHandler *parent) {
    try {
        checkPreCondition();

        cancelButtonHandler(parent);
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

void CalibrationController::e_SetPoint(wxEvtHandler *parent, wxPoint point) {
    try {

        checkPreCondition();

        setPointHandler(parent, Utils::wxPointToCvPoint(point));

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

void CalibrationController::calibrationStartHandler(wxEvtHandler *parent) {
    auto tc = shared->getThreadController();

    throwIfAnyThreadIsRunning();

    if (!shared->isCameraAvailable()) {
        throw std::runtime_error("Camera is not available");
    }

    auto camera = shared->getCamera();

    tc->startCalibrationHandler(parent, camera, panelID);
}

void CalibrationController::calibrationEndHandler(wxEvtHandler *parent) {
    auto tc = shared->getThreadController();

    if (tc->isThreadNullptr(THREAD_CALIBRATION)) {
        throw std::runtime_error("calibThread is not running");
    }

    if (!tc->isThreadOwner(THREAD_CALIBRATION, panelID)) {
        throw std::runtime_error("calibThread is not owned by this panel");
    }

    auto thread = tc->getCalibrationThread();
    thread->Pause();

    saveCalibrationData(parent, thread);

    auto camera = thread->getCamera();
    shared->setCamera(camera);

    tc->endCalibrationHandler();
}

void CalibrationController::calibrationCaptureStartHandler(
    wxEvtHandler *parent) {
    auto tc = shared->getThreadController();

    throwIfAnyThreadIsRunning();

    DataPtr data = shared->getSessionData();

    tc->startCaptureCalibrationHandler(parent, data, panelID);
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

    auto thread = tc->getCaptureCalibrationThread();
    thread->Pause();

    saveCalibrationData(parent, thread);

    tc->endCaptureCalibrationHandler();
}

void CalibrationController::calibrationPreviewStartHandler(
    wxEvtHandler *parent) {
    auto tc = shared->getThreadController();

    throwIfAnyThreadIsRunning();

    auto camera = shared->getCamera();

    if (camera == nullptr) {
        throw std::runtime_error("camera is nullptr");
    }

    DataPtr data = shared->getSessionData();

    tc->startCalibPreviewHandler(parent, camera, data, panelID);
}

void CalibrationController::calibrationPreviewEndHandler(wxEvtHandler *parent) {
    auto tc = shared->getThreadController();

    if (tc->isThreadNullptr(THREAD_CALIBRATION_PREVIEW)) {
        throw std::runtime_error("calibPrevThread is not running");
    }

    if (!tc->isThreadOwner(THREAD_CALIBRATION_PREVIEW, panelID)) {
        throw std::runtime_error("calibPrevThread is not owned by this panel");
    }

    auto thread = tc->getCalibPreviewThread();
    thread->Pause();

    auto camera = thread->getCamera();
    shared->setCamera(camera);

    tc->endCalibPreviewHandler();
}

void CalibrationController::calibrationCapturePreviewStartHandler(
    wxEvtHandler *parent) {
    auto tc = shared->getThreadController();

    throwIfAnyThreadIsRunning();

    auto data = shared->getSessionData();

    if (data->isCaptureDataEmpty()) {
        throw std::runtime_error("capture data is empty");
    }

    tc->startCalibCapturePreviewHandler(parent, data, panelID);
}

void CalibrationController::calibrationCapturePreviewEndHandler(
    wxEvtHandler *parent) {
    auto tc = shared->getThreadController();

    if (tc->isThreadNullptr(THREAD_CALIBRATION_PREVIEW_CAPTURE)) {
        throw std::runtime_error("calibCapPrevThread is not running");
    }

    if (!tc->isThreadOwner(THREAD_CALIBRATION_PREVIEW_CAPTURE, panelID)) {
        throw std::runtime_error(
            "calibCapPrevThread is not owned by this panel");
    }

    auto thread = tc->getCalibCapturePreviewThread();
    thread->Pause();

    tc->endCalibCapturePreviewHandler();
}

void CalibrationController::saveCalibrationData(wxEvtHandler *parent,
                                                BaseCalibrationThread *thread) {
    auto calibData = thread->getCalibData();

    AppConfig config;
    auto pConfig = config.GetPreviewConfig();
    int pWidth = pConfig.width;
    int pHeight = pConfig.height;
    cv::Size pSize(pWidth, pHeight);

    auto cConfig = config.GetCameraConfig();
    int cWidth = cConfig.Camera_Width;
    int cHeight = cConfig.Camera_Height;
    cv::Size cSize(cWidth, cHeight);

    auto leftLine = calibData.lineLeft;
    calibData.lineLeft = leftLine.Scale(pSize, cSize);

    auto rightLine = calibData.lineRight;
    calibData.lineRight = rightLine.Scale(pSize, cSize);

    auto data = shared->getSessionData();
    data->setCalibrationData(calibData);
}

void CalibrationController::setPointHandler(wxEvtHandler *parent,
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

void CalibrationController::checkPreCondition() {
    auto data = shared->getSessionData();
    if (panelID != data->getPanelID()) {
        throw std::runtime_error(
            "CalibrationController::endPoint() - PanelID mismatch");
    }
}

void CalibrationController::throwIfAnyThreadIsRunning() {
    auto tc = shared->getThreadController();

    if (!tc->isThreadNullptr(THREAD_CALIBRATION)) {
        throw std::runtime_error("CalibrationThread is running");
    }

    if (!tc->isThreadNullptr(THREAD_CALIBRATION_CAPTURE)) {
        throw std::runtime_error("CalibrationCaptureThread is running");
    }

    if (!tc->isThreadNullptr(THREAD_CALIBRATION_PREVIEW)) {
        throw std::runtime_error("CalibrationPreviewThread is running");
    }

    if (!tc->isThreadNullptr(THREAD_CALIBRATION_PREVIEW_CAPTURE)) {
        throw std::runtime_error("CalibrationPreviewCaptureThread is running");
    }
}

void CalibrationController::killAllThreads(wxEvtHandler *parent) {
    auto tc = shared->getThreadController();

    if (!tc->isThreadNullptr(THREAD_CALIBRATION)) {
        calibrationEndHandler(parent);
    }

    if (!tc->isThreadNullptr(THREAD_CALIBRATION_CAPTURE)) {
        calibrationCaptureEndHandler(parent);
    }

    if (!tc->isThreadNullptr(THREAD_CALIBRATION_PREVIEW)) {
        calibrationPreviewEndHandler(parent);
    }

    if (!tc->isThreadNullptr(THREAD_CALIBRATION_PREVIEW_CAPTURE)) {
        calibrationCapturePreviewEndHandler(parent);
    }

    throwIfAnyThreadIsRunning();
}

void CalibrationController::createTempSessionDataHandler(wxEvtHandler *parent) {
    auto temp = shared->getTempSessionData();

    if (temp == nullptr) {
        throw std::runtime_error("TempSessionData is nullptr");
    }

    auto data = shared->getSessionData();
    shared->setTempSessionData(*data);
}

void CalibrationController::saveSessionDataHandler(wxEvtHandler *parent) {
    auto temp = shared->getTempSessionData();

    if (temp == nullptr) {
        throw std::runtime_error("TempSessionData is nullptr");
    }

    shared->setTempSessionData(SessionData());
}

void CalibrationController::restoreSessionDataHandler(wxEvtHandler *parent) {
    auto temp = shared->getTempSessionData();

    if (temp == nullptr) {
        throw std::runtime_error("TempSessionData is nullptr");
    }

    shared->setSessionData(*temp);
}

void CalibrationController::okButtonHandler(wxEvtHandler *parent) {
    killAllThreads(parent);

    saveSessionDataHandler(parent);

    ChangePanelData data(this->panelID, PanelID::PANEL_CAPTURE);
    ChangePanelEvent::Submit(parent, data);
}

void CalibrationController::cancelButtonHandler(wxEvtHandler *parent) {
    if (shared->isSessionDataChanged()) {
        auto dialog = CancelDialog(nullptr);
        if (dialog.ShowModal() == wxID_NO) {
            return;
        }
    }

    killAllThreads(parent);

    restoreSessionDataHandler(parent);

    ChangePanelData data(this->panelID, PanelID::PANEL_CAPTURE);
    ChangePanelEvent::Submit(parent, data);
}

void CalibrationController::changeToManualPanelHandler(wxEvtHandler *parent) {
    if (shared->isSessionDataChanged()) {
        auto dialog = CancelDialog(nullptr);
        if (dialog.ShowModal() == wxID_NO) {
            return;
        }
    }

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
        return calibrationStartHandler(parent);

    calibrationCaptureStartHandler(parent);
}