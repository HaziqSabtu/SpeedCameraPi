#pragma once

#include <Model/Enum.hpp>
#include <Model/SharedResource.hpp>
#include <memory>

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

    ButtonState okButtonState;
    ButtonState cancelButtonState;
};

struct TrimDataPanelState {
    ButtonState startButtonState;
    ButtonState replayButtonState;
    ButtonState rangeButtonState;

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
    AppState(ResourcePtr model);

    CapturePanelState getCapturePanelState(ResourcePtr model);
    LaneCalibrationPanelState getLaneCalibrationPanelState(ResourcePtr model);
    LaneManualCalibrationPanelState
    getLaneManualCalibrationPanelState(ResourcePtr model);
    DistanceCalibrationPanelState
    getDistanceCalibrationPanelState(ResourcePtr model);
    ColorCalibrationPanelState getColorCalibrationPanelState(ResourcePtr model);
    RoiPanelState getRoiPanelState(ResourcePtr model);
    ResultPanelState getResultPanelState(ResourcePtr model);
    TrimDataPanelState getTrimDataPanelState(ResourcePtr model);

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
    ButtonState getCPCaptureButtonState(ResourcePtr model);
    ButtonState getCPLoadButtonState(ResourcePtr model);
    ButtonState getCPCameraButtonState(ResourcePtr model);
    ButtonState getCPReplayButtonState(ResourcePtr model);
    ButtonState getCPRemoveButtonState(ResourcePtr model);

    // Capture Panel -> Calibration
    PanelState getCPCaptureStatusState(ResourcePtr model);
    PanelState getCPCalibrationStatusState(ResourcePtr model);
    PanelState getCPHorCalibrationStatusState(ResourcePtr model);
    ButtonState getCPCalibrationButtonState(ResourcePtr model);
    ButtonState getCPCalibrationRemoveButtonState(ResourcePtr model);

    // Capture Panel -> ROI
    PanelState getCPRoiStatusState(ResourcePtr model);
    ButtonState getCPROIButtonState(ResourcePtr model);
    ButtonState getCPROIRemoveButtonState(ResourcePtr model);

    // Capture Panel -> Save / Trim / Reset
    PanelState getCPToolsStatusState(ResourcePtr model);
    ButtonState getCPSaveButtonState(ResourcePtr model);
    ButtonState getCPTrimButtonState(ResourcePtr model);
    ButtonState getCPResetButtonState(ResourcePtr model);

    // Capture Panel -> Measure
    ButtonState getCPMeasureButtonState(ResourcePtr model);

    // Lane Calibration Panel
    PanelState getLCStatusState(ResourcePtr model);
    ButtonState getLCCalibrationButtonState(ResourcePtr model);
    ButtonState getLCPreviewButtonState(ResourcePtr model);
    ButtonState getLCManualCalibrationButtonState(ResourcePtr model);
    ButtonState getLCRemoveButtonState(ResourcePtr model);

    // Lane Calibration Panel -> Tools
    PanelState getLCToolStatusState(ResourcePtr model);
    ButtonState getLCSelectPointButtonState(ResourcePtr model);
    ButtonState getLCCancelCalibrationButtonState(ResourcePtr model);
    ButtonState getLCAcceptCalibrationButtonState(ResourcePtr model);

    // Lane Calibration Panel -> Recalibrate / Others
    PanelState getLCOtherStatusState(ResourcePtr model);
    ButtonState getLCRecalibrateColorButtonState(ResourcePtr model);

    // Lane Calibration Panel -> OK / Cancel
    ButtonState getLCOKButtonState(ResourcePtr model);
    ButtonState getLCCancelButtonState(ResourcePtr model);

    // Lane Manual Calibration Panel
    PanelState getLMStatusState(ResourcePtr model);
    ButtonState getLMButtonState(ResourcePtr model);
    ButtonState getLMPreviewButtonState(ResourcePtr model);
    ButtonState getMCRemoveButtonState(ResourcePtr model);

    // Lane Manual Calibration Panel -> Left
    PanelState getLMLeftStatusState(ResourcePtr model);
    ButtonState getLMSelectLeftButtonState(ResourcePtr model);
    ButtonState getLMRemoveLeftButtonState(ResourcePtr model);

    // Lane Manual Calibration Panel -> Right
    PanelState getLMRightStatusState(ResourcePtr model);
    ButtonState getLMSelectRightButtonState(ResourcePtr model);
    ButtonState getLMRemoveRightButtonState(ResourcePtr model);

