#include "Model/SharedModel.hpp"
#include "Thread/Thread_ColorCalib.hpp"
#include "Thread/Thread_ID.hpp"
#include "Thread/Thread_ManualCalib.hpp"
#include <Model/AppState.hpp>

AppState::AppState() {}

AppState::AppState(ModelPtr model) {
    cameraPanel = getCameraPanelState(model);
    calibrationPanel = getCalibrationPanelState(model);
    manualCalibrationPanel = getManualCalibrationPanelState(model);
    colorCalibrationPanel = getColorCalibrationPanelState(model);
    roiPanel = getRoiPanelState(model);
}

PanelState AppState::getCameraStatusState(ModelPtr model) {
    return model->sessionData.isCaptureDataEmpty() ? PanelState::PANEL_NOT_OK
                                                   : PanelState::PANEL_OK;
}

PanelState AppState::getCalibrationStatusState(ModelPtr model) {
    return model->sessionData.isCalibDataEmpty() ? PanelState::PANEL_NOT_OK
                                                 : PanelState::PANEL_OK;
}

PanelState AppState::getRoiStatusState(ModelPtr model) {
    return model->sessionData.isRoiDataEmpty() ? PanelState::PANEL_NOT_OK
                                               : PanelState::PANEL_OK;
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
    mcps.stopButtonState = getMCStopButtonState(model);
    mcps.cameraButtonState = getMCCameraButtonState(model);
    mcps.removeButtonState = getMCRemoveButtonState(model);

    mcps.leftStatusState = getMCLeftStatusState(model);
    mcps.selectLeftButtonState = getMCSelectLeftButtonState(model);
    mcps.removeLeftButtonState = getMCRemoveLeftButtonState(model);

    mcps.rightStatusState = getMCRightStatusState(model);
    mcps.selectRightButtonState = getMCSelectRightButtonState(model);
    mcps.removeRightButtonState = getMCRemoveRightButtonState(model);

    mcps.okButtonState = getMCOKButtonState(model);
    mcps.cancelButtonState = getMCCancelButtonState(model);

    return mcps;
}

ColorCalibrationPanelState
AppState::getColorCalibrationPanelState(std::shared_ptr<SharedModel> model) {
    ColorCalibrationPanelState ccps;

    ccps.calibrationButtonState = getCCButtonState(model);
    ccps.stopButtonState = getCCStopButtonState(model);
    ccps.cameraButtonState = getCCCameraButtonState(model);
    ccps.removeButtonState = getCCRemoveButtonState(model);

    ccps.blueStatusState = getCCBlueStatusState(model);
    ccps.selectBlueButtonState = getCCSelectBlueButtonState(model);
    ccps.acceptBlueButtonState = getCCAcceptBlueButtonState(model);

    ccps.yellowStatusState = getCCYellowStatusState(model);
    ccps.selectYellowButtonState = getCCSelectYellowButtonState(model);
    ccps.acceptYellowButtonState = getCCAcceptYellowButtonState(model);

    ccps.saveButtonState = getCCSaveButtonState(model);
    ccps.restoreButtonState = getCCRestoreButtonState(model);

    ccps.okButtonState = getCCOKButtonState(model);
    ccps.cancelButtonState = getCCCancelButtonState(model);

    return ccps;
}

