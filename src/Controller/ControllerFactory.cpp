#include <Controller/ControllerFactory.hpp>

#include <Thread/Thread_Controller.hpp>

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

LCCPtr ControllerFactory::createLaneCalibrationController() {
    return std::make_shared<LaneCalibrationController>(sharedModel);
}

DCCPtr ControllerFactory::createDistanceCalibrationController() {
    return std::make_shared<DistanceCalibrationController>(sharedModel);
}

LMCPtr ControllerFactory::createLaneManualCalibrationController() {
    return std::make_shared<LaneManualCalibrationController>(sharedModel);
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