    // Lane Manual Calibration Panel -> OK / Cancel
    ButtonState getLMOKButtonState(ResourcePtr model);
    ButtonState getLMCancelButtonState(ResourcePtr model);

    // Distance Calibration Panel
    PanelState getDCStatusState(ResourcePtr model);
    ButtonState getDCButtonState(ResourcePtr model);
    ButtonState getDCPreviewButtonState(ResourcePtr model);
    ButtonState getDCRemoveButtonState(ResourcePtr model);

    // Distance Calibration Panel -> Top
    PanelState getDCTopStatusState(ResourcePtr model);
    ButtonState getDCSelectTopButtonState(ResourcePtr model);
    ButtonState getDCRemoveTopButtonState(ResourcePtr model);

    // Distance Calibration Panel -> Bottom
    PanelState getDCBottomStatusState(ResourcePtr model);
    ButtonState getDCSelectBottomButtonState(ResourcePtr model);
    ButtonState getDCRemoveBottomButtonState(ResourcePtr model);

    // Distance Calibration Panel -> OK / Cancel
    ButtonState getDCOKButtonState(ResourcePtr model);
    ButtonState getDCCancelButtonState(ResourcePtr model);

    // Color Calibration Panel
    ButtonState getCCButtonState(ResourcePtr model);
    ButtonState getCCCameraButtonState(ResourcePtr model);

    // Color Calibration Panel -> Blue
    PanelState getCCBlueStatusState(ResourcePtr model);
    ButtonState getCCSelectBlueButtonState(ResourcePtr model);
    ButtonState getCCAcceptBlueButtonState(ResourcePtr model);

    // Color Calibration Panel -> Yellow
    PanelState getCCYellowStatusState(ResourcePtr model);
    ButtonState getCCSelectYellowButtonState(ResourcePtr model);
    ButtonState getCCAcceptYellowButtonState(ResourcePtr model);

    // Color Calibration Panel -> Save / Restore
    PanelState getCCOtherStatusState(ResourcePtr model);
    ButtonState getCCRestoreButtonState(ResourcePtr model);

    // Color Calibration Panel -> OK / Cancel
    ButtonState getCCOKButtonState(ResourcePtr model);
    ButtonState getCCCancelButtonState(ResourcePtr model);

    // ROI Panel
    PanelState getROIStatusState(ResourcePtr model);
    ButtonState getROIButtonState(ResourcePtr model);
    ButtonState getROICameraButtonState(ResourcePtr model);
    ButtonState getROIRemoveButtonState(ResourcePtr model);

    // ROI Panel -> OK / Cancel
    ButtonState getROIOKButtonState(ResourcePtr model);
    ButtonState getROICancelButtonState(ResourcePtr model);

    // Trim Data Panel
    ButtonState getTDStartButtonState(ResourcePtr model);
    ButtonState getTDReplayButtonState(ResourcePtr model);
    ButtonState getTDRangeButtonState(ResourcePtr model);

    // Trim Data Panel -> Start
    PanelState getTDStartStatusState(ResourcePtr model);
    ButtonState getTDIncStartButtonState(ResourcePtr model);
    ButtonState getTDDecStartButtonState(ResourcePtr model);

    // Trim Data Panel -> End
    PanelState getTDEndStatusState(ResourcePtr model);
    ButtonState getTDIncEndButtonState(ResourcePtr model);
    ButtonState getTDDecEndButtonState(ResourcePtr model);

    // Trim Data Panel -> OK / Cancel
    ButtonState getTDOKButtonState(ResourcePtr model);
    ButtonState getTDCancelButtonState(ResourcePtr model);

    // Result Panel
    PanelState getRPResultStatusState(ResourcePtr model);
    ButtonState getRPProcLaneButtonState(ResourcePtr model);
    ButtonState getRPProcDistButtonState(ResourcePtr model);
    ButtonState getRPPreviewButtonState(ResourcePtr model);

    // Result Panel -> Preview
    PanelState getRPPreviewStatusState(ResourcePtr model);
    ButtonState getRPBoxButtonState(ResourcePtr model);
    ButtonState getRPLinesButtonState(ResourcePtr model);
    ButtonState getRPLanesButtonState(ResourcePtr model);
    ButtonState getRPReplayButtonState(ResourcePtr model);

    // Result Panel -> Speed
    PanelState getRPSpeedStatusState(ResourcePtr model);

    // Result Panel -> Back
    ButtonState getRPBackButtonState(ResourcePtr model);
};
