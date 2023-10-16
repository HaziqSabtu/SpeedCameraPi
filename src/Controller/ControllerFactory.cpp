#include "Controller/CalibrationController.hpp"
#include "Controller/CaptureController.hpp"
#include "Controller/ManualCalibrationController.hpp"
#include "Controller/RoiController.hpp"
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

    CameraPtr camera = std::make_unique<LibCam>();
    camera->setHeight(cameraConfig.Camera_Height);
    camera->setWidth(cameraConfig.Camera_Width);
    camera->setFPS(cameraConfig.Camera_FPS);

    if (!camera->start()) {
        ErrorEvent errorEvent(c_ERROR_EVENT, wxID_ANY);
        errorEvent.SetErrorData(" Camera not found! ");
        wxPostEvent(parent, errorEvent);
    }

    std::shared_ptr<ThreadPool> threadPool = std::make_shared<ThreadPool>();
    threadPool->setNumThreads(config.GetModelConfig().Pool_Size);

    std::shared_ptr<ThreadController> threadController =
        std::make_shared<ThreadController>();

    sharedModel->setCamera(camera);
    sharedModel->setThreadPool(threadPool);
    sharedModel->setThreadController(threadController);
}

ControllerFactory::~ControllerFactory() { sharedModel = nullptr; }

ModelPtr ControllerFactory::getSharedModel() { return sharedModel; }

CPCPtr ControllerFactory::createCaptureController() {
    return std::make_shared<CaptureController>(sharedModel);
}

CLCPtr ControllerFactory::createCalibrationController() {
    return std::make_shared<CalibrationController>(sharedModel);
}

HCCPtr ControllerFactory::createHorizontalCalibrationController() {
    return std::make_shared<HorizontalCalibrationController>(sharedModel);
}

MCCPtr ControllerFactory::createManualCalibrationController() {
    return std::make_shared<ManualCalibrationController>(sharedModel);
}

CCCPtr ControllerFactory::createColorCalibrationController() {
    return std::make_shared<ColorCalibrationController>(sharedModel);
}

ROCPtr ControllerFactory::createRoiController() {
    return std::make_shared<RoiController>(sharedModel);
}

RSCPtr ControllerFactory::createResultController() {
    return std::make_shared<ResultController>(sharedModel);
}

TDCPtr ControllerFactory::createTrimDataController() {
    return std::make_shared<TrimDataController>(sharedModel);
}