#include "Model/CaptureModel.hpp"
#include "Thread/Thread_Capture.hpp"
#include <Model/CaptureModel.hpp>

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
                "CaptureModel::endPoint() - Invalid PanelID");
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

        throw std::runtime_error("CaptureModel::endPoint() - Invalid Endpoint");

    } catch (std::exception &e) {
        ErrorEvent errorEvent(c_ERROR_EVENT, wxID_ANY);
        errorEvent.SetErrorData(e.what());
        wxPostEvent(parent, errorEvent);
    }
}

void CaptureModel::startCaptureHandler(wxEvtHandler *parent) {
    if (captureThread != nullptr) {
        throw std::runtime_error("captureThread is already running");
    }
    captureThread = new CaptureThread(parent, shared->camera);
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
    loadFileThread = new LoadFileThread(parent, shared->threadPool,
                                        shared->sessionData.imageData, path,
                                        loadConfig.maxFrame);
    loadFileThread->Run();
}

void CaptureModel::endLoadFileHandler() {
    loadFileThread = stopAndDeleteThread(loadFileThread);
}

void CaptureModel::startLoadCaptureHandler(wxEvtHandler *parent) {

    if (captureThread != nullptr) {
        endCaptureHandler();
    }

    if (loadCaptureThread != nullptr) {
        throw std::runtime_error("LoadCaptureThread is already running");
    }

    if (!shared->sessionData.isImageDataEmpty()) {
        shared->sessionData.clearImageData();
    }

    AppConfig config;
    CaptureConfig captureConfig = config.GetCaptureConfig();
    loadCaptureThread = new LoadCaptureThread(
        parent, shared->camera, shared->sessionData.imageData,
        captureConfig.maxFrame, false, false);
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

    wxCommandEvent changePanelEvent(c_CHANGE_PANEL_EVENT, CHANGE_OK);
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