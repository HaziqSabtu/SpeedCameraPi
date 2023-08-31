#include <Model/AppState.hpp>

AppState::AppState() {}

AppState::AppState(ModelPtr model) {
    cameraPanel = getCapturePanelState(model);
    calibrationPanel = getCalibrationPanelState(model);
    manualCalibrationPanel = getManualCalibrationPanelState(model);
    colorCalibrationPanel = getColorCalibrationPanelState(model);
    roiPanel = getRoiPanelState(model);
    resultPanel = getResultPanelState(model);
    trimDataPanel = getTrimDataPanelState(model);
}

PanelState AppState::getCameraStatusState(ModelPtr model) {
    return model->sessionData.isCaptureDataEmpty() ? PanelState::PANEL_NOT_OK
                                                   : PanelState::PANEL_OK;
}

PanelState AppState::getCalibrationStatusState(ModelPtr model) {
    return model->sessionData.isCalibrationDataEmpty()
               ? PanelState::PANEL_NOT_OK
               : PanelState::PANEL_OK;
}

PanelState AppState::getRoiStatusState(ModelPtr model) {
    return model->sessionData.isTrackingDataEmpty() ? PanelState::PANEL_NOT_OK
                                                    : PanelState::PANEL_OK;
}

CapturePanelState AppState::getCapturePanelState(ModelPtr model) {
    CapturePanelState ps;

    ps.captureStatusState = getCameraStatusState(model);
    ps.calibStatusState = getCalibrationStatusState(model);
    ps.roiStatusState = getRoiStatusState(model);

    ps.captureButtonState = getCaptureButtonState(model);
    ps.loadButtonState = getLoadButtonState(model);
    ps.replayButtonState = getReplayButtonState(model);
    ps.removeButtonState = getRemoveButtonState(model);
    ps.cameraButtonState = getCameraButtonState(model);

    ps.calibButtonState = getCPCalibrationButtonState(model);
    ps.calibRemoveButtonState = getCPCalibrationRemoveButtonState(model);

    ps.roiButtonState = getCPROIButtonState(model);
    ps.roiRemoveButtonState = getCPROIRemoveButtonState(model);

    ps.saveButtonState = getCPSaveButtonState(model);
    ps.trimButtonState = getCPTrimButtonState(model);
    ps.resetButtonState = getCPResetButtonState(model);

    ps.measureButtonState = getCPMeasureButtonState(model);

    return ps;
}

CalibrationPanelState AppState::getCalibrationPanelState(ModelPtr model) {
    CalibrationPanelState ps;

    ps.state = getCalibrationStatusState(model);

    ps.calibrationButtonState = getCalibrationButtonState(model);
    ps.calibrationCaptureButtonState = getCalibrationCaptureButtonState(model);
    ps.removeButtonState = getCalibrationRemoveButtonState(model);

    ps.toolStatusState = getCLToolStatusState(model);
    ps.selectPointButtonState = getSelectPointButtonState(model);
    ps.cancelCalibrationButtonState = getCancelCalibrationButtonState(model);
    ps.acceptCalibrationButtonState = getAcceptCalibrationButtonState(model);

    ps.previewStatusState = getCLPreviewStatusState(model);
    ps.prevCameraButtonState = getCLPrevCameraButtonState(model);
    ps.prevCaptureButtonState = getCLPrevCaptureButtonState(model);

    ps.otherStatusState = getCLOtherStatusState(model);
    ps.recalibrateColorButtonState = getRecalibrateColorButtonState(model);
    ps.manualCalibrationButtonState = getManualCalibrationButtonState(model);

    ps.okButtonState = getCLOKButtonState(model);
    ps.cancelButtonState = getCLCancelButtonState(model);

    return ps;
}

