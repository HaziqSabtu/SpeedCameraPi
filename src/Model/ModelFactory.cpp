#include "Thread/ThreadPool.hpp"
#include "Thread/Thread_Controller.hpp"
#include "Utils/Camera/CameraBase.hpp"
#include <Model/ModelFactory.hpp>
#include <memory>

ModelFactory::ModelFactory(wxWindow *parent) {
    sharedModel = std::make_shared<SharedModel>();

    AppConfig config;

    CameraConfig cameraConfig = config.GetCameraConfig();

    std::unique_ptr<CameraBase> camera = std::make_unique<LibCam>();
    camera->setHeight(cameraConfig.Camera_Height);
    camera->setWidth(cameraConfig.Camera_Width);
    camera->setFPS(cameraConfig.Camera_FPS);

    if (!camera->start()) {
        ErrorEvent errorEvent(c_ERROR_EVENT, wxID_ANY);
        errorEvent.SetErrorData(" Camera not found! ");
        wxPostEvent(parent, errorEvent);
    }

    std::shared_ptr<ThreadPool> threadPool = std::make_shared<ThreadPool>();
    threadPool->setNumThreads(config.GetPanelConfig().Thread_Pool_Size);

    std::shared_ptr<ThreadController> threadController =
        std::make_shared<ThreadController>();

    sharedModel->setCamera(camera);
    sharedModel->setThreadPool(threadPool);
    sharedModel->setThreadController(threadController);
}

ModelFactory::~ModelFactory() { sharedModel = nullptr; }

std::unique_ptr<CaptureModel> ModelFactory::createCaptureModel() {
    return std::make_unique<CaptureModel>(sharedModel);
}

std::unique_ptr<RoiModel> ModelFactory::createRoiModel() {
    return std::make_unique<RoiModel>(sharedModel);
}

std::shared_ptr<SharedModel> ModelFactory::getSharedModel() {
    return sharedModel;
}

std::unique_ptr<CalibrationModel> ModelFactory::createCalibrationModel() {
    return std::make_unique<CalibrationModel>(sharedModel);
}