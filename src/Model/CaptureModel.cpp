#include "Model/CaptureModel.hpp"
#include "Event/Event_ChangePanel.hpp"
#include "Event/Event_UpdateState.hpp"
#include "Model/AppState.hpp"
#include "Thread/ThreadPool.hpp"
#include "Thread/Thread_Capture.hpp"
#include "Thread/Thread_ID.hpp"
#include "Thread/Thread_LoadFile.hpp"
#include "Utils/Camera/CameraBase.hpp"
#include "Utils/Config/AppConfig.hpp"
#include "Utils/Config/ConfigStruct.hpp"
#include "Utils/DataStruct.hpp"
#include <Model/CaptureModel.hpp>
#include <memory>
#include <vector>
#include <wx/event.h>

CaptureModel::CaptureModel(std::shared_ptr<SharedModel> sharedModel)
    : shared(sharedModel) {}

CaptureModel::~CaptureModel() {}

void CaptureModel::endPoint(wxEvtHandler *parent, ModelEnum::ModelIDs id) {
    endPoint(parent, id, "");
}

void CaptureModel::endPoint(wxEvtHandler *parent, ModelEnum::ModelIDs id,
                            std::string path) {
    try {
        if (panelID != shared->sessionData.currentPanelID) {
            throw std::runtime_error(
                "CaptureModel::endPoint() - PanelID mismatch");
        }

        if (id == ModelEnum::MODEL_START_CAPTURE) {
            startCaptureHandler(parent);
            return;
        }

        if (id == ModelEnum::MODEL_END_CAPTURE) {
            endCaptureHandler();
            return;
        }

        if (id == ModelEnum::MODEL_START_LOADFILE) {
            startLoadFileHandler(parent, path);
            return;
        }

        if (id == ModelEnum::MODEL_END_LOADFILE) {
            endLoadFileHandler();
            return;
        }

        if (id == ModelEnum::MODEL_START_LOADCAPTURE) {
            startLoadCaptureHandler(parent);
            return;
        }

        if (id == ModelEnum::MODEL_END_LOADCAPTURE) {
            endLoadCaptureHandler();
            return;
        }

        if (id == ModelEnum::MODEL_SWITCH_PANEL) {
            switchPanelHandler(parent);
            return;
        }

        if (id == ModelEnum::MODEL_SWITCH_TO_CALIB) {
            switchToCalibHandler(parent);
            return;
        }

        throw std::runtime_error("CaptureModel::endPoint() - Invalid Endpoint");

    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void CaptureModel::startCaptureHandler(wxEvtHandler *parent) {
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

void CaptureModel::endCaptureHandler() {
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

void CaptureModel::startLoadFileHandler(wxEvtHandler *parent,
                                        std::string path) {

    auto tc = shared->getThreadController();

    if (!tc->isThreadsWithCameraNullptr()) {
        throw std::runtime_error("Thread with camera is already running");
    }

    if (!tc->isThreadNullptr(THREAD_LOAD_FILE)) {
        throw std::runtime_error("LoadFileThread is already running");
    }

    if (!shared->sessionData.isImageDataEmpty()) {
        throw std::runtime_error("ImageData is not empty");
    }

    AppConfig config;
    auto c = config.GetLoadConfig();

    tc->startLoadFileHandler(parent, c.maxFrame, path, panelID);
}

void CaptureModel::endLoadFileHandler() {
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

void CaptureModel::startLoadCaptureHandler(wxEvtHandler *parent) {
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

    if (!shared->sessionData.isImageDataEmpty()) {
        throw std::runtime_error("ImageData is not empty");
    }

    AppConfig config;
    auto captureConfig = config.GetCaptureConfig();

    auto camera = shared->getCamera();

    tc->startLoadCaptureHandler(parent, camera, shared->sessionData.imageData,
                                captureConfig.maxFrame, panelID);
}

void CaptureModel::endLoadCaptureHandler() {
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

void CaptureModel::switchPanelHandler(wxEvtHandler *parent) {
    if (!isRequirementFulfilled()) {
        throw std::runtime_error("Requirement is not fulfilled");
    }

    ChangePanelData data(this->panelID, this->nextPanelID);
    ChangePanelEvent::Submit(parent, data);
}

// TODO: Remove this temporary
void CaptureModel::switchToCalibHandler(wxEvtHandler *parent) {
    ChangePanelData data(this->panelID, PanelID::PANEL_CALIBRATION);
    ChangePanelEvent::Submit(parent, data);
}

bool CaptureModel::isRequirementFulfilled() {
    // if (captureThread != nullptr) {
    //     endCaptureHandler();
    // }

    // if (loadFileThread != nullptr) {
    //     endLoadFileHandler();
    // }

    // if (loadCaptureThread != nullptr) {
    //     endLoadCaptureHandler();
    // }

    if (shared->sessionData.isImageDataEmpty()) {
        throw std::runtime_error("ImageData is empty");
    }
    return true;
}

void CaptureModel::e_UpdateState(wxEvtHandler *parent) {
    AppState state = shared->getAppState();
    UpdateStateEvent::Submit(parent, state);
}