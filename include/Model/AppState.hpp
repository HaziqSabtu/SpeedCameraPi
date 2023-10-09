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

struct CalibrationPanelState {
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

struct ManualCalibrationPanelState {
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

struct HorizontalCalibrationPanelState {
    PanelState state;

    ButtonState calibrationButtonState;
    ButtonState calibrationCaptureButtonState;
    ButtonState removeButtonState;

    PanelState topStatusState;
    ButtonState selectTopButtonState;
    ButtonState removeTopButtonState;

    PanelState bottomStatusState;
    ButtonState selectBottomButtonState;
    ButtonState removeBottomButtonState;

    PanelState previewStatusState;
    ButtonState prevCameraButtonState;
    ButtonState prevCaptureButtonState;

    ButtonState okButtonState;
    ButtonState cancelButtonState;
};

struct ColorCalibrationPanelState {

    ButtonState calibrationButtonState;
    ButtonState stopButtonState;
    ButtonState removeButtonState;
    ButtonState cameraButtonState;

    PanelState blueStatusState;
    ButtonState selectBlueButtonState;
    ButtonState acceptBlueButtonState;

    PanelState yellowStatusState;
    ButtonState selectYellowButtonState;
    ButtonState acceptYellowButtonState;

    ButtonState saveButtonState;
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
};

class AppState {
  public:
    AppState();
    AppState(ModelPtr model);

    CapturePanelState getCapturePanelState(ModelPtr model);
    CalibrationPanelState getCalibrationPanelState(ModelPtr model);
    ManualCalibrationPanelState getManualCalibrationPanelState(ModelPtr model);
    HorizontalCalibrationPanelState
    getHorizontalCalibrationPanelState(ModelPtr model);
    ColorCalibrationPanelState getColorCalibrationPanelState(ModelPtr model);
    RoiPanelState getRoiPanelState(ModelPtr model);
    ResultPanelState getResultPanelState(ModelPtr model);
    TrimDataPanelState getTrimDataPanelState(ModelPtr model);

  public:
    CapturePanelState capturePanel;
    CalibrationPanelState calibrationPanel;
    ManualCalibrationPanelState manualCalibrationPanel;
    HorizontalCalibrationPanelState horizontalCalibrationPanel;
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

    // Calibration Panel
    PanelState getCLStatusState(ModelPtr model);
    ButtonState getCLCalibrationButtonState(ModelPtr model);
    ButtonState getCLPreviewButtonState(ModelPtr model);
    ButtonState getCLManualCalibrationButtonState(ModelPtr model);
    ButtonState getCLRemoveButtonState(ModelPtr model);

    // Calibration Panel -> Tools
    PanelState getCLToolStatusState(ModelPtr model);
    ButtonState getCLSelectPointButtonState(ModelPtr model);
    ButtonState getCLCancelCalibrationButtonState(ModelPtr model);
    ButtonState getCLAcceptCalibrationButtonState(ModelPtr model);

    // Calibration Panel -> Recalibrate / Others
    PanelState getCLOtherStatusState(ModelPtr model);
    ButtonState getCLRecalibrateColorButtonState(ModelPtr model);

    // Calibration Panel -> OK / Cancel
    ButtonState getCLOKButtonState(ModelPtr model);
    ButtonState getCLCancelButtonState(ModelPtr model);

    // Manual Calibration Panel
    PanelState getMCStatusState(ModelPtr model);
    ButtonState getMCButtonState(ModelPtr model);
    ButtonState getMCPreviewButtonState(ModelPtr model);
    ButtonState getMCRemoveButtonState(ModelPtr model);

    // Manual Calibration Panel -> Left
    PanelState getMCLeftStatusState(ModelPtr model);
    ButtonState getMCSelectLeftButtonState(ModelPtr model);
    ButtonState getMCRemoveLeftButtonState(ModelPtr model);

    // Manual Calibration Panel -> Right
    PanelState getMCRightStatusState(ModelPtr model);
    ButtonState getMCSelectRightButtonState(ModelPtr model);
    ButtonState getMCRemoveRightButtonState(ModelPtr model);

    // Manual Calibration Panel -> OK / Cancel
    ButtonState getMCOKButtonState(ModelPtr model);
    ButtonState getMCCancelButtonState(ModelPtr model);

    // Horizontal Calibration Panel
    PanelState getHCStatusState(ModelPtr model);
    ButtonState getHCButtonState(ModelPtr model);
    ButtonState getHCCaptureButtonState(ModelPtr model);
    ButtonState getHCRemoveButtonState(ModelPtr model);

    // Horizontal Calibration Panel -> Top
    PanelState getHCTopStatusState(ModelPtr model);
    ButtonState getHCSelectTopButtonState(ModelPtr model);
    ButtonState getHCRemoveTopButtonState(ModelPtr model);

    // Horizontal Calibration Panel -> Bottom
    PanelState getHCBottomStatusState(ModelPtr model);
    ButtonState getHCSelectBottomButtonState(ModelPtr model);
    ButtonState getHCRemoveBottomButtonState(ModelPtr model);

    // Horizontal Calibration Panel -> Preview
    PanelState getHCPreviewStatusState(ModelPtr model);
    ButtonState getHCPrevCameraButtonState(ModelPtr model);
    ButtonState getHCPrevCaptureButtonState(ModelPtr model);

    // Horizontal Calibration Panel -> OK / Cancel
    ButtonState getHCOKButtonState(ModelPtr model);
    ButtonState getHCCancelButtonState(ModelPtr model);

    // Color Calibration Panel
    ButtonState getCCButtonState(ModelPtr model);
    ButtonState getCCStopButtonState(ModelPtr model);
    ButtonState getCCCameraButtonState(ModelPtr model);
    ButtonState getCCRemoveButtonState(ModelPtr model);

    // Color Calibration Panel -> Blue
    PanelState getCCBlueStatusState(ModelPtr model);
    ButtonState getCCSelectBlueButtonState(ModelPtr model);
    ButtonState getCCAcceptBlueButtonState(ModelPtr model);

    // Color Calibration Panel -> Yellow
    PanelState getCCYellowStatusState(ModelPtr model);
    ButtonState getCCSelectYellowButtonState(ModelPtr model);
    ButtonState getCCAcceptYellowButtonState(ModelPtr model);

    // Color Calibration Panel -> Save / Restore
    ButtonState getCCSaveButtonState(ModelPtr model);
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
};
