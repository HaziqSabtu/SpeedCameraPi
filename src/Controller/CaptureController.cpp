#include "Event/Event_ChangePanel.hpp"
#include "Event/Event_UpdatePreview.hpp"
#include "Event/Event_UpdateState.hpp"
#include "Model/AppState.hpp"
#include "Thread/ThreadPool.hpp"
#include "Thread/Thread_Capture.hpp"
#include "Thread/Thread_ID.hpp"
#include "Thread/Thread_LoadFile.hpp"
#include "UI/Dialog/ResetDataDialog.hpp"
#include "UI/Dialog/SaveDataDialog.hpp"
#include "UI/Layout/StatusPanel.hpp"
#include "Utils/Camera/CameraBase.hpp"
#include "Utils/Config/AppConfig.hpp"
#include "Utils/Config/ConfigStruct.hpp"
#include "Utils/FileReader/fileWR.hpp"
#include "Utils/wxUtils.hpp"
#include <Controller/CaptureController.hpp>
#include <Event/Event_UpdateStatus.hpp>
#include <memory>
#include <vector>
#include <wx/event.h>

CaptureController::CaptureController(ModelPtr sharedModel)
    : shared(sharedModel) {}

CaptureController::~CaptureController() {}

void CaptureController::e_ChangeToCalibPanel(wxEvtHandler *parent) {
    try {
        checkPreCondition();
        ChangePanelData data(this->panelID, PanelID::PANEL_CALIBRATION);
        ChangePanelEvent::Submit(parent, data);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void CaptureController::e_ChangeToRoiPanel(wxEvtHandler *parent) {
    try {
        checkPreCondition();
        ChangePanelData data(this->panelID, PanelID::PANEL_ROI);
        ChangePanelEvent::Submit(parent, data);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

// TODO: Addhandler
void CaptureController::e_ChangeToResultPanel(wxEvtHandler *parent) {
    try {
        checkPreCondition();
        ChangePanelData data(this->panelID, PanelID::PANEL_RESULT);
        ChangePanelEvent::Submit(parent, data);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void CaptureController::e_SaveSessionData(wxEvtHandler *parent) {
    try {
        checkPreCondition();
        saveSessionDataHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void CaptureController::e_ResetSessionData(wxEvtHandler *parent) {
    try {
        checkPreCondition();
        resetSessionDataHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void CaptureController::e_UpdateState(wxEvtHandler *parent) {
    try {
        AppState state(shared);
        UpdateStateEvent::Submit(parent, state);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void CaptureController::e_ClearImageData(wxEvtHandler *parent) {
    try {

        checkPreCondition();

        clearImageDataHandler(parent);

    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void CaptureController::e_RemoveCalibration(wxEvtHandler *parent) {
    try {

        checkPreCondition();

        removeCalibrationHandler(parent);

    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void CaptureController::e_RemoveRoi(wxEvtHandler *parent) {
    try {

        checkPreCondition();

        removeRoiHandler(parent);

    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void CaptureController::e_ReplayStart(wxEvtHandler *parent) {
    try {

        checkPreCondition();

        auto tc = shared->getThreadController();

        if (!tc->isThreadsWithCameraNullptr()) {
            throw std::runtime_error("Thread with camera is already running");
        }

        if (!tc->isThreadNullptr(THREAD_REPLAY)) {
            throw std::runtime_error("ReplayThread is already running");
        }

        if (shared->sessionData.isCaptureDataEmpty()) {
            throw std::runtime_error("ImageData is Empty");
        }

        auto data = shared->getSessionData();

        tc->startReplayHandler(parent, data, panelID);

    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void CaptureController::e_ReplayEnd(wxEvtHandler *parent) {
    try {

        checkPreCondition();

        auto tc = shared->getThreadController();

        if (tc->isThreadNullptr(THREAD_REPLAY)) {
            throw std::runtime_error("replayThread is not running");
        }

        if (!tc->isThreadOwner(THREAD_REPLAY, panelID)) {
            throw std::runtime_error("replayThread is not owned by this panel");
        }

        tc->endReplayHandler();

    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void CaptureController::e_CameraStart(wxEvtHandler *parent) {
    try {

        checkPreCondition();

        startCaptureHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void CaptureController::e_CameraEnd(wxEvtHandler *parent) {
    try {

        checkPreCondition();

        endCaptureHandler();
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void CaptureController::e_LoadFileStart(wxEvtHandler *parent,
                                        std::string path) {
    try {

        checkPreCondition();

        startLoadFileHandler(parent, path);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void CaptureController::e_LoadFileEnd(wxEvtHandler *parent) {
    try {

        checkPreCondition();

        endLoadFileHandler();
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void CaptureController::e_LoadCaptureStart(wxEvtHandler *parent) {
    try {

        checkPreCondition();

        startLoadCaptureHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void CaptureController::e_LoadCaptureEnd(wxEvtHandler *parent) {
    try {

        checkPreCondition();

        endLoadCaptureHandler();

        UpdateStatusEvent::Submit(parent, StatusCollection::STATUS_CAPTURE_END);

    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void CaptureController::startCaptureHandler(wxEvtHandler *parent) {
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

void CaptureController::endCaptureHandler() {
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

void CaptureController::startLoadFileHandler(wxEvtHandler *parent,
                                             std::string path) {

    auto tc = shared->getThreadController();

    if (!tc->isThreadsWithCameraNullptr()) {
        throw std::runtime_error("Thread with camera is already running");
    }

    if (!tc->isThreadNullptr(THREAD_LOAD_FILE)) {
        throw std::runtime_error("LoadFileThread is already running");
    }

    if (!shared->sessionData.isCaptureDataEmpty()) {
        throw std::runtime_error("ImageData is not empty");
    }

    AppConfig config;
    auto c = config.GetLoadConfig();

    auto data = shared->getSessionData();

    tc->startLoadFileHandler(parent, data, c.maxFrame, path, panelID);
}

void CaptureController::endLoadFileHandler() {
    auto tc = shared->getThreadController();

    if (tc->isThreadNullptr(THREAD_LOAD_FILE)) {
        throw std::runtime_error("loadFileThread is not running");
    }

    if (!tc->isThreadOwner(THREAD_LOAD_FILE, panelID)) {
        throw std::runtime_error("loadFileThread is not owned by this panel");
    }

    auto loadCaptureThread = tc->getLoadFileThread();

    tc->endLoadFileHandler();
}

void CaptureController::startLoadCaptureHandler(wxEvtHandler *parent) {
    auto tc = shared->getThreadController();

    if (!shared->isCameraAvailable()) {
        throw std::runtime_error("Error acquiring camera");
    }

    if (!tc->isThreadsWithCameraNullptr()) {
        throw std::runtime_error("Thread with camera is already running");
    }

    if (!tc->isThreadNullptr(THREAD_LOAD_CAPTURE)) {
        throw std::runtime_error("LoadCaptureThread is already running");
    }

    if (!shared->sessionData.isCaptureDataEmpty()) {
        throw std::runtime_error("ImageData is not empty");
    }

    AppConfig config;
    auto captureConfig = config.GetCaptureConfig();
    int maxFrame = captureConfig.maxFrame;

    auto camera = shared->getCamera();

    auto data = shared->getSessionData();

    tc->startLoadCaptureHandler(parent, camera, data, maxFrame, panelID);
}

void CaptureController::endLoadCaptureHandler() {
    auto tc = shared->getThreadController();

    if (tc->isThreadNullptr(THREAD_LOAD_CAPTURE)) {
        throw std::runtime_error("loadCaptureThread is not running");
    }

    if (!tc->isThreadOwner(THREAD_LOAD_CAPTURE, panelID)) {
        throw std::runtime_error(
            "loadCaptureThread is not owned by this panel");
    }

    auto loadCaptureThread = tc->getLoadCaptureThread();

    auto camera = loadCaptureThread->getCamera();
    shared->setCamera(camera);

    tc->endLoadCaptureHandler();
}

void CaptureController::checkPreCondition() {
    auto data = shared->getSessionData();
    if (panelID != data->getPanelID()) {
        throw std::runtime_error(
            "CaptureController::endPoint() - PanelID mismatch");
    }
}

void CaptureController::throwIfAnyThreadIsRunning() {
    auto tc = shared->getThreadController();

    if (!tc->isThreadNullptr(THREAD_CAPTURE)) {
        throw std::runtime_error("captureThread is already running");
    }

    if (!tc->isThreadNullptr(THREAD_LOAD_FILE)) {
        throw std::runtime_error("loadFileThread is already running");
    }

    if (!tc->isThreadNullptr(THREAD_LOAD_CAPTURE)) {
        throw std::runtime_error("loadCaptureThread is already running");
    }

    if (!tc->isThreadNullptr(THREAD_REPLAY)) {
        throw std::runtime_error("replayThread is already running");
    }
}

void CaptureController::clearImageDataHandler(wxEvtHandler *parent) {
    auto tc = shared->getThreadController();

    if (tc->isCapturePanelThreadRunning()) {
        throw std::runtime_error("Thread of Capture Panel is running");
    }

    if (shared->sessionData.isCaptureDataEmpty()) {
        throw std::runtime_error("ImageData is empty");
    }

    shared->sessionData.removeCaptureData();

    shared->sessionData.clearTrackingData();

    shared->sessionData.clearResultData();

    UpdateStatusEvent::Submit(parent, StatusCollection::STATUS_REMOVE_DATA);

    UpdatePreviewEvent::Submit(parent, CLEAR_PREVIEW);
}

void CaptureController::removeCalibrationHandler(wxEvtHandler *parent) {
    auto tc = shared->getThreadController();

    if (tc->isCapturePanelThreadRunning()) {
        throw std::runtime_error("Thread of Capture Panel is running");
    }

    if (shared->sessionData.isCalibrationDataEmpty()) {
        throw std::runtime_error("CalibrationData is empty");
    }

    shared->sessionData.removeCalibrationData();

    // TODO: Add this to StatusCollection
    wxString msg = "Calibration data is removed";
    UpdateStatusEvent::Submit(parent, msg);
}

void CaptureController::removeRoiHandler(wxEvtHandler *parent) {
    auto tc = shared->getThreadController();

    if (tc->isCapturePanelThreadRunning()) {
        throw std::runtime_error("Thread of Capture Panel is running");
    }

    if (shared->sessionData.isTrackingDataEmpty()) {
        throw std::runtime_error("RoiData is empty");
    }

    shared->sessionData.clearTrackingData();

    wxString msg = "Roi data is removed";
    UpdateStatusEvent::Submit(parent, msg);
}

void CaptureController::saveSessionDataHandler(wxEvtHandler *parent) {
    throwIfAnyThreadIsRunning();

    if (shared->sessionData.isCaptureDataEmpty()) {
        throw std::runtime_error("Capture Data is empty");
    }

    auto id = shared->getSessionData()->getID();
    auto filename = Utils::idToFileName(id);

    auto dialog = new SaveDataDialog(nullptr, filename);
    if (dialog->ShowModal() == wxID_NO) {
        // TODO: Add this to StatusCollection
        wxString msg = "Save Cancelled";
        UpdateStatusEvent::Submit(parent, msg);
        return;
    }

    auto data = shared->getSessionData();

    Utils::FileReadWrite().WriteFile(data);

    // TODO: Add this to StatusCollection
    wxString msg = "Data is saved";
    UpdateStatusEvent::Submit(parent, msg);
}

void CaptureController::resetSessionDataHandler(wxEvtHandler *parent) {
    throwIfAnyThreadIsRunning();

    auto dialog = new ResetDataDialog(nullptr);
    if (dialog->ShowModal() == wxID_NO) {
        wxString msg = "Session Reset Cancelled";
        UpdateStatusEvent::Submit(parent, msg);

        return;
    }

    shared->resetSessionData();

    wxString msg = "Session Reset Complete";
    UpdateStatusEvent::Submit(parent, msg);
}