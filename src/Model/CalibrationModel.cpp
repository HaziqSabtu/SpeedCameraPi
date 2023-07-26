#include "Model/CalibrationModel.hpp"
#include "Algorithm/hsv_filter/BFS.hpp"
#include "Algorithm/hsv_filter/HSVFilter.hpp"
#include "Algorithm/ransac_line/RansacLine.hpp"
#include "Event/Event_UpdateState.hpp"

#include "Thread/ThreadPool.hpp"
#include "Thread/Thread_Calibration.hpp"
#include "Thread/Thread_Capture.hpp"
#include "Thread/Thread_ID.hpp"
#include "Thread/Thread_LoadFile.hpp"
#include "Utils/Camera/CameraBase.hpp"
#include "Utils/Config/AppConfig.hpp"
#include "Utils/Config/ConfigStruct.hpp"
#include "Utils/DataStruct.hpp"
#include <Model/CalibrationModel.hpp>
#include <memory>
#include <vector>
#include <wx/event.h>
#include <wx/object.h>

CalibrationModel::CalibrationModel(std::shared_ptr<SharedModel> sharedModel)
    : shared(sharedModel) {}

CalibrationModel::~CalibrationModel() {}

void CalibrationModel::e_UpdateState(wxEvtHandler *parent) {
    try {
        AppState state(shared);
        UpdateStateEvent::Submit(parent, state);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void CalibrationModel::checkPreCondition() {
    if (panelID != shared->sessionData.currentPanelID) {
        throw std::runtime_error(
            "CalibrationModel::endPoint() - PanelID mismatch");
    }
}

void CalibrationModel::e_CameraStart(wxEvtHandler *parent) {
    try {

        checkPreCondition();

        startCaptureHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void CalibrationModel::e_CameraEnd(wxEvtHandler *parent) {
    try {

        checkPreCondition();

        endCaptureHandler();
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void CalibrationModel::e_ChangeToCapturePanel(wxEvtHandler *parent) {
    try {
        checkPreCondition();
        ChangePanelData data(this->panelID, PanelID::PANEL_CAPTURE);
        ChangePanelEvent::Submit(parent, data);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void CalibrationModel::e_ChangeToManualPanel(wxEvtHandler *parent) {
    try {
        checkPreCondition();
        ChangePanelData data(this->panelID, PanelID::PANEL_MANUAL_CALIBRATION);
        ChangePanelEvent::Submit(parent, data);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void CalibrationModel::e_ChangeToColorPanel(wxEvtHandler *parent) {
    try {

        checkPreCondition();

        ChangePanelData data(this->panelID, PanelID::PANEL_COLOR_CALIBRATION);
        ChangePanelEvent::Submit(parent, data);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void CalibrationModel::e_CalibrationStart(wxEvtHandler *parent) {
    try {

        checkPreCondition();

        startCalibrationHandler(parent);

    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void CalibrationModel::e_CalibrationEnd(wxEvtHandler *parent) {
    try {

        checkPreCondition();

        endCalibrationHandler();

    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void CalibrationModel::e_SetPoint(wxEvtHandler *parent, wxPoint point) {
    try {

        checkPreCondition();

        setPointHandler(parent, Utils::wxPointToCvPoint(point));

    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void CalibrationModel::startCalibrationHandler(wxEvtHandler *parent) {
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
    RansacLine ransacLine(500, 50, 8);

    tc->startCalibrationHandler(parent, camera, filter, bfs, ransacLine,
                                panelID);
}

void CalibrationModel::endCalibrationHandler() {
    auto tc = shared->getThreadController();

    if (tc->isThreadNullptr(THREAD_CALIBRATION)) {
        throw std::runtime_error("CalibrationThread is not running");
    }

    if (!tc->isThreadOwner(THREAD_CALIBRATION, panelID)) {
        throw std::runtime_error(
            "CalibrationThread is not owned by this panel");
    }

    auto loadCaptureThread = tc->getLoadCaptureThread();
    loadCaptureThread->Pause();

    auto camera = loadCaptureThread->getCamera();
    shared->setCamera(camera);

    tc->endCalibrationHandler();
}

void CalibrationModel::startCaptureHandler(wxEvtHandler *parent) {
    auto tc = shared->getThreadController();

    if (!shared->isCameraAvailable()) {
        throw std::runtime_error("Error acquiring camera");
    }

    if (!tc->isThreadNullptr(THREAD_CAPTURE)) {
        throw std::runtime_error("captureThread is already running");
    }

    auto camera = shared->getCamera();
    tc->startCaptureHandler(parent, camera, panelID);
}

void CalibrationModel::endCaptureHandler() {
    auto tc = shared->getThreadController();

    if (tc->isThreadNullptr(THREAD_CAPTURE)) {
        throw std::runtime_error("captureThread is not running");
    }

    if (!tc->isThreadOwner(THREAD_CAPTURE, panelID)) {
        throw std::runtime_error("captureThread is not owned by this panel");
    }

    auto captureThread = tc->getCaptureThread();
    captureThread->Pause();

    auto camera = captureThread->getCamera();
    shared->setCamera(camera);

    tc->endCaptureHandler();
}

void CalibrationModel::setPointHandler(wxEvtHandler *parent, cv::Point point) {
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