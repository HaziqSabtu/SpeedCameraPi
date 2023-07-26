#include "Controller/CalibrationController.hpp"
#include "Controller/CaptureController.hpp"
#include "Controller/ManualCalibrationController.hpp"
#include "Model/SharedModel.hpp"
#include "Thread/ThreadPool.hpp"
#include "Thread/Thread_Controller.hpp"
#include "Utils/Camera/CameraBase.hpp"
#include <Controller/ControllerFactory.hpp>
#include <memory>

ControllerFactory::ControllerFactory(wxWindow *parent) {

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

ControllerFactory::~ControllerFactory() { sharedModel = nullptr; }

CPCPtr ControllerFactory::createCaptureModel() {
    return std::make_unique<CaptureController>(sharedModel);
}

std::unique_ptr<RoiModel> ControllerFactory::createRoiModel() {
    return std::make_unique<RoiModel>(sharedModel);
}

ModelPtr ControllerFactory::getSharedModel() { return sharedModel; }

CLCPtr ControllerFactory::createCalibrationModel() {
    return std::make_unique<CalibrationController>(sharedModel);
}

MCCPtr ControllerFactory::createManualCalibrationController() {
    return std::make_unique<ManualCalibrationController>(sharedModel);
}

CCCPtr ControllerFactory::createColorCalibrationController() {
    return std::make_unique<ColorCalibrationController>(sharedModel);
}