ManualCalibrationPanelState
AppState::getManualCalibrationPanelState(std::shared_ptr<SharedModel> model) {
    ManualCalibrationPanelState ps;

    ps.state = getCalibrationStatusState(model);

    ps.calibrationButtonState = getMCButtonState(model);
    ps.calibrationCaptureButtonState = getMCCaptureButtonState(model);
    ps.removeButtonState = getMCRemoveButtonState(model);

    ps.leftStatusState = getMCLeftStatusState(model);
    ps.selectLeftButtonState = getMCSelectLeftButtonState(model);
    ps.removeLeftButtonState = getMCRemoveLeftButtonState(model);

    ps.rightStatusState = getMCRightStatusState(model);
    ps.selectRightButtonState = getMCSelectRightButtonState(model);
    ps.removeRightButtonState = getMCRemoveRightButtonState(model);

    ps.previewStatusState = getMCPreviewStatusState(model);
    ps.prevCameraButtonState = getMCPrevCameraButtonState(model);
    ps.prevCaptureButtonState = getMCPrevCaptureButtonState(model);

    ps.okButtonState = getMCOKButtonState(model);
    ps.cancelButtonState = getMCCancelButtonState(model);

    return ps;
}

ColorCalibrationPanelState
AppState::getColorCalibrationPanelState(std::shared_ptr<SharedModel> model) {
    ColorCalibrationPanelState ps;

    ps.calibrationButtonState = getCCButtonState(model);
    ps.stopButtonState = getCCStopButtonState(model);
    ps.cameraButtonState = getCCCameraButtonState(model);
    ps.removeButtonState = getCCRemoveButtonState(model);

    ps.blueStatusState = getCCBlueStatusState(model);
    ps.selectBlueButtonState = getCCSelectBlueButtonState(model);
    ps.acceptBlueButtonState = getCCAcceptBlueButtonState(model);

    ps.yellowStatusState = getCCYellowStatusState(model);
    ps.selectYellowButtonState = getCCSelectYellowButtonState(model);
    ps.acceptYellowButtonState = getCCAcceptYellowButtonState(model);

    ps.saveButtonState = getCCSaveButtonState(model);
    ps.restoreButtonState = getCCRestoreButtonState(model);

    ps.okButtonState = getCCOKButtonState(model);
    ps.cancelButtonState = getCCCancelButtonState(model);

    return ps;
}

RoiPanelState AppState::getRoiPanelState(ModelPtr model) {
    RoiPanelState ps;

    ps.state = getRoiStatusState(model);

    ps.roiButtonState = getROIButtonState(model);
    ps.cameraButtonState = getROICameraButtonState(model);
    ps.removeButtonState = getROIRemoveButtonState(model);

    ps.roiToolsStatusState = getROIToolsStatusState(model);
    ps.acceptRoiButtonState = getROIAcceptRoiButtonState(model);
    ps.clearRoiButtonState = getROIClearRoiButtonState(model);

    ps.okButtonState = getROIOKButtonState(model);
    ps.cancelButtonState = getROICancelButtonState(model);

    return ps;
}

TrimDataPanelState AppState::getTrimDataPanelState(ModelPtr model) {
    TrimDataPanelState ps;

    ps.startButtonState = getTDStartButtonState(model);
    ps.replayButtonState = getTDReplayButtonState(model);
    ps.rangeButtonState = getTDRangeButtonState(model);
    ps.removeButtonState = getTDRemoveButtonState(model);

    ps.startStatusState = getTDStartStatusState(model);
    ps.incStartButtonState = getTDIncStartButtonState(model);
    ps.decStartButtonState = getTDDecStartButtonState(model);

    ps.endStatusState = getTDEndStatusState(model);
    ps.incEndButtonState = getTDIncEndButtonState(model);
    ps.decEndButtonState = getTDDecEndButtonState(model);

    ps.okButtonState = getTDOKButtonState(model);
    ps.cancelButtonState = getTDCancelButtonState(model);

    return ps;
}

ResultPanelState AppState::getResultPanelState(ModelPtr model) {
    ResultPanelState ps;

    ps.state = getRPResultStatusState(model);

    ps.resultButtonState = getRPResultButtonState(model);
    ps.previewButtonState = getRPPreviewButtonState(model);

    ps.previewStatusState = getRPPreviewStatusState(model);
    ps.boxButtonState = getRPBoxButtonState(model);
    ps.linesButtonState = getRPLinesButtonState(model);
    ps.lanesButtonState = getRPLanesButtonState(model);
    ps.replayButtonState = getRPReplayButtonState(model);

    return ps;
}

ButtonState AppState::getCaptureButtonState(ModelPtr model) {
    auto tc = model->getThreadController();
    if (!tc->isThreadNullptr(THREAD_LOAD_CAPTURE)) {
        return ButtonState::ACTIVE;
    }

    if (tc->isCapturePanelThreadRunning()) {
        return ButtonState::DISABLED;
    }

    if (model->sessionData.isCaptureDataEmpty()) {
        return ButtonState::NORMAL;
    }

    return ButtonState::DISABLED;
}

