#include "Model/SessionData.hpp"
#include "Thread/Thread_HorizontalCalibrationCamera.hpp"
#include "Thread/Thread_ID.hpp"
#include <Model/AppState.hpp>

AppState::AppState() {}

AppState::AppState(ModelPtr model) {
    capturePanel = getCapturePanelState(model);
    calibrationPanel = getCalibrationPanelState(model);
    manualCalibrationPanel = getManualCalibrationPanelState(model);
    horizontalCalibrationPanel = getHorizontalCalibrationPanelState(model);
    colorCalibrationPanel = getColorCalibrationPanelState(model);
    roiPanel = getRoiPanelState(model);
    resultPanel = getResultPanelState(model);
    trimDataPanel = getTrimDataPanelState(model);
}

CapturePanelState AppState::getCapturePanelState(ModelPtr model) {
    CapturePanelState ps;

    ps.captureStatusState = getCPCaptureStatusState(model);
    ps.captureButtonState = getCPCaptureButtonState(model);
    ps.loadButtonState = getCPLoadButtonState(model);
    ps.replayButtonState = getCPReplayButtonState(model);
    ps.removeButtonState = getCPRemoveButtonState(model);
    ps.cameraButtonState = getCPCameraButtonState(model);

    ps.calibStatusState = getCPCalibrationStatusState(model);
    ps.horCalibStatusState = getCPHorCalibrationStatusState(model);
    ps.calibButtonState = getCPCalibrationButtonState(model);
    ps.calibRemoveButtonState = getCPCalibrationRemoveButtonState(model);

    ps.roiStatusState = getCPRoiStatusState(model);
    ps.roiButtonState = getCPROIButtonState(model);
    ps.roiRemoveButtonState = getCPROIRemoveButtonState(model);

    ps.toolsStatusState = getCPToolsStatusState(model);
    ps.saveButtonState = getCPSaveButtonState(model);
    ps.trimButtonState = getCPTrimButtonState(model);
    ps.resetButtonState = getCPResetButtonState(model);

    ps.measureButtonState = getCPMeasureButtonState(model);

    return ps;
}

CalibrationPanelState AppState::getCalibrationPanelState(ModelPtr model) {
    CalibrationPanelState ps;

    ps.state = getCLStatusState(model);

    ps.calibrationButtonState = getCLCalibrationButtonState(model);
    ps.previewButtonState = getCLPreviewButtonState(model);
    ps.manualCalibrationButtonState = getCLManualCalibrationButtonState(model);
    ps.removeButtonState = getCLRemoveButtonState(model);

    ps.toolStatusState = getCLToolStatusState(model);
    ps.selectPointButtonState = getCLSelectPointButtonState(model);
    ps.cancelCalibrationButtonState = getCLCancelCalibrationButtonState(model);
    ps.acceptCalibrationButtonState = getCLAcceptCalibrationButtonState(model);

    ps.otherStatusState = getCLOtherStatusState(model);
    ps.recalibrateColorButtonState = getCLRecalibrateColorButtonState(model);

    ps.okButtonState = getCLOKButtonState(model);
    ps.cancelButtonState = getCLCancelButtonState(model);

    return ps;
}

ManualCalibrationPanelState
AppState::getManualCalibrationPanelState(std::shared_ptr<SharedModel> model) {
    ManualCalibrationPanelState ps;

    ps.state = getMCStatusState(model);

    ps.calibrationButtonState = getMCButtonState(model);
    ps.previewButtonState = getMCPreviewButtonState(model);
    ps.removeButtonState = getMCRemoveButtonState(model);

    ps.leftStatusState = getMCLeftStatusState(model);
    ps.selectLeftButtonState = getMCSelectLeftButtonState(model);
    ps.removeLeftButtonState = getMCRemoveLeftButtonState(model);

    ps.rightStatusState = getMCRightStatusState(model);
    ps.selectRightButtonState = getMCSelectRightButtonState(model);
    ps.removeRightButtonState = getMCRemoveRightButtonState(model);

    ps.okButtonState = getMCOKButtonState(model);
    ps.cancelButtonState = getMCCancelButtonState(model);

    return ps;
}

