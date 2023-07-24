#include "Model/SessionData.hpp"
#include <Model/Model.hpp>
#include <wx/event.h>

Model::Model(wxWindow *parent, wxWindowID id) {
    AppConfig *config = new AppConfig();

    CameraConfig cameraConfig = config->GetCameraConfig();

    camera = std::make_shared<LibCam>();
    camera->setHeight(cameraConfig.Camera_Height);
    camera->setWidth(cameraConfig.Camera_Width);
    camera->setFPS(cameraConfig.Camera_FPS);

    if (!camera->start()) {
        ErrorEvent errorEvent(c_ERROR_EVENT, wxID_ANY);
        errorEvent.SetErrorData(" Camera not found! ");
        wxPostEvent(parent, errorEvent);
    }

    threadPool = std::make_shared<ThreadPool>();
    threadPool->setNumThreads(config->GetPanelConfig().Thread_Pool_Size);

    initThreads();

    delete config;
    config = nullptr;
}

Model::~Model() {
    try {
        camera->stop();
        deleteThreads();
    } catch (std::exception &e) {
        std::cout << e.what() << std::endl;
    }
}

void Model::initThreads() {
    captureThread = nullptr;
    loadFileThread = nullptr;
    loadCaptureThread = nullptr;

    processThread = nullptr;
}

void Model::deleteThreads() {
    captureThread = stopAndDeleteThread(captureThread);
    loadFileThread = stopAndDeleteThread(loadFileThread);
    loadCaptureThread = stopAndDeleteThread(loadCaptureThread);
    processThread = stopAndDeleteThread(processThread);
}

void Model::endPoint(wxEvtHandler *parent, ModelEnum::ModelIDs id,
                     PanelID panelID) {
    try {
        switch (panelID) {
            case PANEL_CAPTURE: requestChangePanel(parent, panelID); break;
            default: break;
        }
    } catch (std::exception &e) {
        ErrorEvent errorEvent(c_ERROR_EVENT, wxID_ANY);
        errorEvent.SetErrorData(e.what());
        wxPostEvent(parent, errorEvent);
    }
}

void Model::endPoint(wxEvtHandler *parent, ModelEnum::ModelIDs id) {
    endPoint(parent, id, "");
}

void Model::endPoint(wxEvtHandler *parent, ModelEnum::ModelIDs id,
                     std::string path) {
    try {

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
            endLoadFileHandler(parent);
            return;
        }

        if (id == ModelEnum::MODEL_START_LOADCAPTURE) {
            startLoadCaptureHandler(parent);
            return;
        }

        if (id == ModelEnum::MODEL_END_LOADCAPTURE) {
            endLoadCaptureHandler(parent);
            return;
        }

        if (id == ModelEnum::MODEL_START_PROCESS) {
            startProcessHandler(parent);
            return;
        }

        throw std::runtime_error("Model::endPoint() - Invalid ModelID");

    } catch (std::exception &e) {
        ErrorEvent errorEvent(c_ERROR_EVENT, wxID_ANY);
        errorEvent.SetErrorData(e.what());
        wxPostEvent(parent, errorEvent);
    }
}

void Model::endPoint(wxEvtHandler *parent, PanelID panelID, wxRect rect) {
    try {
        if (panelID == PANEL_ROI) {
            int x = rect.GetX();
            int y = rect.GetY();
            int width = rect.GetWidth();
            int height = rect.GetHeight();
            sessionData.updateRoiData(x, y, width, height);

            std::cout << "Update Success" << std::endl;
            sessionData.roiData.Info();
        }
    } catch (std::exception &e) {
        ErrorEvent errorEvent(c_ERROR_EVENT, wxID_ANY);
        errorEvent.SetErrorData(e.what());
        wxPostEvent(parent, errorEvent);
    }
}

void Model::startCaptureHandler(wxEvtHandler *parent) {
    if (captureThread != nullptr) {
        throw std::runtime_error("captureThread is already running");
    }

    // captureThread = new CaptureThread(parent, camera);
    captureThread->Run();
}

void Model::endCaptureHandler() {
    captureThread = stopAndDeleteThread(captureThread);
}

void Model::startLoadFileHandler(wxEvtHandler *parent, std::string path) {

    if (captureThread != nullptr) {
        endCaptureHandler();
    }

    if (loadFileThread != nullptr) {
        throw std::runtime_error("loadFileThread is already running");
    }

    if (!sessionData.isImageDataEmpty()) {
        sessionData.clearImageData();
    }

    AppConfig *config = new AppConfig();
    LoadConfig loadConfig = config->GetLoadConfig();
    loadFileThread = new LoadFileThread(
        parent, threadPool, sessionData.imageData, path, loadConfig.maxFrame);
    loadFileThread->Run();
    delete config;
    config = nullptr;
}

void Model::endLoadFileHandler(wxEvtHandler *parent) {
    loadFileThread = stopAndDeleteThread(loadFileThread);
}

void Model::startLoadCaptureHandler(wxEvtHandler *parent) {

    if (captureThread != nullptr) {
        endCaptureHandler();
    }

    if (loadCaptureThread != nullptr) {
        throw std::runtime_error("LoadCaptureThread is already running");
    }

    if (!sessionData.isImageDataEmpty()) {
        sessionData.clearImageData();
    }

    AppConfig *config = new AppConfig();
    CaptureConfig captureConfig = config->GetCaptureConfig();
    // loadCaptureThread =
    //     new LoadCaptureThread(parent, camera, sessionData.imageData,
    //                           captureConfig.maxFrame, false, false);
    loadCaptureThread->Run();
    delete config;
    config = nullptr;
}

void Model::endLoadCaptureHandler(wxEvtHandler *parent) {
    loadCaptureThread = stopAndDeleteThread(loadCaptureThread);
}

void Model::startProcessHandler(wxEvtHandler *parent) {
    if (processThread != nullptr) {
        throw std::runtime_error("ProcessThread is already running");
    }

    if (sessionData.isImageDataEmpty()) {
        throw std::runtime_error("imageData is empty");
    }
    std::cout << "Model::startProcessHandler()" << std::endl;
    processThread =
        new ProcessThread(parent, threadPool, sessionData.imageData);
    processThread->Run();
}

template <typename T>
T *Model::stopAndDeleteThread(T *threadPtr) {
    if (threadPtr == nullptr) {
        return nullptr;
    }

    threadPtr->Delete();
    delete threadPtr;
    threadPtr = nullptr;

    return threadPtr;
}

// TODO : Change to enum norm
void Model::requestChangePanel(wxEvtHandler *parent, PanelID panelID) {
    switch (panelID) {
        case PANEL_CAPTURE: changeCapturePanel(parent); break;
        default: break;
    }
}

void Model::changeCapturePanel(wxEvtHandler *parent) {
    if (captureThread != nullptr) {
        endCaptureHandler();
    }

    if (loadFileThread != nullptr) {
        endLoadFileHandler(parent);
    }

    if (loadCaptureThread != nullptr) {
        endLoadCaptureHandler(parent);
    }

    if (sessionData.isImageDataEmpty()) {
        throw std::runtime_error("sessionData is empty");
    }

    sessionData.currentPanelID = PANEL_ROI;

    wxCommandEvent changePanelEvent(c_CHANGE_PANEL_EVENT, CHANGE_OK);
    wxPostEvent(parent, changePanelEvent);
}