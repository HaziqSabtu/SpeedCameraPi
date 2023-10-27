#include <Controller/ControllerFactory.hpp>

#include <Thread/Thread_Controller.hpp>

ControllerFactory::ControllerFactory(wxWindow *parent) {

    shared = std::make_shared<SharedResource>();

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

    shared->setCamera(camera);
    shared->setThreadPool(threadPool);
    shared->setThreadController(threadController);
}

ControllerFactory::~ControllerFactory() { shared = nullptr; }

ResourcePtr ControllerFactory::getSharedModel() { return shared; }

CPCPtr ControllerFactory::createCaptureController() {
    return std::make_shared<CaptureController>(shared);
}

LCCPtr ControllerFactory::createLaneCalibrationController() {
    return std::make_shared<LaneCalibrationController>(shared);
}

DCCPtr ControllerFactory::createDistanceCalibrationController() {
    return std::make_shared<DistanceCalibrationController>(shared);
}

LMCPtr ControllerFactory::createLaneManualCalibrationController() {
    return std::make_shared<LaneManualCalibrationController>(shared);
}

CCCPtr ControllerFactory::createColorCalibrationController() {
    return std::make_shared<ColorCalibrationController>(shared);
}

ROCPtr ControllerFactory::createRoiController() {
    return std::make_shared<RoiController>(shared);
}

RSCPtr ControllerFactory::createResultController() {
    return std::make_shared<ResultController>(shared);
}

TDCPtr ControllerFactory::createTrimDataController() {
    return std::make_shared<TrimDataController>(shared);
}