HorizontalCalibrationPanelState
AppState::getHorizontalCalibrationPanelState(ModelPtr model) {
    HorizontalCalibrationPanelState ps;

    ps.state = getHCStatusState(model);

    ps.calibrationButtonState = getHCButtonState(model);
    ps.previewButtonState = getHCPreviewButtonState(model);
    ps.removeButtonState = getHCRemoveButtonState(model);

    ps.topStatusState = getHCTopStatusState(model);
    ps.selectTopButtonState = getHCSelectTopButtonState(model);
    ps.removeTopButtonState = getHCRemoveTopButtonState(model);

    ps.bottomStatusState = getHCBottomStatusState(model);
    ps.selectBottomButtonState = getHCSelectBottomButtonState(model);
    ps.removeBottomButtonState = getHCRemoveBottomButtonState(model);

    ps.okButtonState = getHCOKButtonState(model);
    ps.cancelButtonState = getHCCancelButtonState(model);

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

    ps.otherStatusState = getCCOtherStatusState(model);
    ps.saveButtonState = getCCSaveButtonState(model);
    ps.restoreButtonState = getCCRestoreButtonState(model);

    ps.okButtonState = getCCOKButtonState(model);
    ps.cancelButtonState = getCCCancelButtonState(model);

    return ps;
}

RoiPanelState AppState::getRoiPanelState(ModelPtr model) {
    RoiPanelState ps;

    ps.state = getROIStatusState(model);
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

    ps.procLaneButtonState = getRPProcLaneButtonState(model);
    ps.procDistButtonState = getRPProcDistButtonState(model);
    ps.previewButtonState = getRPPreviewButtonState(model);

    ps.previewStatusState = getRPPreviewStatusState(model);
    ps.boxButtonState = getRPBoxButtonState(model);
    ps.linesButtonState = getRPLinesButtonState(model);
    ps.lanesButtonState = getRPLanesButtonState(model);
    ps.replayButtonState = getRPReplayButtonState(model);

    ps.speedStatusState = getRPSpeedStatusState(model);

    ps.backButtonState = getRPBackButtonState(model);

    return ps;
}

PanelState AppState::getCPCaptureStatusState(ModelPtr model) {
    return model->sessionData.isCaptureDataEmpty() ? PanelState::PANEL_NOT_OK
                                                   : PanelState::PANEL_OK;
}

ButtonState AppState::getCPCaptureButtonState(ModelPtr model) {
    auto tc = model->getThreadController();
    if (!tc->isThreadNullptr(THREAD_LOAD_CAPTURE)) {
        return ButtonState::ACTIVE;
    }

    if (!model->sessionData.isCaptureDataEmpty()) {
        return ButtonState::HIDDEN;
    }

    if (tc->isCapturePanelThreadRunning()) {
        return ButtonState::DISABLED;
    }

    if (model->sessionData.isCaptureDataEmpty()) {
        return ButtonState::NORMAL;
    }

    return ButtonState::HIDDEN;
}

ButtonState AppState::getCPLoadButtonState(ModelPtr model) {
    auto tc = model->getThreadController();
    if (!tc->isThreadNullptr(THREAD_LOAD_FILE)) {
        return ButtonState::ACTIVE;
    }

    if (!model->sessionData.isCaptureDataEmpty()) {
        return ButtonState::HIDDEN;
    }

    if (tc->isCapturePanelThreadRunning()) {
        return ButtonState::DISABLED;
    }

    if (model->sessionData.isCaptureDataEmpty()) {
        return ButtonState::NORMAL;
    }

    return ButtonState::HIDDEN;
}

ButtonState AppState::getCPReplayButtonState(ModelPtr model) {
    auto tc = model->getThreadController();

    if (!tc->isThreadNullptr(THREAD_CAPTURE_PREVIEW)) {
        return ButtonState::ACTIVE;
    }

    if (model->sessionData.isCaptureDataEmpty()) {
        return ButtonState::HIDDEN;
    }

    if (tc->isCapturePanelThreadRunning()) {
        return ButtonState::DISABLED;
    }

    if (!model->sessionData.isCaptureDataEmpty()) {
        return ButtonState::NORMAL;
    }

    return ButtonState::HIDDEN;
}

