#include "Model/SharedModel.hpp"
#include "Model/SessionData.hpp"
#include <wx/event.h>

SharedModel::SharedModel(wxWindow *parent) {
    AppConfig config;

    CameraConfig cameraConfig = config.GetCameraConfig();

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
    threadPool->setNumThreads(config.GetPanelConfig().Thread_Pool_Size);
}

SharedModel::~SharedModel() {
    try {
        camera->stop();
    } catch (std::exception &e) {
        std::cout << e.what() << std::endl;
    }
}