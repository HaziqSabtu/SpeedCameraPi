#include <Model/AppState.hpp>

AppState::AppState() {}

AppState::AppState(ModelPtr model) {
    cameraPanel = getCameraPanelState(model);
    calibrationPanel = getCalibrationPanelState(model);
}

CameraPanelState AppState::getCameraPanelState(ModelPtr model) {
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

CalibrationPanelState AppState::getCalibrationPanelState(ModelPtr model) {
    CalibrationPanelState calibrationPanelState;

    auto isImageEmpty = model->sessionData.isImageDataEmpty();
    calibrationPanelState.state = PanelState::PANEL_NOT_OK;
    calibrationPanelState.calibrationButtonState =
        getCalibrationButtonState(model);
    calibrationPanelState.cameraButtonState = getCameraButtonState(model);
    calibrationPanelState.removeButtonState = getRemoveButtonState2(model);

    return calibrationPanelState;
}

ButtonState AppState::getCaptureButtonState(ModelPtr model) {
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

ButtonState AppState::getLoadButtonState(ModelPtr model) {
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

ButtonState AppState::getReplayButtonState(ModelPtr model) {
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

ButtonState AppState::getRemoveButtonState(ModelPtr model) {
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

ButtonState AppState::getCameraButtonState(ModelPtr model) {

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

ButtonState AppState::getCalibrationButtonState(ModelPtr model) {
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

ButtonState AppState::getRemoveButtonState2(ModelPtr model) {
    return ButtonState::DISABLED;
}