RoiPanelState AppState::getRoiPanelState(ModelPtr model) {
    RoiPanelState rops;

    rops.state = getRoiStatusState(model);

    rops.roiButtonState = getROIButtonState(model);
    rops.stopButtonState = getROIStopButtonState(model);
    rops.cameraButtonState = getROICameraButtonState(model);
    rops.removeButtonState = getROIRemoveButtonState(model);

    rops.acceptRoiButtonState = getROIAcceptRoiButtonState(model);
    rops.clearRoiButtonState = getROIClearRoiButtonState(model);

    rops.okButtonState = getROIOKButtonState(model);
    rops.cancelButtonState = getROICancelButtonState(model);

    return rops;
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

    if (model->sessionData.isCaptureDataEmpty()) {
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

    if (model->sessionData.isCaptureDataEmpty()) {
        return ButtonState::NORMAL;
    }

    return ButtonState::DISABLED;
}

ButtonState AppState::getReplayButtonState(ModelPtr model) {
    auto tc = model->getThreadController();

    if (!tc->isThreadNullptr(THREAD_REPLAY)) {
        return ButtonState::ACTIVE;
    }

    if (!model->sessionData.isCaptureDataEmpty()) {
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

    if (!model->sessionData.isCaptureDataEmpty()) {
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

    if (!model->sessionData.isCaptureDataEmpty()) {
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

    if (model->sessionData.isCalibDataEmpty()) {
        return ButtonState::DISABLED;
    }

    return ButtonState::NORMAL;
}

ButtonState AppState::getCPROIButtonState(ModelPtr model) {
    auto tc = model->getThreadController();

    if (!tc->isThreadsWithCameraNullptr()) {
        return ButtonState::DISABLED;
    }

    if (model->sessionData.isCaptureDataEmpty()) {
        return ButtonState::DISABLED;
    }

    return ButtonState::NORMAL;
}

ButtonState AppState::getCPROIRemoveButtonState(ModelPtr model) {
    auto tc = model->getThreadController();

    if (!tc->isThreadsWithCameraNullptr()) {
        return ButtonState::DISABLED;
    }

    if (model->sessionData.isCaptureDataEmpty()) {
        return ButtonState::DISABLED;
    }

    auto data = model->getSessionData();
    if (data->isRoiDataEmpty()) {
        return ButtonState::DISABLED;
    }

    return ButtonState::NORMAL;
}

ButtonState AppState::getCPMeasureButtonState(ModelPtr model) {
    return ButtonState::DISABLED;
}

ButtonState AppState::getCalibrationButtonState(ModelPtr model) {
    auto tc = model->getThreadController();

    if (!tc->isThreadNullptr(THREAD_CALIBRATION)) {
        return ButtonState::ACTIVE;
    }

    if (!tc->isThreadNullptr(THREAD_CALIBRATION_PREVIEW)) {
        return ButtonState::DISABLED;
    }

    if (model->sessionData.isCalibDataEmpty()) {
        return ButtonState::NORMAL;
    }

    if (!model->sessionData.isCalibDataEmpty()) {
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

    if (model->sessionData.isCalibDataEmpty()) {
        return ButtonState::DISABLED;
    }

    if (!model->sessionData.isCalibDataEmpty()) {
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

    if (!tc->isThreadNullptr(THREAD_CALIBRATION_PREVIEW)) {
        return ButtonState::DISABLED;
    }

    if (model->sessionData.isCalibDataEmpty()) {
        return ButtonState::DISABLED;
    }

    return ButtonState::NORMAL;
}

ButtonState AppState::getCLCancelButtonState(ModelPtr model) {
    auto tc = model->getThreadController();

    if (!tc->isThreadNullptr(THREAD_CALIBRATION)) {
        return ButtonState::DISABLED;
    }

    if (!tc->isThreadNullptr(THREAD_CALIBRATION_PREVIEW)) {
        return ButtonState::DISABLED;
    }

    return ButtonState::NORMAL;
}

ButtonState AppState::getMCRemoveButtonState(ModelPtr model) {
    auto tc = model->getThreadController();

    if (!tc->isThreadNullptr(THREAD_MANUAL_CALIBRATION)) {
        return ButtonState::DISABLED;
    }

    if (!tc->isThreadNullptr(THREAD_CALIBRATION_PREVIEW)) {
        return ButtonState::DISABLED;
    }

    if (model->sessionData.isCalibDataEmpty()) {
        return ButtonState::DISABLED;
    }

    if (!model->sessionData.isCalibDataEmpty()) {
        return ButtonState::NORMAL;
    }

    return ButtonState::NORMAL;
}

ButtonState AppState::getMCButtonState(ModelPtr model) {
    auto tc = model->getThreadController();

    if (!tc->isThreadNullptr(THREAD_MANUAL_CALIBRATION)) {
        return ButtonState::ACTIVE;
    }

    if (!tc->isThreadNullptr(THREAD_CALIBRATION_PREVIEW)) {
        return ButtonState::DISABLED;
    }

    if (model->sessionData.isCalibDataEmpty()) {
        return ButtonState::NORMAL;
    }

    if (!model->sessionData.isCalibDataEmpty()) {
        return ButtonState::DISABLED;
    }

    return ButtonState::NORMAL;
}

ButtonState AppState::getMCStopButtonState(ModelPtr model) {
    auto tc = model->getThreadController();

    if (tc->isThreadNullptr(THREAD_MANUAL_CALIBRATION)) {
        return ButtonState::DISABLED;
    }

    if (!tc->isThreadNullptr(THREAD_CALIBRATION_PREVIEW)) {
        return ButtonState::DISABLED;
    }

    return ButtonState::NORMAL;
}

ButtonState AppState::getMCCameraButtonState(ModelPtr model) {
    auto tc = model->getThreadController();

    if (!tc->isThreadNullptr(THREAD_MANUAL_CALIBRATION)) {
        return ButtonState::DISABLED;
    }

    if (tc->isThreadNullptr(THREAD_CALIBRATION_PREVIEW)) {
        return ButtonState::OFF;
    }

    return ButtonState::ON;
}

PanelState AppState::getMCLeftStatusState(ModelPtr model) {
    auto tc = model->getThreadController();

    auto data = model->getSessionData();
    auto calibData = data->getCalibData();

    Detection::Line line = calibData.lineLeft;

    if (line.isNull()) {
        return PanelState::PANEL_NOT_OK;
    }
    return PanelState::PANEL_OK;
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

PanelState AppState::getMCRightStatusState(ModelPtr model) {
    auto tc = model->getThreadController();

    auto calibData = model->sessionData.getCalibData();

    Detection::Line line = calibData.lineRight;

    if (line.isNull()) {
        return PanelState::PANEL_NOT_OK;
    }
    return PanelState::PANEL_OK;
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
    auto tc = model->getThreadController();

    if (!tc->isThreadNullptr(THREAD_MANUAL_CALIBRATION)) {
        return ButtonState::DISABLED;
    }

    if (!tc->isThreadNullptr(THREAD_CALIBRATION_PREVIEW)) {
        return ButtonState::DISABLED;
    }

    if (model->sessionData.isCalibDataEmpty()) {
        return ButtonState::DISABLED;
    }

    return ButtonState::NORMAL;
}

ButtonState AppState::getMCCancelButtonState(ModelPtr model) {
    auto tc = model->getThreadController();

    if (!tc->isThreadNullptr(THREAD_MANUAL_CALIBRATION)) {
        return ButtonState::DISABLED;
    }

    if (!tc->isThreadNullptr(THREAD_CALIBRATION_PREVIEW)) {
        return ButtonState::DISABLED;
    }

    return ButtonState::NORMAL;
}

ButtonState AppState::getCCButtonState(ModelPtr model) {
    auto tc = model->getThreadController();

    if (!tc->isThreadNullptr(THREAD_COLOR_CALIBRATION)) {
        return ButtonState::ACTIVE;
    }

    if (!tc->isThreadNullptr(THREAD_COLOR_CALIBRATION_PREVIEW)) {
        return ButtonState::DISABLED;
    }

    auto ccExtraModel = model->getCCExtraModel();
    if (ccExtraModel->isBlueCalibrated() &&
        ccExtraModel->isYellowCalibrated()) {
        return ButtonState::DISABLED;
    }

    return ButtonState::NORMAL;
}

ButtonState AppState::getCCStopButtonState(ModelPtr model) {
    auto tc = model->getThreadController();

    if (!tc->isThreadNullptr(THREAD_COLOR_CALIBRATION)) {
        return ButtonState::NORMAL;
    }

    return ButtonState::DISABLED;
}

ButtonState AppState::getCCCameraButtonState(ModelPtr model) {
    auto tc = model->getThreadController();

    if (!tc->isThreadNullptr(THREAD_COLOR_CALIBRATION)) {
        return ButtonState::DISABLED;
    }

    if (tc->isThreadNullptr(THREAD_COLOR_CALIBRATION_PREVIEW)) {
        return ButtonState::OFF;
    }

    return ButtonState::ON;
}

ButtonState AppState::getCCRemoveButtonState(ModelPtr model) {
    auto tc = model->getThreadController();

    if (!tc->isThreadNullptr(THREAD_COLOR_CALIBRATION)) {
        return ButtonState::DISABLED;
    }

    if (!tc->isThreadNullptr(THREAD_COLOR_CALIBRATION_PREVIEW)) {
        return ButtonState::DISABLED;
    }

    auto ccExtraModel = model->getCCExtraModel();

    if (ccExtraModel->isBlueCalibrated() ||
        ccExtraModel->isYellowCalibrated()) {
        return ButtonState::NORMAL;
    }

    return ButtonState::DISABLED;
}

PanelState AppState::getCCBlueStatusState(ModelPtr model) {
    auto ccExtraModel = model->getCCExtraModel();
    if (ccExtraModel->isBlueCalibrated()) {
        return PanelState::PANEL_OK;
    }

    return PanelState::PANEL_NOT_OK;
}

ButtonState AppState::getCCSelectBlueButtonState(ModelPtr model) {
    auto tc = model->getThreadController();

    if (tc->isThreadNullptr(THREAD_COLOR_CALIBRATION)) {
        return ButtonState::DISABLED;
    }

    if (!tc->isThreadNullptr(THREAD_COLOR_CALIBRATION_PREVIEW)) {
        return ButtonState::DISABLED;
    }

    auto colorCalibrationThread = tc->getColorCalibrationThread();
    if (colorCalibrationThread->getColorCalibrationType() ==
        ColorCalibrationType::COLOR_CALIBRATION_BLUE) {
        return ButtonState::ACTIVE;
    }

    return ButtonState::NORMAL;
}

ButtonState AppState::getCCAcceptBlueButtonState(ModelPtr model) {
    auto tc = model->getThreadController();

    if (tc->isThreadNullptr(THREAD_COLOR_CALIBRATION)) {
        return ButtonState::DISABLED;
    }

    if (!tc->isThreadNullptr(THREAD_COLOR_CALIBRATION_PREVIEW)) {
        return ButtonState::DISABLED;
    }

    auto colorCalibrationThread = tc->getColorCalibrationThread();
    if (colorCalibrationThread->getColorCalibrationType() !=
        ColorCalibrationType::COLOR_CALIBRATION_BLUE) {
        return ButtonState::DISABLED;
    }

    return ButtonState::NORMAL;
}

PanelState AppState::getCCYellowStatusState(ModelPtr model) {
    auto ccExtraModel = model->getCCExtraModel();
    if (ccExtraModel->isYellowCalibrated()) {
        return PanelState::PANEL_OK;
    }

    return PanelState::PANEL_NOT_OK;
}

ButtonState AppState::getCCSelectYellowButtonState(ModelPtr model) {
    auto tc = model->getThreadController();

    if (tc->isThreadNullptr(THREAD_COLOR_CALIBRATION)) {
        return ButtonState::DISABLED;
    }

    if (!tc->isThreadNullptr(THREAD_COLOR_CALIBRATION_PREVIEW)) {
        return ButtonState::DISABLED;
    }

    auto colorCalibrationThread = tc->getColorCalibrationThread();
    if (colorCalibrationThread->getColorCalibrationType() ==
        ColorCalibrationType::COLOR_CALIBRATION_YELLOW) {
        return ButtonState::ACTIVE;
    }

    return ButtonState::NORMAL;
}

ButtonState AppState::getCCAcceptYellowButtonState(ModelPtr model) {
    auto tc = model->getThreadController();

    if (tc->isThreadNullptr(THREAD_COLOR_CALIBRATION)) {
        return ButtonState::DISABLED;
    }

    if (!tc->isThreadNullptr(THREAD_COLOR_CALIBRATION_PREVIEW)) {
        return ButtonState::DISABLED;
    }

    auto colorCalibrationThread = tc->getColorCalibrationThread();
    if (colorCalibrationThread->getColorCalibrationType() !=
        ColorCalibrationType::COLOR_CALIBRATION_YELLOW) {
        return ButtonState::DISABLED;
    }

    return ButtonState::NORMAL;
}

ButtonState AppState::getCCSaveButtonState(ModelPtr model) {
    auto tc = model->getThreadController();

    if (!tc->isThreadNullptr(THREAD_COLOR_CALIBRATION)) {
        return ButtonState::DISABLED;
    }

    if (!tc->isThreadNullptr(THREAD_COLOR_CALIBRATION_PREVIEW)) {
        return ButtonState::DISABLED;
    }

    auto ccExtraModel = model->getCCExtraModel();

    if (!ccExtraModel->isBlueCalibrated()) {
        return ButtonState::DISABLED;
    }

    if (!ccExtraModel->isYellowCalibrated()) {
        return ButtonState::DISABLED;
    }

    return ButtonState::NORMAL;
}

ButtonState AppState::getCCRestoreButtonState(ModelPtr model) {
    auto tc = model->getThreadController();

    if (!tc->isThreadNullptr(THREAD_COLOR_CALIBRATION)) {
        return ButtonState::DISABLED;
    }

    if (!tc->isThreadNullptr(THREAD_COLOR_CALIBRATION_PREVIEW)) {
        return ButtonState::DISABLED;
    }

    return ButtonState::NORMAL;
}

ButtonState AppState::getCCOKButtonState(ModelPtr model) {
    auto tc = model->getThreadController();

    if (!tc->isThreadNullptr(THREAD_COLOR_CALIBRATION)) {
        return ButtonState::DISABLED;
    }

    if (!tc->isThreadNullptr(THREAD_COLOR_CALIBRATION_PREVIEW)) {
        return ButtonState::DISABLED;
    }

    auto ccExtraModel = model->getCCExtraModel();

    if (!ccExtraModel->isBlueCalibrated()) {
        return ButtonState::DISABLED;
    }

    if (!ccExtraModel->isYellowCalibrated()) {
        return ButtonState::DISABLED;
    }

    return ButtonState::NORMAL;
}

ButtonState AppState::getCCCancelButtonState(ModelPtr model) {
    auto tc = model->getThreadController();

    if (!tc->isThreadNullptr(THREAD_COLOR_CALIBRATION)) {
        return ButtonState::DISABLED;
    }

    if (!tc->isThreadNullptr(THREAD_COLOR_CALIBRATION_PREVIEW)) {
        return ButtonState::DISABLED;
    }

    return ButtonState::NORMAL;
}

ButtonState AppState::getROIButtonState(ModelPtr model) {
    auto tc = model->getThreadController();

    if (!tc->isThreadNullptr(THREAD_ROI)) {
        return ButtonState::ACTIVE;
    }

    if (!tc->isThreadNullptr(THREAD_ROI_PREVIEW)) {
        return ButtonState::DISABLED;
    }

    return ButtonState::NORMAL;
}

ButtonState AppState::getROIStopButtonState(ModelPtr model) {
    auto tc = model->getThreadController();

    if (!tc->isThreadNullptr(THREAD_ROI)) {
        return ButtonState::NORMAL;
    }

    if (!tc->isThreadNullptr(THREAD_ROI_PREVIEW)) {
        return ButtonState::DISABLED;
    }

    return ButtonState::DISABLED;
}

ButtonState AppState::getROICameraButtonState(ModelPtr model) {
    auto tc = model->getThreadController();

    if (!tc->isThreadNullptr(THREAD_ROI)) {
        return ButtonState::DISABLED;
    }

    if (!tc->isThreadNullptr(THREAD_ROI_PREVIEW)) {
        return ButtonState::ON;
    }

    return ButtonState::OFF;
}

ButtonState AppState::getROIRemoveButtonState(ModelPtr model) {
    auto tc = model->getThreadController();

    if (!tc->isThreadNullptr(THREAD_ROI)) {
        return ButtonState::DISABLED;
    }

    if (!tc->isThreadNullptr(THREAD_ROI_PREVIEW)) {
        return ButtonState::DISABLED;
    }

    auto data = model->getSessionData();
    if (data->isRoiDataEmpty()) {
        return ButtonState::DISABLED;
    }

    return ButtonState::NORMAL;
}

ButtonState AppState::getROIAcceptRoiButtonState(ModelPtr model) {
    auto tc = model->getThreadController();

    if (!tc->isThreadNullptr(THREAD_ROI)) {
        return ButtonState::NORMAL;
    }
    return ButtonState::DISABLED;
}

ButtonState AppState::getROIClearRoiButtonState(ModelPtr model) {
    auto tc = model->getThreadController();

    if (!tc->isThreadNullptr(THREAD_ROI)) {
        return ButtonState::NORMAL;
    }
    return ButtonState::DISABLED;
}
ButtonState AppState::getROIOKButtonState(ModelPtr model) {
    auto tc = model->getThreadController();

    if (!tc->isThreadNullptr(THREAD_ROI)) {
        return ButtonState::DISABLED;
    }

    if (!tc->isThreadNullptr(THREAD_ROI_PREVIEW)) {
        return ButtonState::DISABLED;
    }

    auto data = model->getSessionData();
    if (data->isRoiDataEmpty()) {
        return ButtonState::DISABLED;
    }

    return ButtonState::NORMAL;
}
ButtonState AppState::getROICancelButtonState(ModelPtr model) {

    auto tc = model->getThreadController();

    if (!tc->isThreadNullptr(THREAD_ROI)) {
        return ButtonState::DISABLED;
    }

    if (!tc->isThreadNullptr(THREAD_ROI_PREVIEW)) {
        return ButtonState::DISABLED;
    }
    return ButtonState::NORMAL;
}