ButtonState AppState::getLoadButtonState(ModelPtr model) {
    auto tc = model->getThreadController();
    if (!tc->isThreadNullptr(THREAD_LOAD_FILE)) {
        return ButtonState::ACTIVE;
    }

    if (tc->isCapturePanelThreadRunning()) {
        return ButtonState::DISABLED;
    }

    if (model->sessionData.isCaptureDataEmpty()) {
        return ButtonState::NORMAL;
    }

    return ButtonState::DISABLED;
}

ButtonState AppState::getReplayButtonState(ModelPtr model) {
    auto tc = model->getThreadController();

    if (!tc->isThreadNullptr(THREAD_CAPTURE_PREVIEW)) {
        return ButtonState::ACTIVE;
    }

    if (tc->isCapturePanelThreadRunning()) {
        return ButtonState::DISABLED;
    }

    if (!model->sessionData.isCaptureDataEmpty()) {
        return ButtonState::NORMAL;
    }

    return ButtonState::DISABLED;
}

ButtonState AppState::getRemoveButtonState(ModelPtr model) {
    auto tc = model->getThreadController();

    if (tc->isCapturePanelThreadRunning()) {
        return ButtonState::DISABLED;
    }

    if (!model->sessionData.isCaptureDataEmpty()) {
        return ButtonState::NORMAL;
    }

    return ButtonState::DISABLED;
}

ButtonState AppState::getCameraButtonState(ModelPtr model) {

    auto tc = model->getThreadController();

    if (!tc->isThreadNullptr(THREAD_CAMERA_PREVIEW)) {
        return ButtonState::ON;
    }

    if (tc->isCapturePanelThreadRunning()) {
        return ButtonState::DISABLED;
    }

    if (!model->sessionData.isCaptureDataEmpty()) {
        return ButtonState::DISABLED;
    }

    return ButtonState::OFF;
}

ButtonState AppState::getCPCalibrationButtonState(ModelPtr model) {
    auto tc = model->getThreadController();

    if (tc->isCapturePanelThreadRunning()) {
        return ButtonState::DISABLED;
    }

    return ButtonState::NORMAL;
}

ButtonState AppState::getCPCalibrationRemoveButtonState(ModelPtr model) {
    auto tc = model->getThreadController();

    if (tc->isCapturePanelThreadRunning()) {
        return ButtonState::DISABLED;
    }

    if (model->sessionData.isCalibrationDataEmpty()) {
        return ButtonState::DISABLED;
    }

    return ButtonState::NORMAL;
}

ButtonState AppState::getCPROIButtonState(ModelPtr model) {
    auto tc = model->getThreadController();

    if (tc->isCapturePanelThreadRunning()) {
        return ButtonState::DISABLED;
    }

    if (model->sessionData.isCaptureDataEmpty()) {
        return ButtonState::DISABLED;
    }

    return ButtonState::NORMAL;
}

ButtonState AppState::getCPROIRemoveButtonState(ModelPtr model) {
    auto tc = model->getThreadController();

    if (tc->isCapturePanelThreadRunning()) {
        return ButtonState::DISABLED;
    }

    if (model->sessionData.isCaptureDataEmpty()) {
        return ButtonState::DISABLED;
    }

    auto data = model->getSessionData();
    if (data->isTrackingDataEmpty()) {
        return ButtonState::DISABLED;
    }

    return ButtonState::NORMAL;
}

ButtonState AppState::getCPSaveButtonState(ModelPtr model) {
    auto tc = model->getThreadController();

    if (tc->isCapturePanelThreadRunning()) {
        return ButtonState::DISABLED;
    }

    if (model->sessionData.isCaptureDataEmpty()) {
        return ButtonState::DISABLED;
    }

    return ButtonState::NORMAL;
}

ButtonState AppState::getCPTrimButtonState(ModelPtr model) {
    return getCPSaveButtonState(model);
}

ButtonState AppState::getCPResetButtonState(ModelPtr model) {
    return getCPSaveButtonState(model);
}

