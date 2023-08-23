#include "Algorithm/Struct/D_Line.hpp"
#include "Event/Event_UpdateState.hpp"
#include "Model/AppState.hpp"
#include "Model/CalibrationData.hpp"
#include "Model/SessionData.hpp"
#include "Model/SharedModel.hpp"
#include "Thread/Thread_ID.hpp"
#include "Thread/Thread_ManualCalib.hpp"
#include "UI/Dialog/CancelDialog.hpp"
#include "Utils/wxUtils.hpp"

#include <Controller/ManualCalibrationController.hpp>
#include <wx/event.h>

ManualCalibrationController::ManualCalibrationController(ModelPtr sharedModel)
    : shared(sharedModel) {}

void ManualCalibrationController::e_UpdateState(wxEvtHandler *parent) {
    try {
        AppState state(shared);
        UpdateStateEvent::Submit(parent, state);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

ManualCalibrationController::~ManualCalibrationController() {}

void ManualCalibrationController::checkPreCondition() {
    auto data = shared->getSessionData();
    if (panelID != data->getPanelID()) {
        throw std::runtime_error(
            "ManualCalibrationController::endPoint() - PanelID mismatch");
    }
}

void ManualCalibrationController::e_PanelShow(wxEvtHandler *parent) {
    try {
        checkPreCondition();

        panelShowHandler(parent);

        e_UpdateState(parent);

    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void ManualCalibrationController::throwIfAnyThreadIsRunning() {
    auto tc = shared->getThreadController();

    if (!tc->isThreadNullptr(THREAD_MANUAL_CALIBRATION)) {
        throw std::runtime_error("manualCalibThread is running");
    }

    if (!tc->isThreadNullptr(THREAD_MANUAL_CALIBRATION_CAPTURE)) {
        throw std::runtime_error("manualCalibCapTureThread is running");
    }

    if (!tc->isThreadNullptr(THREAD_CALIBRATION_PREVIEW_CAPTURE)) {
        throw std::runtime_error("calibCapPrevThread is running");
    }

    if (!tc->isThreadNullptr(THREAD_CALIBRATION_PREVIEW)) {
        throw std::runtime_error("calibPrevThread is running");
    }
}

void ManualCalibrationController::killAllThreads(wxEvtHandler *parent) {
    auto tc = shared->getThreadController();

    if (!tc->isThreadNullptr(THREAD_MANUAL_CALIBRATION)) {
        manualCalibEndHandler(parent);
    }

    if (!tc->isThreadNullptr(THREAD_MANUAL_CALIBRATION_CAPTURE)) {
        manualCalibCaptureEndHandler(parent);
    }

    if (!tc->isThreadNullptr(THREAD_CALIBRATION_PREVIEW_CAPTURE)) {
        calibCapturePrevEndHandler(parent);
    }

    if (!tc->isThreadNullptr(THREAD_CALIBRATION_PREVIEW)) {
        calibPrevEndHandler(parent);
    }

    throwIfAnyThreadIsRunning();
}

void ManualCalibrationController::e_CreateTempSessionData(
    wxEvtHandler *parent) {
    try {
        checkPreCondition();

        createTempSessionDataHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void ManualCalibrationController::e_RestoreSessionData(wxEvtHandler *parent) {
    try {
        checkPreCondition();

        restoreSessionDataHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void ManualCalibrationController::e_SaveSessionData(wxEvtHandler *parent) {
    try {
        checkPreCondition();

        saveSessionDataHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void ManualCalibrationController::e_OKButtonHandler(wxEvtHandler *parent) {
    try {
        checkPreCondition();

        okButtonHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void ManualCalibrationController::e_CancelButtonHandler(wxEvtHandler *parent) {
    try {
        checkPreCondition();

        cancelButtonHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
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

void ManualCalibrationController::e_SetPoint1(wxEvtHandler *parent,
                                              wxPoint point) {
    try {
        checkPreCondition();

        setPoint1Handler(parent, Utils::wxPointToCvPoint(point));

    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void ManualCalibrationController::e_SetPoint2(wxEvtHandler *parent,
                                              wxPoint point) {
    try {
        checkPreCondition();

        setPoint2Handler(parent, Utils::wxPointToCvPoint(point));

    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void ManualCalibrationController::e_SaveLine(wxEvtHandler *parent,
                                             wxPoint point) {
    try {
        checkPreCondition();

        saveLineHandler(parent, Utils::wxPointToCvPoint(point));

    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void ManualCalibrationController::e_ManualCalibStart(wxEvtHandler *parent) {
    try {
        checkPreCondition();

        manualCalibStartHandler(parent);

    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void ManualCalibrationController::e_ManualCalibEnd(wxEvtHandler *parent) {
    try {
        checkPreCondition();

        manualCalibEndHandler(parent);

    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void ManualCalibrationController::e_ManualCalibCaptureStart(
    wxEvtHandler *parent) {
    try {
        checkPreCondition();

        manualCalibCaptureStartHandler(parent);

    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void ManualCalibrationController::e_ManualCalibCaptureEnd(
    wxEvtHandler *parent) {
    try {
        checkPreCondition();

        manualCalibCaptureEndHandler(parent);

    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void ManualCalibrationController::e_CalibPrevStart(wxEvtHandler *parent) {
    try {
        checkPreCondition();

        calibPrevStartHandler(parent);

    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void ManualCalibrationController::e_CalibPrevEnd(wxEvtHandler *parent) {
    try {
        checkPreCondition();

        calibPrevEndHandler(parent);

    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void ManualCalibrationController::e_CalibCapturePrevStart(
    wxEvtHandler *parent) {
    try {
        checkPreCondition();

        calibCapturePrevStartHandler(parent);

    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void ManualCalibrationController::e_CalibCapturePrevEnd(wxEvtHandler *parent) {
    try {
        checkPreCondition();

        calibCapturePrevEndHandler(parent);

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

void ManualCalibrationController::e_RemoveCalibData(wxEvtHandler *parent) {
    try {
        checkPreCondition();

        removeCalibDataHandler(parent);

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
}

void ManualCalibrationController::setPoint1Handler(wxEvtHandler *parent,
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

void ManualCalibrationController::setPoint2Handler(wxEvtHandler *parent,
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

void ManualCalibrationController::saveLineHandler(wxEvtHandler *parent,
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
    auto line =
        dir == MANUAL_LEFT ? thread->getBlueLine() : thread->getYellowLine();

    auto data = shared->getSessionData();

    // TODO: Do this inside thread
    AppConfig config;
    auto pConfig = config.GetPreviewConfig();
    int pWidth = pConfig.width;
    int pHeight = pConfig.height;
    cv::Size src(pWidth, pHeight);

    auto cConfig = config.GetCameraConfig();

    int width = cConfig.Camera_Width;
    int height = cConfig.Camera_Height;
    cv::Size dst(width, height);

    auto realLine = line.Scale(src, dst);

    auto calibData = data->getCalibrationData();

    dir == MANUAL_LEFT ? calibData.lineLeft = realLine
                       : calibData.lineRight = realLine;

    data->setCalibrationData(calibData);
}

void ManualCalibrationController::manualCalibStartHandler(
    wxEvtHandler *parent) {
    auto tc = shared->getThreadController();

    throwIfAnyThreadIsRunning();

    if (!shared->isCameraAvailable()) {
        throw std::runtime_error("Camera is not available");
    }

    auto camera = shared->getCamera();

    tc->startManualCalibrationHandler(parent, camera, panelID);
}

void ManualCalibrationController::manualCalibEndHandler(wxEvtHandler *parent) {
    auto tc = shared->getThreadController();

    if (tc->isThreadNullptr(THREAD_MANUAL_CALIBRATION)) {
        throw std::runtime_error("manualCalibThread is not running");
    }

    if (!tc->isThreadOwner(THREAD_MANUAL_CALIBRATION, panelID)) {
        throw std::runtime_error(
            "manualCalibThread is not owned by this panel");
    }

    auto thread = tc->getManualCalibrationThread();
    thread->Pause();

    auto camera = thread->getCamera();
    shared->setCamera(camera);

    tc->endManualCalibrationHandler();
}

void ManualCalibrationController::manualCalibCaptureStartHandler(
    wxEvtHandler *parent) {
    auto tc = shared->getThreadController();

    throwIfAnyThreadIsRunning();

    DataPtr data = shared->getSessionData();

    tc->startManualCalibrationCaptureHandler(parent, data, panelID);
}

void ManualCalibrationController::manualCalibCaptureEndHandler(
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

void ManualCalibrationController::calibPrevStartHandler(wxEvtHandler *parent) {
    auto tc = shared->getThreadController();

    throwIfAnyThreadIsRunning();

    auto camera = shared->getCamera();

    if (camera == nullptr) {
        throw std::runtime_error("camera is nullptr");
    }

    DataPtr data = shared->getSessionData();

    tc->startCalibPreviewHandler(parent, camera, data, panelID);
}

void ManualCalibrationController::calibPrevEndHandler(wxEvtHandler *parent) {
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

void ManualCalibrationController::calibCapturePrevStartHandler(
    wxEvtHandler *parent) {
    auto tc = shared->getThreadController();

    throwIfAnyThreadIsRunning();

    auto data = shared->getSessionData();

    if (data->isCaptureDataEmpty()) {
        throw std::runtime_error("capture data is empty");
    }

    tc->startCalibCapturePreviewHandler(parent, data, panelID);
}

void ManualCalibrationController::calibCapturePrevEndHandler(
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

    thread->setBlueLine(Line());

    auto data = shared->getSessionData();

    auto calibData = data->getCalibrationData();

    calibData.lineLeft = Line();

    data->setCalibrationData(calibData);
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

    thread->setYellowLine(Line());

    auto data = shared->getSessionData();

    auto calibData = data->getCalibrationData();

    calibData.lineRight = Line();

    data->setCalibrationData(calibData);
}

void ManualCalibrationController::createTempSessionDataHandler(
    wxEvtHandler *parent) {
    auto temp = shared->getTempSessionData();

    if (temp == nullptr) {
        throw std::runtime_error("TempSessionData is nullptr");
    }

    auto data = shared->getSessionData();
    shared->setTempSessionData(*data);
}

void ManualCalibrationController::saveSessionDataHandler(wxEvtHandler *parent) {
    auto temp = shared->getTempSessionData();

    //  will it ever null?
    if (temp == nullptr) {
        throw std::runtime_error("TempSessionData is nullptr");
    }

    shared->setTempSessionData(SessionData());
}

void ManualCalibrationController::restoreSessionDataHandler(
    wxEvtHandler *parent) {
    auto temp = shared->getTempSessionData();

    if (temp == nullptr) {
        throw std::runtime_error("TempSessionData is nullptr");
    }

    shared->setSessionData(*temp);
}

void ManualCalibrationController::removeCalibDataHandler(wxEvtHandler *parent) {
    auto tc = shared->getThreadController();

    throwIfAnyThreadIsRunning();

    auto data = shared->getSessionData();

    data->removeCalibrationData();
}

void ManualCalibrationController::okButtonHandler(wxEvtHandler *parent) {

    killAllThreads(parent);

    saveSessionDataHandler(parent);

    ChangePanelData data(this->panelID, PanelID::PANEL_CAPTURE);
    ChangePanelEvent::Submit(parent, data);
}

void ManualCalibrationController::cancelButtonHandler(wxEvtHandler *parent) {

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
        return manualCalibStartHandler(parent);

    manualCalibCaptureStartHandler(parent);
}
