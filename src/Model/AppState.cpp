#include "Model/SharedModel.hpp"
#include "Thread/Thread_ID.hpp"
#include "Thread/Thread_ManualCalib.hpp"
#include <Model/AppState.hpp>

AppState::AppState() {}

AppState::AppState(ModelPtr model) {
    cameraPanel = getCameraPanelState(model);
    calibrationPanel = getCalibrationPanelState(model);
    manualCalibrationPanel = getManualCalibrationPanelState(model);
}

PanelState AppState::getCameraStatusState(ModelPtr model) {
    return model->sessionData.isImageDataEmpty() ? PanelState::PANEL_NOT_OK
                                                 : PanelState::PANEL_OK;
}

PanelState AppState::getCalibrationStatusState(ModelPtr model) {
    return model->sessionData.calibData.isNull() ? PanelState::PANEL_NOT_OK
                                                 : PanelState::PANEL_OK;
}

PanelState AppState::getRoiStatusState(ModelPtr model) {
    return PanelState::PANEL_NOT_OK;
}

CapturePanelState AppState::getCameraPanelState(ModelPtr model) {
    CapturePanelState cpps;

    cpps.captureStatusState = getCameraStatusState(model);
    cpps.calibStatusState = getCalibrationStatusState(model);
    cpps.roiStatusState = getRoiStatusState(model);

    cpps.captureButtonState = getCaptureButtonState(model);
    cpps.loadButtonState = getLoadButtonState(model);
    cpps.replayButtonState = getReplayButtonState(model);
    cpps.removeButtonState = getRemoveButtonState(model);
    cpps.cameraButtonState = getCameraButtonState(model);

    cpps.calibButtonState = getCPCalibrationButtonState(model);
    cpps.calibRemoveButtonState = getCPCalibrationRemoveButtonState(model);

    cpps.roiButtonState = getCPROIButtonState(model);
    cpps.roiRemoveButtonState = getCPROIRemoveButtonState(model);

    cpps.measureButtonState = getCPMeasureButtonState(model);

    return cpps;
}

CalibrationPanelState AppState::getCalibrationPanelState(ModelPtr model) {
    CalibrationPanelState clps;

    bool isCalibrationDataNull = model->sessionData.calibData.isNull();

    clps.state = getCalibrationStatusState(model);

    clps.calibrationButtonState = getCalibrationButtonState(model);
    clps.cameraButtonState = getCLCameraButtonState(model);
    clps.removeButtonState = getCalibrationRemoveButtonState(model);

    clps.selectPointButtonState = getSelectPointButtonState(model);
    clps.cancelCalibrationButtonState = getCancelCalibrationButtonState(model);
    clps.acceptCalibrationButtonState = getAcceptCalibrationButtonState(model);

    clps.recalibrateColorButtonState = getRecalibrateColorButtonState(model);
    clps.manualCalibrationButtonState = getManualCalibrationButtonState(model);

    clps.okButtonState = getCLOKButtonState(model);
    clps.cancelButtonState = getCLCancelButtonState(model);

    return clps;
}

ManualCalibrationPanelState
AppState::getManualCalibrationPanelState(std::shared_ptr<SharedModel> model) {
    ManualCalibrationPanelState mcps;

    mcps.state = getCalibrationStatusState(model);

    mcps.calibrationButtonState = getMCButtonState(model);
    mcps.cameraButtonState = getMCCameraButtonState(model);
    mcps.removeButtonState = getMCRemoveButtonState(model);

    mcps.selectLeftButtonState = getMCSelectLeftButtonState(model);
    mcps.removeLeftButtonState = getMCRemoveLeftButtonState(model);

    mcps.selectRightButtonState = getMCSelectRightButtonState(model);
    mcps.removeRightButtonState = getMCRemoveRightButtonState(model);

    mcps.okButtonState = getMCOKButtonState(model);
    mcps.cancelButtonState = getMCCancelButtonState(model);

    return mcps;
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

    if (!model->sessionData.isImageDataEmpty()) {
        return ButtonState::DISABLED;
    }

    return ButtonState::OFF;
}

ButtonState AppState::getCPCalibrationButtonState(ModelPtr model) {
    auto tc = model->getThreadController();

    if (!tc->isThreadsWithCameraNullptr()) {
        return ButtonState::DISABLED;
    }

    return ButtonState::NORMAL;
}

ButtonState AppState::getCPCalibrationRemoveButtonState(ModelPtr model) {
    auto tc = model->getThreadController();

    if (!tc->isThreadsWithCameraNullptr()) {
        return ButtonState::DISABLED;
    }

    if (model->sessionData.calibData.isNull()) {
        return ButtonState::DISABLED;
    }

    return ButtonState::NORMAL;
}

ButtonState AppState::getCPROIButtonState(ModelPtr model) {
    return ButtonState::DISABLED;
}

ButtonState AppState::getCPROIRemoveButtonState(ModelPtr model) {
    return ButtonState::DISABLED;
}

ButtonState AppState::getCPMeasureButtonState(ModelPtr model) {
    return ButtonState::DISABLED;
}