ButtonState AppState::getCPMeasureButtonState(ModelPtr model) {
    auto tc = model->getThreadController();

    if (tc->isCapturePanelThreadRunning()) {
        return ButtonState::DISABLED;
    }

    if (model->sessionData.isCaptureDataEmpty()) {
        return ButtonState::DISABLED;
    }

    if (model->sessionData.isCalibrationDataEmpty()) {
        return ButtonState::DISABLED;
    }

    if (model->sessionData.isTrackingDataEmpty()) {
        return ButtonState::DISABLED;
    }

    return ButtonState::NORMAL;
}

ButtonState AppState::getCalibrationButtonState(ModelPtr model) {
    auto tc = model->getThreadController();

    if (!tc->isThreadNullptr(THREAD_CALIBRATION_CAMERA)) {
        return ButtonState::ON;
    }

    if (!tc->isThreadNullptr(THREAD_CALIBRATION_CAPTURE)) {
        return ButtonState::DISABLED;
    }

    if (tc->isCalibPreviewThreadRunning()) {
        return ButtonState::DISABLED;
    }

    return ButtonState::OFF;
}

ButtonState AppState::getCalibrationCaptureButtonState(ModelPtr model) {
    auto tc = model->getThreadController();

    auto data = model->getSessionData();

    if (data->isCaptureDataEmpty()) {
        return ButtonState::DISABLED;
    }

    if (!tc->isThreadNullptr(THREAD_CALIBRATION_CAPTURE)) {
        return ButtonState::ON;
    }

    if (!tc->isThreadNullptr(THREAD_CALIBRATION_CAMERA)) {
        return ButtonState::DISABLED;
    }

    if (tc->isCalibPreviewThreadRunning()) {
        return ButtonState::DISABLED;
    }

    return ButtonState::OFF;
}

ButtonState AppState::getCalibrationRemoveButtonState(ModelPtr model) {
    auto tc = model->getThreadController();

    if (!tc->isThreadNullptr(THREAD_CALIBRATION_CAMERA)) {
        return ButtonState::DISABLED;
    }

    if (!tc->isThreadNullptr(THREAD_LOAD_CAPTURE)) {
        return ButtonState::DISABLED;
    }

    if (!tc->isThreadNullptr(THREAD_LOAD_FILE)) {
        return ButtonState::DISABLED;
    }

    if (!tc->isThreadNullptr(THREAD_CAMERA_PREVIEW)) {
        return ButtonState::DISABLED;
    }

    if (model->sessionData.isCalibrationDataEmpty()) {
        return ButtonState::DISABLED;
    }

    if (!model->sessionData.isCalibrationDataEmpty()) {
        return ButtonState::NORMAL;
    }

    return ButtonState::NORMAL;
}

PanelState AppState::getCLToolStatusState(ModelPtr model) {
    auto tc = model->getThreadController();

    if (!tc->isCalibrationThreadRunning()) {
        return PanelState::PANEL_HIDDEN;
    }

    return PanelState::PANEL_OK;
}

