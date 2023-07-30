#include "Model/SharedModel.hpp"
#include "Thread/Thread_ID.hpp"
#include <Controller/ColorCalibrationController.hpp>

ColorCalibrationController::ColorCalibrationController(ModelPtr sharedModel)
    : shared(sharedModel) {}

ColorCalibrationController::~ColorCalibrationController() {}

void ColorCalibrationController::checkPreCondition() {
    if (panelID != shared->sessionData.currentPanelID) {
        throw std::runtime_error(
            "ColorCalibrationController::endPoint() - PanelID mismatch");
    }
}

void ColorCalibrationController::e_ChangeToCapturePanel(wxEvtHandler *parent) {
    try {
        checkPreCondition();
        ChangePanelData data(this->panelID, PanelID::PANEL_CAPTURE);
        ChangePanelEvent::Submit(parent, data);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void ColorCalibrationController::e_ChangeToCalibrationPanel(
    wxEvtHandler *parent) {
    try {
        checkPreCondition();
        ChangePanelData data(this->panelID, PanelID::PANEL_CALIBRATION);
        ChangePanelEvent::Submit(parent, data);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void ColorCalibrationController::e_ColorCalibrationStart(wxEvtHandler *parent) {
    try {
        checkPreCondition();

        colorCalibrationStartHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void ColorCalibrationController::e_ColorCalibrationEnd(wxEvtHandler *parent) {
    try {
        checkPreCondition();

        colorCalibrationEndHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void ColorCalibrationController::colorCalibrationStartHandler(
    wxEvtHandler *parent) {
    auto tc = shared->getThreadController();

    if (!shared->isCameraAvailable()) {
        throw std::runtime_error("Camera is not available");
    }

    if (!tc->isThreadsWithCameraNullptr()) {
        throw std::runtime_error("Thread with camera is already running");
    }

    if (!tc->isThreadNullptr(THREAD_COLOR_CALIBRATION)) {
        throw std::runtime_error("ColorCalibrationThread is already running");
    }

    auto camera = shared->getCamera();

    HSVFilter filter;
    BFS bfs;

    tc->startColorCalibrationHandler(parent, camera, filter, bfs, panelID);
}

void ColorCalibrationController::colorCalibrationEndHandler(
    wxEvtHandler *parent) {

    auto tc = shared->getThreadController();

    if (tc->isThreadNullptr(THREAD_COLOR_CALIBRATION)) {
        throw std::runtime_error("ColorCalibrationThread is not running");
    }

    if (!tc->isThreadOwner(THREAD_COLOR_CALIBRATION, panelID)) {
        throw std::runtime_error(
            "ColorCalibrationThread is not owned by this panel");
    }

    auto calibrationThread = tc->getColorCalibrationThread();
    calibrationThread->Pause();

    auto camera = calibrationThread->getCamera();
    shared->setCamera(camera);

    tc->endColorCalibrationHandler();
}