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
#include "Utils/Camera/CameraBase.hpp"
#include "Utils/Config/AppConfig.hpp"
#include "Utils/Config/ConfigStruct.hpp"
#include "Utils/DataStruct.hpp"
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

void CalibrationController::e_RemoveCalibData(wxEvtHandler *parent) {
    try {
        checkPreCondition();

        shared->sessionData.removeCalibData();
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void CalibrationController::e_CameraStart(wxEvtHandler *parent) {
    try {

        checkPreCondition();

        startCaptureHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void CalibrationController::e_CameraEnd(wxEvtHandler *parent) {
    try {

        checkPreCondition();

        endCaptureHandler();
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void CalibrationController::e_ChangeToCapturePanel(wxEvtHandler *parent) {
    try {
        checkPreCondition();
        ChangePanelData data(this->panelID, PanelID::PANEL_CAPTURE);
        ChangePanelEvent::Submit(parent, data);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void CalibrationController::e_ChangeToManualPanel(wxEvtHandler *parent) {
    try {
        checkPreCondition();
        ChangePanelData data(this->panelID, PanelID::PANEL_MANUAL_CALIBRATION);
        ChangePanelEvent::Submit(parent, data);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void CalibrationController::e_ChangeToColorPanel(wxEvtHandler *parent) {
    try {

        checkPreCondition();

        ChangePanelData data(this->panelID, PanelID::PANEL_COLOR_CALIBRATION);
        ChangePanelEvent::Submit(parent, data);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void CalibrationController::e_CalibrationStart(wxEvtHandler *parent) {
    try {

        checkPreCondition();

        startCalibrationHandler(parent);

    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void CalibrationController::e_CalibrationSave(wxEvtHandler *parent) {
    try {

        checkPreCondition();

        saveCalibrationHandler(parent);

    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void CalibrationController::e_CalibrationEnd(wxEvtHandler *parent) {
    try {

        checkPreCondition();

        endCalibrationHandler();

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

void CalibrationController::startCalibrationHandler(wxEvtHandler *parent) {
    auto tc = shared->getThreadController();

    if (!shared->isCameraAvailable()) {
        throw std::runtime_error("Camera is not available");
    }

    if (!tc->isThreadsWithCameraNullptr()) {
        throw std::runtime_error("Thread with camera is already running");
    }

    if (!tc->isThreadNullptr(THREAD_CALIBRATION)) {
        throw std::runtime_error("CalibrationThread is already running");
    }

    auto camera = shared->getCamera();

    HSVFilter filter;
    BFS bfs;
    RansacLine ransacLine(500, 50, 6);

    tc->startCalibrationHandler(parent, camera, filter, bfs, ransacLine,
                                panelID);
}

void CalibrationController::saveCalibrationHandler(wxEvtHandler *parent) {
    auto tc = shared->getThreadController();

    if (tc->isThreadNullptr(THREAD_CALIBRATION)) {
        throw std::runtime_error("CalibrationThread is not running");
    }

    if (!tc->isThreadOwner(THREAD_CALIBRATION, panelID)) {
        throw std::runtime_error(
            "CalibrationThread is not owned by this panel");
    }

    auto calibrationThread = tc->getCalibrationThread();
    calibrationThread->Pause();

    auto calibData = calibrationThread->getCalibData();

    shared->sessionData.calibData = calibData;

    auto camera = calibrationThread->getCamera();
    shared->setCamera(camera);

    tc->endCalibrationHandler();
}

void CalibrationController::endCalibrationHandler() {
    auto tc = shared->getThreadController();

    if (tc->isThreadNullptr(THREAD_CALIBRATION)) {
        throw std::runtime_error("CalibrationThread is not running");
    }

    if (!tc->isThreadOwner(THREAD_CALIBRATION, panelID)) {
        throw std::runtime_error(
            "CalibrationThread is not owned by this panel");
    }

    auto calibrationThread = tc->getCalibrationThread();
    calibrationThread->Pause();

    auto camera = calibrationThread->getCamera();
    shared->setCamera(camera);

    tc->endCalibrationHandler();
}

void CalibrationController::startCaptureHandler(wxEvtHandler *parent) {
    auto tc = shared->getThreadController();

    if (!shared->isCameraAvailable()) {
        throw std::runtime_error("Error acquiring camera");
    }

    if (!tc->isThreadNullptr(THREAD_CALIBRATION_PREVIEW)) {
        throw std::runtime_error("calibrationPreview is already running");
    }

    auto camera = shared->getCamera();
    auto data = shared->getSessionData();
    tc->startCalibPreviewHandler(parent, camera, data, panelID);
}

void CalibrationController::endCaptureHandler() {
    auto tc = shared->getThreadController();

    if (tc->isThreadNullptr(THREAD_CALIBRATION_PREVIEW)) {
        throw std::runtime_error("calibrationPreview is not running");
    }

    if (!tc->isThreadOwner(THREAD_CALIBRATION_PREVIEW, panelID)) {
        throw std::runtime_error(
            "calibrationPreview is not owned by this panel");
    }

    auto calibPreviewThread = tc->getCalibPreviewThread();
    calibPreviewThread->Pause();

    auto camera = calibPreviewThread->getCamera();
    shared->setCamera(camera);

    tc->endCalibPreviewHandler();
}

void CalibrationController::setPointHandler(wxEvtHandler *parent,
                                            cv::Point point) {
    auto tc = shared->getThreadController();

    if (tc->isThreadNullptr(THREAD_CALIBRATION)) {
        throw std::runtime_error("calibrationThread is not running");
    }

    if (!tc->isThreadOwner(THREAD_CALIBRATION, panelID)) {
        throw std::runtime_error(
            "calibrationThread is not owned by this panel");
    }

    auto calibrationThread = tc->getCalibrationThread();
    calibrationThread->setPoint(point);
}

void CalibrationController::checkPreCondition() {
    if (panelID != shared->sessionData.currentPanelID) {
        throw std::runtime_error(
            "CalibrationController::endPoint() - PanelID mismatch");
    }
}