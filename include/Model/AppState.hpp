#pragma once

#include <Model/SharedModel.hpp>
#include <memory>

enum ButtonState { NORMAL, ACTIVE, DISABLED, ON, OFF, HIDDEN };

enum PanelState { PANEL_NOT_OK, PANEL_OK, PANEL_HIDDEN };

struct CapturePanelState {
    PanelState captureStatusState;
    ButtonState captureButtonState;
    ButtonState loadButtonState;
    ButtonState replayButtonState;
    ButtonState removeButtonState;
    ButtonState cameraButtonState;

    PanelState calibStatusState;
    PanelState horCalibStatusState;
    ButtonState calibButtonState;
    ButtonState calibRemoveButtonState;

    PanelState roiStatusState;
    ButtonState roiButtonState;
    ButtonState roiRemoveButtonState;

    PanelState toolsStatusState;
    ButtonState saveButtonState;
    ButtonState trimButtonState;
    ButtonState resetButtonState;

    ButtonState measureButtonState;
};

struct LaneCalibrationPanelState {
    PanelState state;

    ButtonState calibrationButtonState;
    ButtonState previewButtonState;
    ButtonState manualCalibrationButtonState;
    ButtonState removeButtonState;

    PanelState toolStatusState;
    ButtonState selectPointButtonState;
    ButtonState cancelCalibrationButtonState;
    ButtonState acceptCalibrationButtonState;

    PanelState otherStatusState;
    ButtonState recalibrateColorButtonState;

    ButtonState okButtonState;
    ButtonState cancelButtonState;
};

struct LaneManualCalibrationPanelState {
    PanelState state;

    ButtonState calibrationButtonState;
    ButtonState previewButtonState;
    ButtonState removeButtonState;

    PanelState leftStatusState;
    ButtonState selectLeftButtonState;
    ButtonState removeLeftButtonState;

    PanelState rightStatusState;
    ButtonState selectRightButtonState;
    ButtonState removeRightButtonState;

    ButtonState okButtonState;
    ButtonState cancelButtonState;
};

struct DistanceCalibrationPanelState {
    PanelState state;

    ButtonState calibrationButtonState;
    ButtonState previewButtonState;
    ButtonState removeButtonState;

    PanelState topStatusState;
    ButtonState selectTopButtonState;
    ButtonState removeTopButtonState;

    PanelState bottomStatusState;
    ButtonState selectBottomButtonState;
    ButtonState removeBottomButtonState;

    ButtonState okButtonState;
    ButtonState cancelButtonState;
};

struct ColorCalibrationPanelState {

    ButtonState calibrationButtonState;
    ButtonState stopButtonState;
    ButtonState cameraButtonState;

    PanelState blueStatusState;
    ButtonState selectBlueButtonState;
    ButtonState acceptBlueButtonState;

    PanelState yellowStatusState;
    ButtonState selectYellowButtonState;
    ButtonState acceptYellowButtonState;

    PanelState otherStatusState;
    ButtonState restoreButtonState;

    ButtonState okButtonState;
    ButtonState cancelButtonState;
};

struct RoiPanelState {
    PanelState state;

    ButtonState roiButtonState;
    ButtonState cameraButtonState;
    ButtonState removeButtonState;

    PanelState roiToolsStatusState;
    ButtonState acceptRoiButtonState;
    ButtonState clearRoiButtonState;

    ButtonState okButtonState;
    ButtonState cancelButtonState;
};

struct TrimDataPanelState {
    ButtonState startButtonState;
    ButtonState replayButtonState;
    ButtonState rangeButtonState;
    ButtonState removeButtonState;

    PanelState startStatusState;
    ButtonState incStartButtonState;
    ButtonState decStartButtonState;

    PanelState endStatusState;
    ButtonState incEndButtonState;
    ButtonState decEndButtonState;

    ButtonState okButtonState;
    ButtonState cancelButtonState;
};

struct ResultPanelState {
    PanelState state;
    ButtonState procLaneButtonState;
    ButtonState procDistButtonState;
    ButtonState previewButtonState;

    PanelState previewStatusState;
    ButtonState boxButtonState;
    ButtonState linesButtonState;
    ButtonState lanesButtonState;
    ButtonState replayButtonState;

    PanelState speedStatusState;

    ButtonState backButtonState;
};

class AppState {
  public:
    AppState();
    AppState(ModelPtr model);