ButtonState AppState::getCPRemoveButtonState(ModelPtr model) {
    auto tc = model->getThreadController();

    if (tc->isCapturePanelThreadRunning()) {
        return ButtonState::DISABLED;
    }

    if (model->sessionData.isCaptureDataEmpty()) {
        return ButtonState::HIDDEN;
    }

    if (!model->sessionData.isCaptureDataEmpty()) {
        return ButtonState::NORMAL;
    }

    return ButtonState::HIDDEN;
}

ButtonState AppState::getCPCameraButtonState(ModelPtr model) {

    auto tc = model->getThreadController();

    if (!tc->isThreadNullptr(THREAD_CAMERA_PREVIEW)) {
        return ButtonState::ON;
    }

    if (!model->sessionData.isCaptureDataEmpty()) {
        return ButtonState::HIDDEN;
    }

    if (tc->isCapturePanelThreadRunning()) {
        return ButtonState::DISABLED;
    }

    return ButtonState::OFF;
}

PanelState AppState::getCPCalibrationStatusState(ModelPtr model) {
    auto data = model->getSessionData();

    if (data->getMode() != MODE_LANE) {
        return PanelState::PANEL_HIDDEN;
    }

    if (data->isCalibrationDataEmpty()) {
        return PanelState::PANEL_NOT_OK;
    }

    return PanelState::PANEL_OK;
}

