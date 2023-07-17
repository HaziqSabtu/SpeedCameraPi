#include "Model/CaptureModel.hpp"
#include "Event/Event_ChangePanel.hpp"
#include "Thread/ThreadPool.hpp"
#include "Thread/Thread_Capture.hpp"
#include "Thread/Thread_LoadFile.hpp"
#include "Utils/Camera/CameraBase.hpp"
#include "Utils/Config/AppConfig.hpp"
#include "Utils/Config/ConfigStruct.hpp"
#include "Utils/DataStruct.hpp"
#include <Model/CaptureModel.hpp>
#include <vector>
#include <wx/event.h>

CaptureModel::CaptureModel(std::shared_ptr<SharedModel> sharedModel)
    : shared(sharedModel) {
    initThreads();
}

CaptureModel::~CaptureModel() {
    try {
        deleteThreads();
    } catch (std::exception &e) {
        std::cout << e.what() << std::endl;
    }
}

void CaptureModel::initThreads() {
    captureThread = nullptr;
    loadFileThread = nullptr;
    loadCaptureThread = nullptr;
}

void CaptureModel::deleteThreads() {
    captureThread = stopAndDeleteThread(captureThread);
    loadFileThread = stopAndDeleteThread(loadFileThread);
    loadCaptureThread = stopAndDeleteThread(loadCaptureThread);
}

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
        ErrorEvent errorEvent(c_ERROR_EVENT, wxID_ANY);
        errorEvent.SetErrorData(e.what());
        wxPostEvent(parent, errorEvent);
    }
}

void CaptureModel::startCaptureHandler(wxEvtHandler *parent) {
    if (shared->getCamera() == nullptr) {
        throw std::runtime_error("Camera is not initialized");
    }
    if (captureThread != nullptr) {
        throw std::runtime_error("captureThread is already running");
    }

    captureThread = initCaptureThread(parent, shared->getCamera());
    captureThread->Run();
}

void CaptureModel::endCaptureHandler() {
    captureThread = stopAndDeleteThread(captureThread);
}

void CaptureModel::startLoadFileHandler(wxEvtHandler *parent,
                                        std::string path) {

    if (captureThread != nullptr) {
        endCaptureHandler();
    }

    if (loadFileThread != nullptr) {
        throw std::runtime_error("loadFileThread is already running");
    }

    if (!shared->sessionData.isImageDataEmpty()) {
        shared->sessionData.clearImageData();
    }

    AppConfig config;
    LoadConfig loadConfig = config.GetLoadConfig();
    loadFileThread = initLoadFileThread(parent, loadConfig.maxFrame, path);
    loadFileThread->Run();
}

void CaptureModel::endLoadFileHandler() {
    loadFileThread = stopAndDeleteThread(loadFileThread);
}

void CaptureModel::startLoadCaptureHandler(wxEvtHandler *parent) {

    if (shared->getCamera() == nullptr) {
        throw std::runtime_error("Camera is not initialized");
    }

    if (captureThread != nullptr) {
        endCaptureHandler();
    }

    if (loadCaptureThread != nullptr) {
        throw std::runtime_error("LoadCaptureThread is already running");
    }

    if (!shared->sessionData.isImageDataEmpty()) {
        std::cerr << "ImageData is not empty" << std::endl;
        shared->sessionData.clearImageData();
    }

    AppConfig config;
    CaptureConfig captureConfig = config.GetCaptureConfig();
    loadCaptureThread = initLoadCaptureThread(parent, shared->getCamera(),
                                              shared->sessionData.imageData,
                                              captureConfig.maxFrame);
    loadCaptureThread->Run();
}

void CaptureModel::endLoadCaptureHandler() {
    loadCaptureThread = stopAndDeleteThread(loadCaptureThread);
}

template <typename T>
T *CaptureModel::stopAndDeleteThread(T *threadPtr) {
    if (threadPtr == nullptr) {
        return nullptr;
    }

    threadPtr->Delete();
    delete threadPtr;
    threadPtr = nullptr;

    return threadPtr;
}

void CaptureModel::switchPanelHandler(wxEvtHandler *parent) {
    if (!isRequirementFulfilled()) {
        throw std::runtime_error("Requirement is not fulfilled");
    }

    ChangePanelData data(this->panelID, this->nextPanelID);

    ChangePanelEvent changePanelEvent(c_CHANGE_PANEL_EVENT, CHANGE_OK);
    changePanelEvent.SetPanelData(data);
    wxPostEvent(parent, changePanelEvent);
}

// TODO: REmove this temporary
void CaptureModel::switchToCalibHandler(wxEvtHandler *parent) {

    ChangePanelData data(this->panelID, PanelID::PANEL_CALIBRATION);

    ChangePanelEvent changePanelEvent(c_CHANGE_PANEL_EVENT, CHANGE_OK);
    changePanelEvent.SetPanelData(data);
    wxPostEvent(parent, changePanelEvent);
}

bool CaptureModel::isRequirementFulfilled() {
    if (captureThread != nullptr) {
        endCaptureHandler();
    }

    if (loadFileThread != nullptr) {
        endLoadFileHandler();
    }

    if (loadCaptureThread != nullptr) {
        endLoadCaptureHandler();
    }

    if (shared->sessionData.isImageDataEmpty()) {
        throw std::runtime_error("ImageData is empty");
    }
    return true;
}

wxThread *CaptureModel::initCaptureThread(wxEvtHandler *parent,
                                          std::shared_ptr<CameraBase> camera) {
    return new CaptureThread(parent, camera);
}

wxThread *CaptureModel::initLoadFileThread(wxEvtHandler *parent, int maxFrame,
                                           std::string path) {
    return new LoadFileThread(parent, shared->getThreadPool(),
                              shared->sessionData.imageData, path, maxFrame);
}

wxThread *CaptureModel::initLoadCaptureThread(
    wxEvtHandler *parent, std::shared_ptr<CameraBase> camera,
    std::shared_ptr<std::vector<ImageData>> imgData, const int maxFrame) {
    return new LoadCaptureThread(parent, camera, imgData, maxFrame);
}