ButtonState AppState::getCalibrationButtonState(ModelPtr model) {
    auto tc = model->getThreadController();

    if (!tc->isThreadNullptr(THREAD_CALIBRATION)) {
        return ButtonState::ACTIVE;
    }

    if (model->sessionData.calibData.isNull()) {
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

    if (model->sessionData.calibData.isNull()) {
        return ButtonState::NORMAL;
    }

    if (!model->sessionData.calibData.isNull()) {
        return ButtonState::DISABLED;
    }

    return ButtonState::NORMAL;
}

ButtonState AppState::getCLCameraButtonState(ModelPtr model) {

    auto tc = model->getThreadController();

    if (!tc->isThreadNullptr(THREAD_CALIBRATION_PREVIEW)) {
        return ButtonState::ON;
    }

    if (!tc->isThreadNullptr(THREAD_CALIBRATION)) {
        return ButtonState::DISABLED;
    }

    return ButtonState::OFF;
}

ButtonState AppState::getCalibrationRemoveButtonState(ModelPtr model) {
    auto tc = model->getThreadController();

    if (!tc->isThreadNullptr(THREAD_CALIBRATION)) {
        return ButtonState::DISABLED;
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

    if (model->sessionData.calibData.isNull()) {
        return ButtonState::DISABLED;
    }

    if (!model->sessionData.calibData.isNull()) {
        return ButtonState::NORMAL;
    }

    return ButtonState::NORMAL;
}

ButtonState AppState::getSelectPointButtonState(ModelPtr model) {
    auto tc = model->getThreadController();

    if (tc->isThreadNullptr(THREAD_CALIBRATION)) {
        return ButtonState::DISABLED;
    }

    return ButtonState::NORMAL;
}

ButtonState AppState::getCancelCalibrationButtonState(ModelPtr model) {
    return getSelectPointButtonState(model);
}

ButtonState AppState::getAcceptCalibrationButtonState(ModelPtr model) {
    return getSelectPointButtonState(model);
}

ButtonState AppState::getRecalibrateColorButtonState(ModelPtr model) {
    auto tc = model->getThreadController();

    if (!tc->isThreadNullptr(THREAD_CALIBRATION)) {
        return ButtonState::DISABLED;
    }

    return ButtonState::NORMAL;
}

ButtonState AppState::getManualCalibrationButtonState(ModelPtr model) {
    return getRecalibrateColorButtonState(model);
}

ButtonState AppState::getCLOKButtonState(ModelPtr model) {
    auto tc = model->getThreadController();

    if (!tc->isThreadNullptr(THREAD_CALIBRATION)) {
        return ButtonState::DISABLED;
    }

    if (model->sessionData.calibData.isNull()) {
        return ButtonState::DISABLED;
    }

    return ButtonState::NORMAL;
}

ButtonState AppState::getCLCancelButtonState(ModelPtr model) {
    auto tc = model->getThreadController();

    if (!tc->isThreadNullptr(THREAD_CALIBRATION)) {
        return ButtonState::DISABLED;
    }

    return ButtonState::NORMAL;
}

ButtonState AppState::getMCRemoveButtonState(ModelPtr model) {
    return ButtonState::NORMAL;
}

ButtonState AppState::getMCButtonState(ModelPtr model) {
    return ButtonState::NORMAL;
}

ButtonState AppState::getMCCameraButtonState(ModelPtr model) {
    return ButtonState::ON;
}

ButtonState AppState::getMCSelectLeftButtonState(ModelPtr model) {
    auto tc = model->getThreadController();

    if (tc->isThreadNullptr(THREAD_MANUAL_CALIBRATION)) {
        return ButtonState::DISABLED;
    }

    auto thread = tc->getManualCalibrationThread();
    if (thread->getDirection() == ManualDirection::MANUAL_LEFT) {
        return ButtonState::ACTIVE;
    }

    return ButtonState::NORMAL;
}

ButtonState AppState::getMCRemoveLeftButtonState(ModelPtr model) {
    auto tc = model->getThreadController();

    if (tc->isThreadNullptr(THREAD_MANUAL_CALIBRATION)) {
        return ButtonState::DISABLED;
    }

    return ButtonState::NORMAL;
}

ButtonState AppState::getMCSelectRightButtonState(ModelPtr model) {
    auto tc = model->getThreadController();

    if (tc->isThreadNullptr(THREAD_MANUAL_CALIBRATION)) {
        return ButtonState::DISABLED;
    }

    auto thread = tc->getManualCalibrationThread();
    if (thread->getDirection() == ManualDirection::MANUAL_RIGHT) {
        return ButtonState::ACTIVE;
    }

    return ButtonState::NORMAL;
}

ButtonState AppState::getMCRemoveRightButtonState(ModelPtr model) {
    auto tc = model->getThreadController();

    if (tc->isThreadNullptr(THREAD_MANUAL_CALIBRATION)) {
        return ButtonState::DISABLED;
    }

    return ButtonState::NORMAL;
}

ButtonState AppState::getMCOKButtonState(ModelPtr model) {
    return ButtonState::NORMAL;
}

ButtonState AppState::getMCCancelButtonState(ModelPtr model) {
    return ButtonState::NORMAL;
}
