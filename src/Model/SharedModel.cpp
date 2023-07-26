#include "Model/SharedModel.hpp"
#include "Model/AppState.hpp"
#include "Model/SessionData.hpp"
#include "Thread/Thread_Controller.hpp"
#include "Thread/Thread_ID.hpp"
#include <memory>
#include <wx/event.h>

SharedModel::SharedModel() : camera(nullptr), threadPool(nullptr) {}

SharedModel::~SharedModel() {
    try {
        if (camera != nullptr) {
            camera->stop();
        }
    } catch (std::exception &e) {
        std::cout << e.what() << std::endl;
    }
}

void SharedModel::setCamera(std::unique_ptr<CameraBase> &camera) {
    this->camera = std::move(camera);
}

std::unique_ptr<CameraBase> SharedModel::getCamera() {
    return camera == nullptr ? nullptr : std::move(camera);
}

bool SharedModel::isCameraAvailable() { return camera != nullptr; }

void SharedModel::setThreadPool(std::shared_ptr<ThreadPool> threadPool) {
    this->threadPool = threadPool;
}

std::shared_ptr<ThreadPool> SharedModel::getThreadPool() { return threadPool; }

void SharedModel::setThreadController(
    std::shared_ptr<ThreadController> threadController) {
    this->threadController = threadController;
}

std::shared_ptr<ThreadController> SharedModel::getThreadController() {
    return threadController;
}

void SharedModel::killAllThreads() {
    auto tc = getThreadController();

    if (!tc->isThreadNullptr(ThreadID::THREAD_CAPTURE)) {
        auto captureThread = tc->getCaptureThread();
        captureThread->Pause();

        auto camera = captureThread->getCamera();
        setCamera(camera);

        tc->endCaptureHandler();
    }

    if (!tc->isThreadNullptr(ThreadID::THREAD_LOAD_CAPTURE)) {
        auto loadCaptureThread = tc->getLoadCaptureThread();
        loadCaptureThread->Pause();

        auto camera = loadCaptureThread->getCamera();
        setCamera(camera);

        tc->endLoadCaptureHandler();
    }

    if (!tc->isThreadNullptr(ThreadID::THREAD_CALIBRATION)) {
        auto calibrationThread = tc->getCalibrationThread();
        calibrationThread->Pause();

        auto camera = calibrationThread->getCamera();
        setCamera(camera);

        tc->endCalibrationHandler();
    }
}

AppState SharedModel::getAppState() {
    AppState appState;
    appState.cameraPanel = getCameraPanelState();
    appState.calibrationPanel = getCalibrationPanelState();
    return appState;
}

CameraPanelState SharedModel::getCameraPanelState() {
    CameraPanelState cameraPanelState;

    auto isImageEmpty = sessionData.isImageDataEmpty();
    cameraPanelState.state =
        isImageEmpty ? PanelState::PANEL_NOT_OK : PanelState::PANEL_OK;

    cameraPanelState.captureButtonState = getCaptureButtonState();
    cameraPanelState.loadButtonState = getLoadButtonState();
    cameraPanelState.replayButtonState = getReplayButtonState();
    cameraPanelState.removeButtonState = getRemoveButtonState();
    cameraPanelState.cameraButtonState = getCameraButtonState();

    return cameraPanelState;
}

CalibrationPanelState SharedModel::getCalibrationPanelState() {
    CalibrationPanelState calibrationPanelState;

    auto isImageEmpty = sessionData.isImageDataEmpty();
    calibrationPanelState.state = PanelState::PANEL_NOT_OK;
    calibrationPanelState.calibrationButtonState = getCalibrationButtonState();
    calibrationPanelState.cameraButtonState = getCameraButtonState();
    calibrationPanelState.removeButtonState = getRemoveButtonState2();

    return calibrationPanelState;
}