PanelState AppState::getCPHorCalibrationStatusState(ModelPtr model) {
    auto data = model->getSessionData();

    if (data->getMode() != MODE_DISTANCE) {
        return PanelState::PANEL_HIDDEN;
    }

    if (data->isCalibrationDataEmpty()) {
        return PanelState::PANEL_NOT_OK;
    }

    return PanelState::PANEL_OK;
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

PanelState AppState::getCPRoiStatusState(ModelPtr model) {
    return model->sessionData.isTrackingDataEmpty() ? PanelState::PANEL_NOT_OK
                                                    : PanelState::PANEL_OK;
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

PanelState AppState::getCPToolsStatusState(ModelPtr model) {
    auto data = model->getSessionData();

    if (data->isCaptureDataEmpty()) {
        return PanelState::PANEL_HIDDEN;
    }

    return PanelState::PANEL_OK;
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

PanelState AppState::getCLStatusState(ModelPtr model) {
    return model->sessionData.isCalibrationDataEmpty()
               ? PanelState::PANEL_NOT_OK
               : PanelState::PANEL_OK;
}

ButtonState AppState::getCLCalibrationButtonState(ModelPtr model) {
    auto tc = model->getThreadController();

    if (tc->isCalibrationThreadRunning()) {
        return ButtonState::ON;
    }

    auto data = model->getSessionData();
    if (!data->isCalibrationDataEmpty()) {
        return ButtonState::HIDDEN;
    }

    return ButtonState::OFF;
}

ButtonState AppState::getCLRemoveButtonState(ModelPtr model) {
    auto tc = model->getThreadController();

    if (model->sessionData.isCalibrationDataEmpty()) {
        return ButtonState::HIDDEN;
    }

    if (tc->isCalibrationThreadRunning()) {
        return ButtonState::HIDDEN;
    }

    if (tc->isCalibPreviewThreadRunning()) {
        return ButtonState::DISABLED;
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

ButtonState AppState::getCLSelectPointButtonState(ModelPtr model) {
    auto tc = model->getThreadController();

    if (getCLToolStatusState(model) == PanelState::PANEL_HIDDEN) {
        return ButtonState::DISABLED;
    }

    return ButtonState::NORMAL;
}

ButtonState AppState::getCLCancelCalibrationButtonState(ModelPtr model) {
    return getCLSelectPointButtonState(model);
}

ButtonState AppState::getCLAcceptCalibrationButtonState(ModelPtr model) {
    return getCLSelectPointButtonState(model);
}

ButtonState AppState::getCLPreviewButtonState(ModelPtr model) {
    auto tc = model->getThreadController();

    auto data = model->getSessionData();
    if (data->isCalibrationDataEmpty()) {
        return ButtonState::HIDDEN;
    }

    if (tc->isCalibrationThreadRunning()) {
        return ButtonState::HIDDEN;
    }

    if (tc->isCalibPreviewThreadRunning()) {
        return ButtonState::ON;
    }

    return ButtonState::OFF;
}

PanelState AppState::getCLOtherStatusState(ModelPtr model) {
    auto tc = model->getThreadController();

    if (tc->isCalibrationThreadRunning()) {
        return PanelState::PANEL_HIDDEN;
    }

    auto data = model->getSessionData();
    if (!data->isCalibrationDataEmpty()) {
        return PanelState::PANEL_HIDDEN;
    }

    return PanelState::PANEL_OK;
}

ButtonState AppState::getCLRecalibrateColorButtonState(ModelPtr model) {
    auto tc = model->getThreadController();

    if (getCLOtherStatusState(model) == PanelState::PANEL_HIDDEN) {
        return ButtonState::DISABLED;
    }

    return ButtonState::NORMAL;
}

ButtonState AppState::getCLManualCalibrationButtonState(ModelPtr model) {
    auto tc = model->getThreadController();

    if (tc->isCalibrationThreadRunning()) {
        return ButtonState::HIDDEN;
    }

    auto data = model->getSessionData();
    if (!data->isCalibrationDataEmpty()) {
        return ButtonState::HIDDEN;
    }

    return ButtonState::NORMAL;
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

PanelState AppState::getMCStatusState(ModelPtr model) {
    return model->sessionData.isCalibrationDataEmpty()
               ? PanelState::PANEL_NOT_OK
               : PanelState::PANEL_OK;
}

ButtonState AppState::getMCButtonState(ModelPtr model) {
    auto tc = model->getThreadController();

    if (tc->isManualCalibrationThreadRunning()) {
        return ButtonState::ON;
    }

    auto data = model->getSessionData();
    if (!data->isCalibrationDataEmpty()) {
        return ButtonState::HIDDEN;
    }

    return ButtonState::OFF;
}

ButtonState AppState::getMCRemoveButtonState(ModelPtr model) {
    auto tc = model->getThreadController();

    if (model->sessionData.isCalibrationDataEmpty()) {
        return ButtonState::HIDDEN;
    }

    if (tc->isManualCalibrationThreadRunning()) {
        return ButtonState::HIDDEN;
    }

    if (tc->isCalibPreviewThreadRunning()) {
        return ButtonState::DISABLED;
    }

    return ButtonState::NORMAL;
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

ButtonState AppState::getMCPreviewButtonState(ModelPtr model) {
    auto tc = model->getThreadController();

    auto data = model->getSessionData();
    if (data->isCalibrationDataEmpty()) {
        return ButtonState::HIDDEN;
    }

    if (tc->isManualCalibrationThreadRunning()) {
        return ButtonState::HIDDEN;
    }

    if (tc->isCalibPreviewThreadRunning()) {
        return ButtonState::ON;
    }

    return ButtonState::OFF;
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

PanelState AppState::getHCStatusState(ModelPtr model) {
    return model->sessionData.isCalibrationDataEmpty()
               ? PanelState::PANEL_NOT_OK
               : PanelState::PANEL_OK;
}

ButtonState AppState::getHCButtonState(ModelPtr model) {
    auto tc = model->getThreadController();

    if (tc->isHorizontalCalibrationThreadRunning()) {
        return ButtonState::ON;
    }

    auto data = model->getSessionData();
    if (!data->isCalibrationDataEmpty()) {
        return ButtonState::HIDDEN;
    }

    return ButtonState::OFF;
}

ButtonState AppState::getHCRemoveButtonState(ModelPtr model) {
    auto tc = model->getThreadController();

    if (model->sessionData.isCalibrationDataEmpty()) {
        return ButtonState::HIDDEN;
    }

    if (tc->isManualCalibrationThreadRunning()) {
        return ButtonState::HIDDEN;
    }

    if (tc->isCalibPreviewThreadRunning()) {
        return ButtonState::DISABLED;
    }

    return ButtonState::NORMAL;
}

PanelState AppState::getHCTopStatusState(ModelPtr model) {
    auto tc = model->getThreadController();

    if (!tc->isHorizontalCalibrationThreadRunning()) {
        return PanelState::PANEL_HIDDEN;
    }

    auto data = model->getSessionData();
    auto calibData = data->getCalibrationData();

    Line line = calibData.lineRight;

    if (line.isNull()) {
        return PanelState::PANEL_NOT_OK;
    }
    return PanelState::PANEL_OK;
}

ButtonState AppState::getHCSelectTopButtonState(ModelPtr model) {
    auto tc = model->getThreadController();

    if (getHCTopStatusState(model) == PanelState::PANEL_HIDDEN) {
        return ButtonState::DISABLED;
    }

    auto thread = tc->getRunningHorizontalCalibrationThread();
    if (thread->getDirection() == HorizontalDirection::HORIZONTAL_TOP) {
        return ButtonState::ACTIVE;
    }

    return ButtonState::NORMAL;
}

ButtonState AppState::getHCRemoveTopButtonState(ModelPtr model) {
    auto tc = model->getThreadController();

    if (getHCTopStatusState(model) == PanelState::PANEL_HIDDEN) {
        return ButtonState::DISABLED;
    }

    return ButtonState::NORMAL;
}

PanelState AppState::getHCBottomStatusState(ModelPtr model) {
    auto tc = model->getThreadController();

    if (!tc->isHorizontalCalibrationThreadRunning()) {
        return PanelState::PANEL_HIDDEN;
    }

    auto calibData = model->sessionData.getCalibrationData();

    Line line = calibData.lineLeft;

    if (line.isNull()) {
        return PanelState::PANEL_NOT_OK;
    }
    return PanelState::PANEL_OK;
}

ButtonState AppState::getHCSelectBottomButtonState(ModelPtr model) {
    auto tc = model->getThreadController();

    if (getHCBottomStatusState(model) == PanelState::PANEL_HIDDEN) {
        return ButtonState::DISABLED;
    }

    auto thread = tc->getRunningHorizontalCalibrationThread();
    if (thread->getDirection() == HorizontalDirection::HORIZONTAL_BOTTOM) {
        return ButtonState::ACTIVE;
    }

    return ButtonState::NORMAL;
}

ButtonState AppState::getHCRemoveBottomButtonState(ModelPtr model) {
    auto tc = model->getThreadController();

    if (getHCBottomStatusState(model) == PanelState::PANEL_HIDDEN) {
        return ButtonState::DISABLED;
    }

    return ButtonState::NORMAL;
}

ButtonState AppState::getHCPreviewButtonState(ModelPtr model) {
    auto tc = model->getThreadController();

    auto data = model->getSessionData();
    if (data->isCalibrationDataEmpty()) {
        return ButtonState::HIDDEN;
    }

    if (tc->isHorizontalCalibrationThreadRunning()) {
        return ButtonState::HIDDEN;
    }

    if (tc->isCalibPreviewThreadRunning()) {
        return ButtonState::ON;
    }

    return ButtonState::OFF;
}

ButtonState AppState::getHCOKButtonState(ModelPtr model) {
    if (model->isSessionDataChanged()) {
        return ButtonState::NORMAL;
    }

    return ButtonState::DISABLED;
}

ButtonState AppState::getHCCancelButtonState(ModelPtr model) {
    return ButtonState::NORMAL;
}

ButtonState AppState::getCCButtonState(ModelPtr model) {
    auto tc = model->getThreadController();

    if (!tc->isThreadNullptr(THREAD_COLOR_CALIBRATION_PREVIEW)) {
        return ButtonState::HIDDEN;
    }

    if (!tc->isThreadNullptr(THREAD_COLOR_CALIBRATION)) {
        return ButtonState::ON;
    }

    return ButtonState::OFF;
}

ButtonState AppState::getCCStopButtonState(ModelPtr model) {
    // auto tc = model->getThreadController();

    // if (!tc->isThreadNullptr(THREAD_COLOR_CALIBRATION)) {
    //     return ButtonState::NORMAL;
    // }

    return ButtonState::HIDDEN;
}

ButtonState AppState::getCCCameraButtonState(ModelPtr model) {
    auto tc = model->getThreadController();

    if (!tc->isThreadNullptr(THREAD_COLOR_CALIBRATION)) {
        return ButtonState::HIDDEN;
    }

    if (!tc->isThreadNullptr(THREAD_COLOR_CALIBRATION_PREVIEW)) {
        return ButtonState::ON;
    }

    return ButtonState::OFF;
}

ButtonState AppState::getCCRemoveButtonState(ModelPtr model) {
    // auto tc = model->getThreadController();

    // if (!tc->isThreadNullptr(THREAD_COLOR_CALIBRATION)) {
    //     return ButtonState::DISABLED;
    // }

    // if (!tc->isThreadNullptr(THREAD_COLOR_CALIBRATION_PREVIEW)) {
    //     return ButtonState::DISABLED;
    // }

    // auto ccExtraModel = model->getCCExtraModel();

    // if (ccExtraModel->isBlueCalibrated() ||
    //     ccExtraModel->isYellowCalibrated()) {
    //     return ButtonState::NORMAL;
    // }

    return ButtonState::HIDDEN;
}

PanelState AppState::getCCBlueStatusState(ModelPtr model) {
    auto tc = model->getThreadController();

    if (tc->isThreadNullptr(THREAD_COLOR_CALIBRATION)) {
        return PanelState::PANEL_HIDDEN;
    }

    auto thread = tc->getColorCalibrationThread();
    if (thread->isBlueRangeDefined()) {
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

    auto thread = tc->getColorCalibrationThread();
    if (thread->getColorCalibrationType() ==
        ColorCalibrationType::COLOR_CALIBRATION_BLUE) {
        return ButtonState::ACTIVE;
    }

    return ButtonState::NORMAL;
}

ButtonState AppState::getCCAcceptBlueButtonState(ModelPtr model) {
    auto tc = model->getThreadController();

    if (tc->isThreadNullptr(THREAD_COLOR_CALIBRATION)) {
        return ButtonState::HIDDEN;
    }

    auto thread = tc->getColorCalibrationThread();
    if (!thread->isBlueRangeDefined()) {
        return ButtonState::DISABLED;
    }

    return ButtonState::NORMAL;
}

PanelState AppState::getCCYellowStatusState(ModelPtr model) {
    auto tc = model->getThreadController();

    if (tc->isThreadNullptr(THREAD_COLOR_CALIBRATION)) {
        return PanelState::PANEL_HIDDEN;
    }

    auto thread = tc->getColorCalibrationThread();
    if (thread->isYellowRangeDefined()) {
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

    auto thread = tc->getColorCalibrationThread();
    if (thread->getColorCalibrationType() ==
        ColorCalibrationType::COLOR_CALIBRATION_YELLOW) {
        return ButtonState::ACTIVE;
    }

    return ButtonState::NORMAL;
}

ButtonState AppState::getCCAcceptYellowButtonState(ModelPtr model) {
    auto tc = model->getThreadController();

    if (tc->isThreadNullptr(THREAD_COLOR_CALIBRATION)) {
        return ButtonState::HIDDEN;
    }

    auto thread = tc->getColorCalibrationThread();
    if (!thread->isYellowRangeDefined()) {
        return ButtonState::DISABLED;
    }

    return ButtonState::NORMAL;
}

PanelState AppState::getCCOtherStatusState(ModelPtr model) {
    auto tc = model->getThreadController();

    if (!tc->isThreadNullptr(THREAD_COLOR_CALIBRATION)) {
        return PanelState::PANEL_HIDDEN;
    }

    if (!tc->isThreadNullptr(THREAD_COLOR_CALIBRATION_PREVIEW)) {
        return PanelState::PANEL_HIDDEN;
    }

    return PanelState::PANEL_OK;
}

ButtonState AppState::getCCSaveButtonState(ModelPtr model) {
    // auto tc = model->getThreadController();

    // if (!tc->isThreadNullptr(THREAD_COLOR_CALIBRATION)) {
    //     return ButtonState::DISABLED;
    // }

    // if (!tc->isThreadNullptr(THREAD_COLOR_CALIBRATION_PREVIEW)) {
    //     return ButtonState::DISABLED;
    // }

    // auto ccExtraModel = model->getCCExtraModel();

    // if (!ccExtraModel->isBlueCalibrated()) {
    //     return ButtonState::DISABLED;
    // }

    // if (!ccExtraModel->isYellowCalibrated()) {
    //     return ButtonState::DISABLED;
    // }

    return ButtonState::HIDDEN;
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
    return ButtonState::NORMAL;
}

ButtonState AppState::getCCCancelButtonState(ModelPtr model) {
    return ButtonState::NORMAL;
}

PanelState AppState::getROIStatusState(ModelPtr model) {
    return model->sessionData.isTrackingDataEmpty() ? PanelState::PANEL_NOT_OK
                                                    : PanelState::PANEL_OK;
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
    auto tc = model->getThreadController();

    if (!tc->isThreadNullptr(THREAD_TRIM_DATA)) {
        return ButtonState::NORMAL;
    }

    return ButtonState::DISABLED;
}

ButtonState AppState::getTDCancelButtonState(ModelPtr model) {
    return ButtonState::NORMAL;
}

PanelState AppState::getRPResultStatusState(ModelPtr model) {
    auto data = model->getSessionData();
    if (data->isResultDataEmpty()) {
        return PanelState::PANEL_NOT_OK;
    }
    return PanelState::PANEL_OK;
}

ButtonState AppState::getRPProcLaneButtonState(ModelPtr model) {
    auto tc = model->getThreadController();

    auto data = model->getSessionData();
    if (!data->isResultDataEmpty()) {
        return ButtonState::HIDDEN;
    }

    if (!tc->isThreadNullptr(THREAD_PROCESS)) {
        return ButtonState::ACTIVE;
    }

    return ButtonState::NORMAL;
}

ButtonState AppState::getRPProcDistButtonState(ModelPtr model) {
    auto tc = model->getThreadController();

    auto data = model->getSessionData();
    if (data->isResultDataEmpty()) {
        return ButtonState::HIDDEN;
    }

    if (!tc->isThreadNullptr(THREAD_RESULT_PREVIEW)) {
        return ButtonState::HIDDEN;
    }

    if (!tc->isThreadNullptr(THREAD_PROCESS)) {
        return ButtonState::ACTIVE;
    }

    return ButtonState::NORMAL;
}

ButtonState AppState::getRPPreviewButtonState(ModelPtr model) {
    auto tc = model->getThreadController();

    auto data = model->getSessionData();
    if (data->isResultDataEmpty()) {
        return ButtonState::HIDDEN;
    }

    if (!tc->isThreadNullptr(THREAD_PROCESS)) {
        return ButtonState::HIDDEN;
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

    auto data = model->getSessionData();
    if (data->getMode() == Mode::MODE_DISTANCE) {
        return ButtonState::HIDDEN;
    }

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

PanelState AppState::getRPSpeedStatusState(ModelPtr model) {
    auto data = model->getSessionData();

    if (data->isResultDataEmpty()) {
        return PanelState::PANEL_HIDDEN;
    }

    return PanelState::PANEL_OK;
}

ButtonState AppState::getRPBackButtonState(ModelPtr model) {
    auto tc = model->getThreadController();

    if (tc->isProcessThreadRunning()) {
        return ButtonState::DISABLED;
    }

    return ButtonState::NORMAL;
}