    CapturePanelState getCapturePanelState(ModelPtr model);
    LaneCalibrationPanelState getLaneCalibrationPanelState(ModelPtr model);
    LaneManualCalibrationPanelState
    getLaneManualCalibrationPanelState(ModelPtr model);
    DistanceCalibrationPanelState
    getDistanceCalibrationPanelState(ModelPtr model);
    ColorCalibrationPanelState getColorCalibrationPanelState(ModelPtr model);
    RoiPanelState getRoiPanelState(ModelPtr model);
    ResultPanelState getResultPanelState(ModelPtr model);
    TrimDataPanelState getTrimDataPanelState(ModelPtr model);

  public:
    CapturePanelState capturePanel;
    LaneCalibrationPanelState laneCalibrationPanel;
    LaneManualCalibrationPanelState laneManualCalibrationPanel;
    DistanceCalibrationPanelState distanceCalibrationPanel;
    ColorCalibrationPanelState colorCalibrationPanel;
    RoiPanelState roiPanel;
    ResultPanelState resultPanel;
    TrimDataPanelState trimDataPanel;

  private:
    // Capture Panel
    ButtonState getCPCaptureButtonState(ModelPtr model);
    ButtonState getCPLoadButtonState(ModelPtr model);
    ButtonState getCPCameraButtonState(ModelPtr model);
    ButtonState getCPReplayButtonState(ModelPtr model);
    ButtonState getCPRemoveButtonState(ModelPtr model);

    // Capture Panel -> Calibration
    PanelState getCPCaptureStatusState(ModelPtr model);
    PanelState getCPCalibrationStatusState(ModelPtr model);
    PanelState getCPHorCalibrationStatusState(ModelPtr model);
    ButtonState getCPCalibrationButtonState(ModelPtr model);
    ButtonState getCPCalibrationRemoveButtonState(ModelPtr model);

    // Capture Panel -> ROI
    PanelState getCPRoiStatusState(ModelPtr model);
    ButtonState getCPROIButtonState(ModelPtr model);
    ButtonState getCPROIRemoveButtonState(ModelPtr model);

    // Capture Panel -> Save / Trim / Reset
    PanelState getCPToolsStatusState(ModelPtr model);
    ButtonState getCPSaveButtonState(ModelPtr model);
    ButtonState getCPTrimButtonState(ModelPtr model);
    ButtonState getCPResetButtonState(ModelPtr model);

    // Capture Panel -> Measure
    ButtonState getCPMeasureButtonState(ModelPtr model);

    // Lane Calibration Panel
    PanelState getLCStatusState(ModelPtr model);
    ButtonState getLCCalibrationButtonState(ModelPtr model);
    ButtonState getLCPreviewButtonState(ModelPtr model);
    ButtonState getLCManualCalibrationButtonState(ModelPtr model);
    ButtonState getLCRemoveButtonState(ModelPtr model);

    // Lane Calibration Panel -> Tools
    PanelState getLCToolStatusState(ModelPtr model);
    ButtonState getLCSelectPointButtonState(ModelPtr model);
    ButtonState getLCCancelCalibrationButtonState(ModelPtr model);
    ButtonState getLCAcceptCalibrationButtonState(ModelPtr model);

    // Lane Calibration Panel -> Recalibrate / Others
    PanelState getLCOtherStatusState(ModelPtr model);
    ButtonState getLCRecalibrateColorButtonState(ModelPtr model);

    // Lane Calibration Panel -> OK / Cancel
    ButtonState getLCOKButtonState(ModelPtr model);
    ButtonState getLCCancelButtonState(ModelPtr model);

    // Lane Manual Calibration Panel
    PanelState getLMStatusState(ModelPtr model);
    ButtonState getLMButtonState(ModelPtr model);
    ButtonState getLMPreviewButtonState(ModelPtr model);
    ButtonState getMCRemoveButtonState(ModelPtr model);

    // Lane Manual Calibration Panel -> Left
    PanelState getLMLeftStatusState(ModelPtr model);
    ButtonState getLMSelectLeftButtonState(ModelPtr model);
    ButtonState getLMRemoveLeftButtonState(ModelPtr model);

    // Lane Manual Calibration Panel -> Right
    PanelState getLMRightStatusState(ModelPtr model);
    ButtonState getLMSelectRightButtonState(ModelPtr model);
    ButtonState getLMRemoveRightButtonState(ModelPtr model);

    // Lane Manual Calibration Panel -> OK / Cancel
    ButtonState getLMOKButtonState(ModelPtr model);
    ButtonState getLMCancelButtonState(ModelPtr model);

