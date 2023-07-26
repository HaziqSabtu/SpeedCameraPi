#include <Model/AppState.hpp>

AppState::AppState() {}

AppState::AppState(modelPtr model) {
    cameraPanel = getCameraPanelState(model);
    calibrationPanel = getCalibrationPanelState(model);
}

CameraPanelState AppState::getCameraPanelState(modelPtr model) {
    CameraPanelState cameraPanelState;

    auto isImageEmpty = model->sessionData.isImageDataEmpty();
    cameraPanelState.state =
        isImageEmpty ? PanelState::PANEL_NOT_OK : PanelState::PANEL_OK;

    cameraPanelState.captureButtonState = getCaptureButtonState(model);
    cameraPanelState.loadButtonState = getLoadButtonState(model);
    cameraPanelState.replayButtonState = getReplayButtonState(model);
    cameraPanelState.removeButtonState = getRemoveButtonState(model);
    cameraPanelState.cameraButtonState = getCameraButtonState(model);

    return cameraPanelState;
}

CalibrationPanelState AppState::getCalibrationPanelState(modelPtr model) {
    CalibrationPanelState calibrationPanelState;

    auto isImageEmpty = model->sessionData.isImageDataEmpty();
    calibrationPanelState.state = PanelState::PANEL_NOT_OK;
    calibrationPanelState.calibrationButtonState =
        getCalibrationButtonState(model);
    calibrationPanelState.cameraButtonState = getCameraButtonState(model);
    calibrationPanelState.removeButtonState = getRemoveButtonState2(model);

    return calibrationPanelState;
}

ButtonState AppState::getCaptureButtonState(modelPtr model) {
    auto tc = model->getThreadController();
    if (!tc->isThreadNullptr(THREAD_LOAD_CAPTURE)) {
        return ButtonState::ACTIVE;
    }

    if (!tc->isThreadNullptr(THREAD_LOAD_FILE)) {
        return ButtonState::DISABLED;
    }

    if (!tc->isThreadNullptr(THREAD_CAPTURE)) {
        return ButtonState::DISABLED;
    }

    if (model->sessionData.isImageDataEmpty()) {
        return ButtonState::NORMAL;
    }

    return ButtonState::DISABLED;
}

ButtonState AppState::getLoadButtonState(modelPtr model) {
    auto tc = model->getThreadController();
    if (!tc->isThreadNullptr(THREAD_LOAD_CAPTURE)) {
        return ButtonState::DISABLED;
    }

    if (!tc->isThreadNullptr(THREAD_LOAD_FILE)) {
        return ButtonState::ACTIVE;
    }

    if (!tc->isThreadNullptr(THREAD_CAPTURE)) {
        return ButtonState::DISABLED;
    }

    if (model->sessionData.isImageDataEmpty()) {
        return ButtonState::NORMAL;
    }

    return ButtonState::DISABLED;
}

ButtonState AppState::getReplayButtonState(modelPtr model) {
    auto tc = model->getThreadController();

    if (!tc->isThreadNullptr(THREAD_REPLAY)) {
        return ButtonState::ACTIVE;
    }

    if (!model->sessionData.isImageDataEmpty()) {
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

ButtonState AppState::getRemoveButtonState(modelPtr model) {
    auto tc = model->getThreadController();

    if (!tc->isThreadNullptr(THREAD_LOAD_CAPTURE)) {
        return ButtonState::DISABLED;
    }

    if (!tc->isThreadNullptr(THREAD_LOAD_FILE)) {
        return ButtonState::DISABLED;
    }

    if (!tc->isThreadNullptr(THREAD_CAPTURE)) {
        return ButtonState::DISABLED;
    }

    if (!model->sessionData.isImageDataEmpty()) {
        return ButtonState::NORMAL;
    }

    return ButtonState::DISABLED;
}

ButtonState AppState::getCameraButtonState(modelPtr model) {

    auto tc = model->getThreadController();

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
    if (!model->sessionData.isImageDataEmpty()) {
        return ButtonState::DISABLED;
    }

    return ButtonState::OFF;
}

ButtonState AppState::getCalibrationButtonState(modelPtr model) {
    auto tc = model->getThreadController();

    if (!tc->isThreadNullptr(THREAD_CALIBRATION)) {
        return ButtonState::ACTIVE;
    }

    // TODO: Fix this
    if (!model->sessionData.isImageDataEmpty()) {
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

ButtonState AppState::getRemoveButtonState2(modelPtr model) {
    return ButtonState::DISABLED;
}