#include "Model/SessionData.hpp"
#include "Thread/Thread_DistanceCalibrationCamera.hpp"
#include "Thread/Thread_ID.hpp"
#include <Model/AppState.hpp>

AppState::AppState() {}

AppState::AppState(ModelPtr model) {
    capturePanel = getCapturePanelState(model);
    laneCalibrationPanel = getLaneCalibrationPanelState(model);
    laneManualCalibrationPanel = getLaneManualCalibrationPanelState(model);
    distanceCalibrationPanel = getDistanceCalibrationPanelState(model);
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

LaneCalibrationPanelState
AppState::getLaneCalibrationPanelState(ModelPtr model) {
    LaneCalibrationPanelState ps;

    ps.state = getLCStatusState(model);

    ps.calibrationButtonState = getLCCalibrationButtonState(model);
    ps.previewButtonState = getLCPreviewButtonState(model);
    ps.manualCalibrationButtonState = getLCManualCalibrationButtonState(model);
    ps.removeButtonState = getLCRemoveButtonState(model);

    ps.toolStatusState = getLCToolStatusState(model);
    ps.selectPointButtonState = getLCSelectPointButtonState(model);
    ps.cancelCalibrationButtonState = getLCCancelCalibrationButtonState(model);
    ps.acceptCalibrationButtonState = getLCAcceptCalibrationButtonState(model);

    ps.otherStatusState = getLCOtherStatusState(model);
    ps.recalibrateColorButtonState = getLCRecalibrateColorButtonState(model);

    ps.okButtonState = getLCOKButtonState(model);
    ps.cancelButtonState = getLCCancelButtonState(model);

    return ps;
}

LaneManualCalibrationPanelState AppState::getLaneManualCalibrationPanelState(
    std::shared_ptr<SharedModel> model) {
    LaneManualCalibrationPanelState ps;

    ps.state = getLMStatusState(model);

    ps.calibrationButtonState = getLMButtonState(model);
    ps.previewButtonState = getLMPreviewButtonState(model);
    ps.removeButtonState = getMCRemoveButtonState(model);

    ps.leftStatusState = getLMLeftStatusState(model);
    ps.selectLeftButtonState = getLMSelectLeftButtonState(model);
    ps.removeLeftButtonState = getLMRemoveLeftButtonState(model);

    ps.rightStatusState = getLMRightStatusState(model);
    ps.selectRightButtonState = getLMSelectRightButtonState(model);
    ps.removeRightButtonState = getLMRemoveRightButtonState(model);

    ps.okButtonState = getLMOKButtonState(model);
    ps.cancelButtonState = getLMCancelButtonState(model);

    return ps;
}

DistanceCalibrationPanelState
AppState::getDistanceCalibrationPanelState(ModelPtr model) {
    DistanceCalibrationPanelState ps;

    ps.state = getDCStatusState(model);

    ps.calibrationButtonState = getDCButtonState(model);
    ps.previewButtonState = getDCPreviewButtonState(model);
    ps.removeButtonState = getDCRemoveButtonState(model);

    ps.topStatusState = getDCTopStatusState(model);
    ps.selectTopButtonState = getDCSelectTopButtonState(model);
    ps.removeTopButtonState = getDCRemoveTopButtonState(model);

    ps.bottomStatusState = getDCBottomStatusState(model);
    ps.selectBottomButtonState = getDCSelectBottomButtonState(model);
    ps.removeBottomButtonState = getDCRemoveBottomButtonState(model);

    ps.okButtonState = getDCOKButtonState(model);
    ps.cancelButtonState = getDCCancelButtonState(model);

    return ps;
}

ColorCalibrationPanelState
AppState::getColorCalibrationPanelState(std::shared_ptr<SharedModel> model) {
    ColorCalibrationPanelState ps;

    ps.calibrationButtonState = getCCButtonState(model);
    ps.stopButtonState = getCCStopButtonState(model);
    ps.cameraButtonState = getCCCameraButtonState(model);

    ps.blueStatusState = getCCBlueStatusState(model);
    ps.selectBlueButtonState = getCCSelectBlueButtonState(model);
    ps.acceptBlueButtonState = getCCAcceptBlueButtonState(model);

    ps.yellowStatusState = getCCYellowStatusState(model);
    ps.selectYellowButtonState = getCCSelectYellowButtonState(model);
    ps.acceptYellowButtonState = getCCAcceptYellowButtonState(model);

    ps.otherStatusState = getCCOtherStatusState(model);
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

PanelState AppState::getLCStatusState(ModelPtr model) {
    return model->sessionData.isCalibrationDataEmpty()
               ? PanelState::PANEL_NOT_OK
               : PanelState::PANEL_OK;
}

ButtonState AppState::getLCCalibrationButtonState(ModelPtr model) {
    auto tc = model->getThreadController();

    if (tc->isLaneCalibrationThreadRunning()) {
        return ButtonState::ON;
    }

    auto data = model->getSessionData();
    if (!data->isCalibrationDataEmpty()) {
        return ButtonState::HIDDEN;
    }

    return ButtonState::OFF;
}

ButtonState AppState::getLCRemoveButtonState(ModelPtr model) {
    auto tc = model->getThreadController();

    if (model->sessionData.isCalibrationDataEmpty()) {
        return ButtonState::HIDDEN;
    }

    if (tc->isLaneCalibrationThreadRunning()) {
        return ButtonState::HIDDEN;
    }

    if (tc->isCalibPreviewThreadRunning()) {
        return ButtonState::DISABLED;
    }

    return ButtonState::NORMAL;
}

PanelState AppState::getLCToolStatusState(ModelPtr model) {
    auto tc = model->getThreadController();

    if (!tc->isLaneCalibrationThreadRunning()) {
        return PanelState::PANEL_HIDDEN;
    }

    return PanelState::PANEL_OK;
}

ButtonState AppState::getLCSelectPointButtonState(ModelPtr model) {
    auto tc = model->getThreadController();

    if (getLCToolStatusState(model) == PanelState::PANEL_HIDDEN) {
        return ButtonState::DISABLED;
    }

    return ButtonState::NORMAL;
}

ButtonState AppState::getLCCancelCalibrationButtonState(ModelPtr model) {
    return getLCSelectPointButtonState(model);
}

ButtonState AppState::getLCAcceptCalibrationButtonState(ModelPtr model) {
    return getLCSelectPointButtonState(model);
}

ButtonState AppState::getLCPreviewButtonState(ModelPtr model) {
    auto tc = model->getThreadController();

    auto data = model->getSessionData();
    if (data->isCalibrationDataEmpty()) {
        return ButtonState::HIDDEN;
    }

    if (tc->isLaneCalibrationThreadRunning()) {
        return ButtonState::HIDDEN;
    }

    if (tc->isCalibPreviewThreadRunning()) {
        return ButtonState::ON;
    }

    return ButtonState::OFF;
}

PanelState AppState::getLCOtherStatusState(ModelPtr model) {
    auto tc = model->getThreadController();

    if (tc->isLaneCalibrationThreadRunning()) {
        return PanelState::PANEL_HIDDEN;
    }

    auto data = model->getSessionData();
    if (!data->isCalibrationDataEmpty()) {
        return PanelState::PANEL_HIDDEN;
    }

    return PanelState::PANEL_OK;
}

ButtonState AppState::getLCRecalibrateColorButtonState(ModelPtr model) {
    auto tc = model->getThreadController();

    if (getLCOtherStatusState(model) == PanelState::PANEL_HIDDEN) {
        return ButtonState::DISABLED;
    }

    return ButtonState::NORMAL;
}

ButtonState AppState::getLCManualCalibrationButtonState(ModelPtr model) {
    auto tc = model->getThreadController();

    if (tc->isLaneCalibrationThreadRunning()) {
        return ButtonState::HIDDEN;
    }

    auto data = model->getSessionData();
    if (!data->isCalibrationDataEmpty()) {
        return ButtonState::HIDDEN;
    }

    return ButtonState::NORMAL;
}

ButtonState AppState::getLCOKButtonState(ModelPtr model) {
    if (model->isSessionDataChanged()) {
        return ButtonState::NORMAL;
    }

    return ButtonState::DISABLED;
}

ButtonState AppState::getLCCancelButtonState(ModelPtr model) {
    return ButtonState::NORMAL;
}

PanelState AppState::getLMStatusState(ModelPtr model) {
    return model->sessionData.isCalibrationDataEmpty()
               ? PanelState::PANEL_NOT_OK
               : PanelState::PANEL_OK;
}

ButtonState AppState::getLMButtonState(ModelPtr model) {
    auto tc = model->getThreadController();

    if (tc->isLaneManualCalibrationThreadRunning()) {
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

    if (tc->isLaneManualCalibrationThreadRunning()) {
        return ButtonState::HIDDEN;
    }

    if (tc->isCalibPreviewThreadRunning()) {
        return ButtonState::DISABLED;
    }

    return ButtonState::NORMAL;
}

PanelState AppState::getLMLeftStatusState(ModelPtr model) {
    auto tc = model->getThreadController();

    if (!tc->isLaneManualCalibrationThreadRunning()) {
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

ButtonState AppState::getLMSelectLeftButtonState(ModelPtr model) {
    auto tc = model->getThreadController();

    if (getLMLeftStatusState(model) == PanelState::PANEL_HIDDEN) {
        return ButtonState::DISABLED;
    }

    auto thread = tc->getRunningLaneManualCalibrationThread();
    if (thread->getDirection() == ManualDirection::MANUAL_LEFT) {
        return ButtonState::ACTIVE;
    }

    return ButtonState::NORMAL;
}

ButtonState AppState::getLMRemoveLeftButtonState(ModelPtr model) {
    auto tc = model->getThreadController();

    if (getLMLeftStatusState(model) == PanelState::PANEL_HIDDEN) {
        return ButtonState::DISABLED;
    }

    return ButtonState::NORMAL;
}

PanelState AppState::getLMRightStatusState(ModelPtr model) {
    auto tc = model->getThreadController();

    if (!tc->isLaneManualCalibrationThreadRunning()) {
        return PanelState::PANEL_HIDDEN;
    }

    auto calibData = model->sessionData.getCalibrationData();

    Line line = calibData.lineRight;

    if (line.isNull()) {
        return PanelState::PANEL_NOT_OK;
    }
    return PanelState::PANEL_OK;
}

ButtonState AppState::getLMSelectRightButtonState(ModelPtr model) {
    auto tc = model->getThreadController();

    if (getLMLeftStatusState(model) == PanelState::PANEL_HIDDEN) {
        return ButtonState::DISABLED;
    }

    auto thread = tc->getRunningLaneManualCalibrationThread();
    if (thread->getDirection() == ManualDirection::MANUAL_RIGHT) {
        return ButtonState::ACTIVE;
    }

    return ButtonState::NORMAL;
}

ButtonState AppState::getLMRemoveRightButtonState(ModelPtr model) {
    auto tc = model->getThreadController();

    if (getLMLeftStatusState(model) == PanelState::PANEL_HIDDEN) {
        return ButtonState::DISABLED;
    }

    return ButtonState::NORMAL;
}

ButtonState AppState::getLMPreviewButtonState(ModelPtr model) {
    auto tc = model->getThreadController();

    auto data = model->getSessionData();
    if (data->isCalibrationDataEmpty()) {
        return ButtonState::HIDDEN;
    }

    if (tc->isLaneManualCalibrationThreadRunning()) {
        return ButtonState::HIDDEN;
    }

    if (tc->isCalibPreviewThreadRunning()) {
        return ButtonState::ON;
    }

    return ButtonState::OFF;
}

ButtonState AppState::getLMOKButtonState(ModelPtr model) {
    if (model->isSessionDataChanged()) {
        return ButtonState::NORMAL;
    }

    return ButtonState::DISABLED;
}

ButtonState AppState::getLMCancelButtonState(ModelPtr model) {
    return ButtonState::NORMAL;
}

PanelState AppState::getDCStatusState(ModelPtr model) {
    return model->sessionData.isCalibrationDataEmpty()
               ? PanelState::PANEL_NOT_OK
               : PanelState::PANEL_OK;
}

ButtonState AppState::getDCButtonState(ModelPtr model) {
    auto tc = model->getThreadController();

    if (tc->isDistanceCalibrationThreadRunning()) {
        return ButtonState::ON;
    }

    auto data = model->getSessionData();
    if (!data->isCalibrationDataEmpty()) {
        return ButtonState::HIDDEN;
    }

    return ButtonState::OFF;
}

ButtonState AppState::getDCRemoveButtonState(ModelPtr model) {
    auto tc = model->getThreadController();

    if (model->sessionData.isCalibrationDataEmpty()) {
        return ButtonState::HIDDEN;
    }

    if (tc->isLaneManualCalibrationThreadRunning()) {
        return ButtonState::HIDDEN;
    }

    if (tc->isCalibPreviewThreadRunning()) {
        return ButtonState::DISABLED;
    }

    return ButtonState::NORMAL;
}

PanelState AppState::getDCTopStatusState(ModelPtr model) {
    auto tc = model->getThreadController();

    if (!tc->isDistanceCalibrationThreadRunning()) {
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

ButtonState AppState::getDCSelectTopButtonState(ModelPtr model) {
    auto tc = model->getThreadController();

    if (getDCTopStatusState(model) == PanelState::PANEL_HIDDEN) {
        return ButtonState::DISABLED;
    }

    auto thread = tc->getRunningDistanceCalibrationThread();
    if (thread->getDirection() == DistanceDirection::DISTANCE_TOP) {
        return ButtonState::ACTIVE;
    }

    return ButtonState::NORMAL;
}

ButtonState AppState::getDCRemoveTopButtonState(ModelPtr model) {
    auto tc = model->getThreadController();

    if (getDCTopStatusState(model) == PanelState::PANEL_HIDDEN) {
        return ButtonState::DISABLED;
    }

    return ButtonState::NORMAL;
}

PanelState AppState::getDCBottomStatusState(ModelPtr model) {
    auto tc = model->getThreadController();

    if (!tc->isDistanceCalibrationThreadRunning()) {
        return PanelState::PANEL_HIDDEN;
    }

    auto calibData = model->sessionData.getCalibrationData();

    Line line = calibData.lineLeft;

    if (line.isNull()) {
        return PanelState::PANEL_NOT_OK;
    }
    return PanelState::PANEL_OK;
}

ButtonState AppState::getDCSelectBottomButtonState(ModelPtr model) {
    auto tc = model->getThreadController();

    if (getDCBottomStatusState(model) == PanelState::PANEL_HIDDEN) {
        return ButtonState::DISABLED;
    }

    auto thread = tc->getRunningDistanceCalibrationThread();
    if (thread->getDirection() == DistanceDirection::DISTANCE_BOTTOM) {
        return ButtonState::ACTIVE;
    }

    return ButtonState::NORMAL;
}

ButtonState AppState::getDCRemoveBottomButtonState(ModelPtr model) {
    auto tc = model->getThreadController();

    if (getDCBottomStatusState(model) == PanelState::PANEL_HIDDEN) {
        return ButtonState::DISABLED;
    }

    return ButtonState::NORMAL;
}

ButtonState AppState::getDCPreviewButtonState(ModelPtr model) {
    auto tc = model->getThreadController();

    auto data = model->getSessionData();
    if (data->isCalibrationDataEmpty()) {
        return ButtonState::HIDDEN;
    }

    if (tc->isDistanceCalibrationThreadRunning()) {
        return ButtonState::HIDDEN;
    }

    if (tc->isCalibPreviewThreadRunning()) {
        return ButtonState::ON;
    }

    return ButtonState::OFF;
}

ButtonState AppState::getDCOKButtonState(ModelPtr model) {
    if (model->isSessionDataChanged()) {
        return ButtonState::NORMAL;
    }

    return ButtonState::DISABLED;
}

ButtonState AppState::getDCCancelButtonState(ModelPtr model) {
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