    // Distance Calibration Panel
    PanelState getDCStatusState(ModelPtr model);
    ButtonState getDCButtonState(ModelPtr model);
    ButtonState getDCPreviewButtonState(ModelPtr model);
    ButtonState getDCRemoveButtonState(ModelPtr model);

    // Distance Calibration Panel -> Top
    PanelState getDCTopStatusState(ModelPtr model);
    ButtonState getDCSelectTopButtonState(ModelPtr model);
    ButtonState getDCRemoveTopButtonState(ModelPtr model);

    // Distance Calibration Panel -> Bottom
    PanelState getDCBottomStatusState(ModelPtr model);
    ButtonState getDCSelectBottomButtonState(ModelPtr model);
    ButtonState getDCRemoveBottomButtonState(ModelPtr model);

    // Distance Calibration Panel -> OK / Cancel
    ButtonState getDCOKButtonState(ModelPtr model);
    ButtonState getDCCancelButtonState(ModelPtr model);

    // Color Calibration Panel
    ButtonState getCCButtonState(ModelPtr model);
    ButtonState getCCStopButtonState(ModelPtr model);
    ButtonState getCCCameraButtonState(ModelPtr model);

    // Color Calibration Panel -> Blue
    PanelState getCCBlueStatusState(ModelPtr model);
    ButtonState getCCSelectBlueButtonState(ModelPtr model);
    ButtonState getCCAcceptBlueButtonState(ModelPtr model);

    // Color Calibration Panel -> Yellow
    PanelState getCCYellowStatusState(ModelPtr model);
    ButtonState getCCSelectYellowButtonState(ModelPtr model);
    ButtonState getCCAcceptYellowButtonState(ModelPtr model);

    // Color Calibration Panel -> Save / Restore
    PanelState getCCOtherStatusState(ModelPtr model);
    ButtonState getCCRestoreButtonState(ModelPtr model);

    // Color Calibration Panel -> OK / Cancel
    ButtonState getCCOKButtonState(ModelPtr model);
    ButtonState getCCCancelButtonState(ModelPtr model);

    // ROI Panel
    PanelState getROIStatusState(ModelPtr model);
    ButtonState getROIButtonState(ModelPtr model);
    ButtonState getROICameraButtonState(ModelPtr model);
    ButtonState getROIRemoveButtonState(ModelPtr model);

    // ROI Panel -> Accept / Clear
    PanelState getROIToolsStatusState(ModelPtr model);
    ButtonState getROIAcceptRoiButtonState(ModelPtr model);
    ButtonState getROIClearRoiButtonState(ModelPtr model);

    // ROI Panel -> OK / Cancel
    ButtonState getROIOKButtonState(ModelPtr model);
    ButtonState getROICancelButtonState(ModelPtr model);

    // Trim Data Panel
    ButtonState getTDStartButtonState(ModelPtr model);
    ButtonState getTDReplayButtonState(ModelPtr model);
    ButtonState getTDRangeButtonState(ModelPtr model);
    ButtonState getTDRemoveButtonState(ModelPtr model);

    // Trim Data Panel -> Start
    PanelState getTDStartStatusState(ModelPtr model);
    ButtonState getTDIncStartButtonState(ModelPtr model);
    ButtonState getTDDecStartButtonState(ModelPtr model);

    // Trim Data Panel -> End
    PanelState getTDEndStatusState(ModelPtr model);
    ButtonState getTDIncEndButtonState(ModelPtr model);
    ButtonState getTDDecEndButtonState(ModelPtr model);

    // Trim Data Panel -> OK / Cancel
    ButtonState getTDOKButtonState(ModelPtr model);
    ButtonState getTDCancelButtonState(ModelPtr model);

    // Result Panel
    PanelState getRPResultStatusState(ModelPtr model);
    ButtonState getRPProcLaneButtonState(ModelPtr model);
    ButtonState getRPProcDistButtonState(ModelPtr model);
    ButtonState getRPPreviewButtonState(ModelPtr model);

    // Result Panel -> Preview
    PanelState getRPPreviewStatusState(ModelPtr model);
    ButtonState getRPBoxButtonState(ModelPtr model);
    ButtonState getRPLinesButtonState(ModelPtr model);
    ButtonState getRPLanesButtonState(ModelPtr model);
    ButtonState getRPReplayButtonState(ModelPtr model);

    // Result Panel -> Speed
    PanelState getRPSpeedStatusState(ModelPtr model);

    // Result Panel -> Back
    ButtonState getRPBackButtonState(ModelPtr model);
};
