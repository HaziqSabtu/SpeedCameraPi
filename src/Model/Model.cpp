#include "Thread/Thread_LoadFile.hpp"
#include <Model/Model.hpp>

Model::Model(wxWindow* parent, wxWindowID id) : wxPanel(parent, id) {
    AppConfig* config = new AppConfig();

    CameraConfig cameraConfig = config->GetCameraConfig();

    camera = std::make_shared<LibCam>();
    camera->setHeight(cameraConfig.Camera_Height);
    camera->setWidth(cameraConfig.Camera_Width);
    camera->setFPS(cameraConfig.Camera_FPS);

    if (!camera->start()) {
        // TODO : Error handling
        wxMessageBox(" Camera not found! ", "Error", wxOK | wxICON_ERROR);
        Close();
    }

    threadPool = std::make_shared<ThreadPool>();
    threadPool->setNumThreads(config->GetPanelConfig().Thread_Pool_Size);

    init();

    delete config;
    config = nullptr;
}

Model::~Model() {}

void Model::init() {
    imgData = std::make_shared<std::vector<ImageData>>();

    captureThread = nullptr;
    loadFileThread = nullptr;

    std::cout << "Model Init" << std::endl;
}

void Model::endPoint(wxEvtHandler* parent, ModelEnum::ModelIDs id) {
    endPoint(parent, id, "");
}

void Model::endPoint(wxEvtHandler* parent,
                     ModelEnum::ModelIDs id,
                     std::string path) {
    switch (id) {
        case ModelEnum::MODEL_START_CAPTURE:
            startCaptureHandler(parent);
            break;
        case ModelEnum::MODEL_END_CAPTURE:
            endCaptureHandler(parent);
            break;
        case ModelEnum::MODEL_START_LOADFILE:
            startLoadFileHandler(parent, path);
            break;
        case ModelEnum::MODEL_END_LOADFILE:
            endLoadFileHandler(parent);
            break;
        case ModelEnum::MODEL_START_LOADCAPTURE:
            startLoadCaptureHandler(parent);
            break;
        case ModelEnum::MODEL_END_LOADCAPTURE:
            endLoadCaptureHandler(parent);
            break;
        default:
            break;
    }
}

void Model::startCaptureHandler(wxEvtHandler* parent) {
    if (captureThread != nullptr) {
        return;
    }
    captureThread = new CaptureThread(parent, camera);
    captureThread->Run();
}

void Model::endCaptureHandler(wxEvtHandler* parent) {
    captureThread = stopAndDeleteThread(captureThread);
}

void Model::startLoadFileHandler(wxEvtHandler* parent, std::string path) {

    if (imgData->empty()) {
        imgData->clear();
    }

    AppConfig* config = new AppConfig();
    LoadConfig loadConfig = config->GetLoadConfig();
    loadFileThread = new LoadFileThread(parent,
                                        threadPool,
                                        imgData,
                                        path,
                                        loadConfig.maxFrame);
    loadFileThread->Run();
    delete config;
    config = nullptr;
}

void Model::endLoadFileHandler(wxEvtHandler* parent) {
    loadFileThread = stopAndDeleteThread(loadFileThread);
}

void Model::startLoadCaptureHandler(wxEvtHandler* parent) {
    if (imgData->empty()) {
        imgData->clear();
    }

    AppConfig* config = new AppConfig();
    CaptureConfig captureConfig = config->GetCaptureConfig();
    loadCaptureThread = new LoadCaptureThread(parent,
                                              camera,
                                              imgData,
                                              captureConfig.maxFrame,
                                              false,
                                              false);
    loadCaptureThread->Run();
    delete config;
    config = nullptr;
}

void Model::endLoadCaptureHandler(wxEvtHandler* parent) {
    loadCaptureThread = stopAndDeleteThread(loadCaptureThread);
}

template <typename T>
T* Model::stopAndDeleteThread(T* threadPtr) {
    if (threadPtr != nullptr) {
        return nullptr;
    }

    threadPtr->Delete();
    delete threadPtr;
    threadPtr = nullptr;

    return threadPtr;
}