ButtonState SharedModel::getCaptureButtonState() {
    auto tc = getThreadController();
    if (!tc->isThreadNullptr(THREAD_LOAD_CAPTURE)) {
        return ButtonState::ACTIVE;
    }

    if (!tc->isThreadNullptr(THREAD_LOAD_FILE)) {
        return ButtonState::DISABLED;
    }

    if (!tc->isThreadNullptr(THREAD_CAPTURE)) {
        return ButtonState::DISABLED;
    }

    if (sessionData.isImageDataEmpty()) {
        return ButtonState::NORMAL;
    }

    return ButtonState::DISABLED;
}

ButtonState SharedModel::getLoadButtonState() {
    auto tc = getThreadController();
    if (!tc->isThreadNullptr(THREAD_LOAD_CAPTURE)) {
        return ButtonState::DISABLED;
    }

    if (!tc->isThreadNullptr(THREAD_LOAD_FILE)) {
        return ButtonState::ACTIVE;
    }

    if (!tc->isThreadNullptr(THREAD_CAPTURE)) {
        return ButtonState::DISABLED;
    }

    if (sessionData.isImageDataEmpty()) {
        return ButtonState::NORMAL;
    }

    return ButtonState::DISABLED;
}

ButtonState SharedModel::getReplayButtonState() {
    auto tc = getThreadController();

    if (!tc->isThreadNullptr(THREAD_REPLAY)) {
        return ButtonState::ACTIVE;
    }

    if (!sessionData.isImageDataEmpty()) {
        return ButtonState::NORMAL;
    }

    if (!tc->isThreadNullptr(THREAD_LOAD_CAPTURE)) {
        return ButtonState::DISABLED;
    }

    if (!tc->isThreadNullptr(THREAD_LOAD_FILE)) {
        return ButtonState::DISABLED;
    }

    if (!tc->isThreadNullptr(THREAD_CAPTURE)) {
        return ButtonState::DISABLED;
    }

    return ButtonState::DISABLED;
}

ButtonState SharedModel::getRemoveButtonState() {
    auto tc = getThreadController();

    if (!tc->isThreadNullptr(THREAD_LOAD_CAPTURE)) {
        return ButtonState::DISABLED;
    }

    if (!tc->isThreadNullptr(THREAD_LOAD_FILE)) {
        return ButtonState::DISABLED;
    }

    if (!tc->isThreadNullptr(THREAD_CAPTURE)) {
        return ButtonState::DISABLED;
    }

    if (!sessionData.isImageDataEmpty()) {
        return ButtonState::NORMAL;
    }

    return ButtonState::DISABLED;
}

ButtonState SharedModel::getCameraButtonState() {

    auto tc = getThreadController();

    if (!tc->isThreadNullptr(THREAD_CAPTURE)) {
        return ButtonState::ON;
    }

    if (!tc->isThreadNullptr(THREAD_LOAD_FILE)) {
        return ButtonState::DISABLED;
    }

    if (!tc->isThreadNullptr(THREAD_LOAD_CAPTURE)) {
        return ButtonState::DISABLED;
    }

    // !ERROR Might Cause issue
    if (!sessionData.isImageDataEmpty()) {
        return ButtonState::DISABLED;
    }

    return ButtonState::OFF;
}

ButtonState SharedModel::getCalibrationButtonState() {
    auto tc = getThreadController();

    if (!tc->isThreadNullptr(THREAD_CALIBRATION)) {
        return ButtonState::ACTIVE;
    }

    // TODO: Fix this
    if (!sessionData.isImageDataEmpty()) {
        return ButtonState::NORMAL;
    }

    if (!tc->isThreadNullptr(THREAD_LOAD_CAPTURE)) {
        return ButtonState::DISABLED;
    }

    if (!tc->isThreadNullptr(THREAD_LOAD_FILE)) {
        return ButtonState::DISABLED;
    }

    if (!tc->isThreadNullptr(THREAD_CAPTURE)) {
        return ButtonState::DISABLED;
    }

    return ButtonState::DISABLED;
}

ButtonState SharedModel::getRemoveButtonState2() {
    return ButtonState::DISABLED;
}