ButtonState AppState::getSelectPointButtonState(ModelPtr model) {
    auto tc = model->getThreadController();

    if (getCLToolStatusState(model) == PanelState::PANEL_HIDDEN) {
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

PanelState AppState::getCLPreviewStatusState(ModelPtr model) {
    auto tc = model->getThreadController();

    if (tc->isCalibrationThreadRunning()) {
        return PanelState::PANEL_HIDDEN;
    }

    return PanelState::PANEL_OK;
}

ButtonState AppState::getCLPrevCameraButtonState(ModelPtr model) {
    auto tc = model->getThreadController();

    if (!tc->isThreadNullptr(THREAD_CALIBRATION_PREVIEW_CAMERA)) {
        return ButtonState::ON;
    }

    if (!tc->isThreadNullptr(THREAD_CALIBRATION_CAMERA)) {
        return ButtonState::DISABLED;
    }

    return ButtonState::OFF;
}

ButtonState AppState::getCLPrevCaptureButtonState(ModelPtr model) {
    auto tc = model->getThreadController();

    if (getCLPreviewStatusState(model) == PanelState::PANEL_HIDDEN) {
        return ButtonState::DISABLED;
    }

    auto data = model->getSessionData();

    if (data->isCaptureDataEmpty()) {
        return ButtonState::DISABLED;
    }

    if (!tc->isThreadNullptr(THREAD_CALIBRATION_PREVIEW_CAMERA)) {
        return ButtonState::DISABLED;
    }

    if (tc->isThreadNullptr(THREAD_CALIBRATION_PREVIEW_CAPTURE)) {
        return ButtonState::OFF;
    }

    return ButtonState::ON;
}

PanelState AppState::getCLOtherStatusState(ModelPtr model) {
    return PanelState::PANEL_OK;
    // return getCLPreviewStatusState(model);
}

ButtonState AppState::getRecalibrateColorButtonState(ModelPtr model) {
    auto tc = model->getThreadController();

    if (getCLOtherStatusState(model) == PanelState::PANEL_HIDDEN) {
        return ButtonState::DISABLED;
    }

    // if (tc->isCalibPreviewThreadRunning()) {
    //     return ButtonState::DISABLED;
    // }

    // if (tc->isCalibrationThreadRunning()) {
    //     return ButtonState::DISABLED;
    // }

    return ButtonState::NORMAL;
}

ButtonState AppState::getManualCalibrationButtonState(ModelPtr model) {
    return getRecalibrateColorButtonState(model);
}

ButtonState AppState::getCLOKButtonState(ModelPtr model) {
    if (model->isSessionDataChanged()) {
        return ButtonState::NORMAL;
    }

    return ButtonState::DISABLED;
}

ButtonState AppState::getCLCancelButtonState(ModelPtr model) {
    return ButtonState::NORMAL;
}

ButtonState AppState::getMCButtonState(ModelPtr model) {
    auto tc = model->getThreadController();

    if (!tc->isThreadNullptr(THREAD_MANUAL_CALIBRATION_CAMERA)) {
        return ButtonState::ON;
    }

    if (!tc->isThreadNullptr(THREAD_MANUAL_CALIBRATION_CAPTURE)) {
        return ButtonState::DISABLED;
    }

    if (tc->isCalibPreviewThreadRunning()) {
        return ButtonState::DISABLED;
    }

    return ButtonState::OFF;
}

ButtonState AppState::getMCCaptureButtonState(ModelPtr model) {
    auto tc = model->getThreadController();

    auto data = model->getSessionData();

    if (data->isCaptureDataEmpty()) {
        return ButtonState::DISABLED;
    }

    if (!tc->isThreadNullptr(THREAD_MANUAL_CALIBRATION_CAPTURE)) {
        return ButtonState::ON;
    }

    if (!tc->isThreadNullptr(THREAD_CALIBRATION_PREVIEW_CAMERA)) {
        return ButtonState::DISABLED;
    }

    if (tc->isCalibPreviewThreadRunning()) {
        return ButtonState::DISABLED;
    }

    return ButtonState::OFF;
}

ButtonState AppState::getMCRemoveButtonState(ModelPtr model) {
    auto tc = model->getThreadController();

    if (tc->isManualCalibrationThreadRunning()) {
        return ButtonState::DISABLED;
    }

    if (tc->isCalibPreviewThreadRunning()) {
        return ButtonState::DISABLED;
    }

    if (!model->sessionData.isCalibrationDataEmpty()) {
        return ButtonState::NORMAL;
    }

    return ButtonState::DISABLED;
}

PanelState AppState::getMCLeftStatusState(ModelPtr model) {
    auto tc = model->getThreadController();

    if (!tc->isManualCalibrationThreadRunning()) {
        return PanelState::PANEL_HIDDEN;
    }

    auto data = model->getSessionData();
    auto calibData = data->getCalibrationData();

    Line line = calibData.lineLeft;

    if (line.isNull()) {
        return PanelState::PANEL_NOT_OK;
    }
    return PanelState::PANEL_OK;
}

ButtonState AppState::getMCSelectLeftButtonState(ModelPtr model) {
    auto tc = model->getThreadController();

    if (getMCLeftStatusState(model) == PanelState::PANEL_HIDDEN) {
        return ButtonState::DISABLED;
    }

    auto thread = tc->getRunningManualCalibrationThread();
    if (thread->getDirection() == ManualDirection::MANUAL_LEFT) {
        return ButtonState::ACTIVE;
    }

    return ButtonState::NORMAL;
}

ButtonState AppState::getMCRemoveLeftButtonState(ModelPtr model) {
    auto tc = model->getThreadController();

    if (getMCLeftStatusState(model) == PanelState::PANEL_HIDDEN) {
        return ButtonState::DISABLED;
    }

    return ButtonState::NORMAL;
}

PanelState AppState::getMCRightStatusState(ModelPtr model) {
    auto tc = model->getThreadController();

    if (!tc->isManualCalibrationThreadRunning()) {
        return PanelState::PANEL_HIDDEN;
    }

    auto calibData = model->sessionData.getCalibrationData();

    Line line = calibData.lineRight;

    if (line.isNull()) {
        return PanelState::PANEL_NOT_OK;
    }
    return PanelState::PANEL_OK;
}

ButtonState AppState::getMCSelectRightButtonState(ModelPtr model) {
    auto tc = model->getThreadController();

    if (getMCLeftStatusState(model) == PanelState::PANEL_HIDDEN) {
        return ButtonState::DISABLED;
    }

    auto thread = tc->getRunningManualCalibrationThread();
    if (thread->getDirection() == ManualDirection::MANUAL_RIGHT) {
        return ButtonState::ACTIVE;
    }

    return ButtonState::NORMAL;
}

ButtonState AppState::getMCRemoveRightButtonState(ModelPtr model) {
    auto tc = model->getThreadController();

    if (getMCLeftStatusState(model) == PanelState::PANEL_HIDDEN) {
        return ButtonState::DISABLED;
    }

    return ButtonState::NORMAL;
}

PanelState AppState::getMCPreviewStatusState(ModelPtr model) {
    auto tc = model->getThreadController();

    if (tc->getRunningManualCalibrationThread() != nullptr) {
        return PanelState::PANEL_HIDDEN;
    }

    return PanelState::PANEL_OK;
}

ButtonState AppState::getMCPrevCameraButtonState(ModelPtr model) {
    auto tc = model->getThreadController();

    if (getMCPreviewStatusState(model) == PanelState::PANEL_HIDDEN) {
        return ButtonState::DISABLED;
    }

    if (!tc->isThreadNullptr(THREAD_CALIBRATION_PREVIEW_CAPTURE)) {
        return ButtonState::DISABLED;
    }

    if (tc->isThreadNullptr(THREAD_CALIBRATION_PREVIEW_CAMERA)) {
        return ButtonState::OFF;
    }

    return ButtonState::ON;
}

ButtonState AppState::getMCPrevCaptureButtonState(ModelPtr model) {
    auto tc = model->getThreadController();

    if (getMCPreviewStatusState(model) == PanelState::PANEL_HIDDEN) {
        return ButtonState::DISABLED;
    }

    auto data = model->getSessionData();

    if (data->isCaptureDataEmpty()) {
        return ButtonState::DISABLED;
    }

    if (!tc->isThreadNullptr(THREAD_CALIBRATION_PREVIEW_CAMERA)) {
        return ButtonState::DISABLED;
    }

    if (tc->isThreadNullptr(THREAD_CALIBRATION_PREVIEW_CAPTURE)) {
        return ButtonState::OFF;
    }

    return ButtonState::ON;
}

ButtonState AppState::getMCOKButtonState(ModelPtr model) {
    if (model->isSessionDataChanged()) {
        return ButtonState::NORMAL;
    }

    return ButtonState::DISABLED;
}

ButtonState AppState::getMCCancelButtonState(ModelPtr model) {
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
    auto data = model->getSessionData();

    if (!data->isTrackingDataEmpty()) {
        return ButtonState::DISABLED;
    }

    auto tc = model->getThreadController();

    if (!tc->isThreadNullptr(THREAD_ROI_PREVIEW)) {
        return ButtonState::DISABLED;
    }

    if (!tc->isThreadNullptr(THREAD_ROI)) {
        return ButtonState::ON;
    }

    return ButtonState::OFF;
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
    if (data->isTrackingDataEmpty()) {
        return ButtonState::DISABLED;
    }

    return ButtonState::NORMAL;
}

PanelState AppState::getROIToolsStatusState(ModelPtr model) {
    auto tc = model->getThreadController();

    if (!tc->isThreadNullptr(THREAD_ROI)) {
        return PanelState::PANEL_OK;
    }

    return PanelState::PANEL_HIDDEN;
}

ButtonState AppState::getROIAcceptRoiButtonState(ModelPtr model) {
    auto tc = model->getThreadController();

    if (getROIToolsStatusState(model) == PanelState::PANEL_HIDDEN) {
        return ButtonState::DISABLED;
    }

    auto thread = tc->getRoiThread();

    if (!thread->isRectValid()) {
        return ButtonState::DISABLED;
    }

    return ButtonState::NORMAL;
}

ButtonState AppState::getROIClearRoiButtonState(ModelPtr model) {
    return getROIAcceptRoiButtonState(model);
}

ButtonState AppState::getROIOKButtonState(ModelPtr model) {
    if (model->isSessionDataChanged()) {
        return ButtonState::NORMAL;
    }

    return ButtonState::DISABLED;
}

ButtonState AppState::getROICancelButtonState(ModelPtr model) {
    return ButtonState::NORMAL;
}

ButtonState AppState::getTDStartButtonState(ModelPtr model) {
    auto tc = model->getThreadController();

    if (!tc->isThreadNullptr(THREAD_TRIM_DATA)) {
        return ButtonState::ON;
    }

    if (!tc->isThreadNullptr(THREAD_CAPTURE_PREVIEW)) {
        return ButtonState::DISABLED;
    }

    return ButtonState::OFF;
}

ButtonState AppState::getTDReplayButtonState(ModelPtr model) {
    auto tc = model->getThreadController();

    if (!tc->isThreadNullptr(THREAD_TRIM_DATA)) {
        return ButtonState::HIDDEN;
    }

    return ButtonState::NORMAL;
}

ButtonState AppState::getTDRangeButtonState(ModelPtr model) {
    auto tc = model->getThreadController();

    if (tc->isThreadNullptr(THREAD_TRIM_DATA)) {
        return ButtonState::HIDDEN;
    }

    auto thread = tc->getTrimDataThread();
    if (thread->getStatus() == TRIM_PREVIEW) {
        return ButtonState::DISABLED;
    }

    return ButtonState::NORMAL;
}

ButtonState AppState::getTDRemoveButtonState(ModelPtr model) {
    auto tc = model->getThreadController();

    if (!tc->isThreadNullptr(THREAD_TRIM_DATA)) {
        return ButtonState::DISABLED;
    }

    if (!tc->isThreadNullptr(THREAD_CAPTURE_PREVIEW)) {
        return ButtonState::DISABLED;
    }

    if (model->isSessionDataChanged()) {
        return ButtonState::NORMAL;
    }

    return ButtonState::DISABLED;
}

PanelState AppState::getTDStartStatusState(ModelPtr model) {
    auto tc = model->getThreadController();

    if (!tc->isThreadNullptr(THREAD_TRIM_DATA)) {
        return PanelState::PANEL_OK;
    }

    return PanelState::PANEL_HIDDEN;
}

ButtonState AppState::getTDIncStartButtonState(ModelPtr model) {
    auto tc = model->getThreadController();

    if (getTDStartStatusState(model) == PanelState::PANEL_HIDDEN) {
        return ButtonState::DISABLED;
    }

    if (tc->isThreadNullptr(THREAD_TRIM_DATA)) {
        return ButtonState::DISABLED;
    }

    auto thread = tc->getTrimDataThread();

    if (thread->getStatus() == TRIM_PREVIEW) {
        return ButtonState::DISABLED;
    }

    if (!thread->isStartIncrementable()) {
        return ButtonState::DISABLED;
    }

    return ButtonState::NORMAL;
}

ButtonState AppState::getTDDecStartButtonState(ModelPtr model) {
    auto tc = model->getThreadController();

    if (getTDStartStatusState(model) == PanelState::PANEL_HIDDEN) {
        return ButtonState::DISABLED;
    }

    if (tc->isThreadNullptr(THREAD_TRIM_DATA)) {
        return ButtonState::DISABLED;
    }

    auto thread = tc->getTrimDataThread();

    if (thread->getStatus() == TRIM_PREVIEW) {
        return ButtonState::DISABLED;
    }

    if (!thread->isStartDecrementable()) {
        return ButtonState::DISABLED;
    }

    return ButtonState::NORMAL;
}

PanelState AppState::getTDEndStatusState(ModelPtr model) {
    return getTDStartStatusState(model);
}

ButtonState AppState::getTDIncEndButtonState(ModelPtr model) {
    auto tc = model->getThreadController();

    if (getTDEndStatusState(model) == PanelState::PANEL_HIDDEN) {
        return ButtonState::DISABLED;
    }

    if (tc->isThreadNullptr(THREAD_TRIM_DATA)) {
        return ButtonState::DISABLED;
    }

    auto thread = tc->getTrimDataThread();

    if (thread->getStatus() == TRIM_PREVIEW) {
        return ButtonState::DISABLED;
    }

    if (!thread->isEndIncrementable()) {
        return ButtonState::DISABLED;
    }

    return ButtonState::NORMAL;
}

ButtonState AppState::getTDDecEndButtonState(ModelPtr model) {
    auto tc = model->getThreadController();

    if (getTDEndStatusState(model) == PanelState::PANEL_HIDDEN) {
        return ButtonState::DISABLED;
    }

    if (tc->isThreadNullptr(THREAD_TRIM_DATA)) {
        return ButtonState::DISABLED;
    }

    auto thread = tc->getTrimDataThread();

    if (thread->getStatus() == TRIM_PREVIEW) {
        return ButtonState::DISABLED;
    }

    if (!thread->isEndDecrementable()) {
        return ButtonState::DISABLED;
    }

    return ButtonState::NORMAL;
}

ButtonState AppState::getTDOKButtonState(ModelPtr model) {
    if (model->isSessionDataChanged()) {
        return ButtonState::NORMAL;
    }

    return ButtonState::DISABLED;
}

ButtonState AppState::getTDCancelButtonState(ModelPtr model) {
    return ButtonState::NORMAL;
}

PanelState AppState::getRPResultStatusState(ModelPtr model) { return PANEL_OK; }

ButtonState AppState::getRPResultButtonState(ModelPtr model) {
    auto tc = model->getThreadController();

    if (!tc->isThreadNullptr(THREAD_RESULT_PREVIEW)) {
        return ButtonState::DISABLED;
    }

    if (!tc->isThreadNullptr(THREAD_PROCESS)) {
        return ButtonState::ACTIVE;
    }

    return ButtonState::NORMAL;
}

ButtonState AppState::getRPPreviewButtonState(ModelPtr model) {
    auto tc = model->getThreadController();

    if (!tc->isThreadNullptr(THREAD_PROCESS)) {
        return ButtonState::DISABLED;
    }

    if (!tc->isThreadNullptr(THREAD_RESULT_PREVIEW)) {
        return ButtonState::ON;
    }

    return ButtonState::OFF;
}

PanelState AppState::getRPPreviewStatusState(ModelPtr model) {
    auto tc = model->getThreadController();

    if (!tc->isThreadNullptr(THREAD_RESULT_PREVIEW)) {
        return PanelState::PANEL_OK;
    }

    return PanelState::PANEL_HIDDEN;
}

ButtonState AppState::getRPBoxButtonState(ModelPtr model) {
    auto tc = model->getThreadController();

    if (getRPPreviewStatusState(model) == PanelState::PANEL_HIDDEN) {
        return ButtonState::DISABLED;
    }

    auto thread = tc->getResultPreviewThread();

    if (thread->GetShowBox() == true) {
        return ButtonState::ON;
    }

    return ButtonState::OFF;
}
ButtonState AppState::getRPLinesButtonState(ModelPtr model) {
    auto tc = model->getThreadController();

    if (getRPPreviewStatusState(model) == PanelState::PANEL_HIDDEN) {
        return ButtonState::DISABLED;
    }

    auto thread = tc->getResultPreviewThread();

    if (thread->GetShowIntersection() == true) {
        return ButtonState::ON;
    }

    return ButtonState::OFF;
}
ButtonState AppState::getRPLanesButtonState(ModelPtr model) {
    auto tc = model->getThreadController();

    if (getRPPreviewStatusState(model) == PanelState::PANEL_HIDDEN) {
        return ButtonState::DISABLED;
    }

    auto thread = tc->getResultPreviewThread();

    if (thread->GetShowLanes() == true) {
        return ButtonState::ON;
    }

    return ButtonState::OFF;
}

ButtonState AppState::getRPReplayButtonState(ModelPtr model) {
    auto tc = model->getThreadController();

    if (getRPPreviewStatusState(model) == PanelState::PANEL_HIDDEN) {
        return ButtonState::DISABLED;
    }

    return ButtonState::NORMAL;
}
