#pragma once

#include "Model/SharedModel.hpp"
#include <memory>
enum ButtonState { NORMAL, ACTIVE, DISABLED, ON, OFF };

enum PanelState { PANEL_NOT_OK, PANEL_OK };

struct CapturePanelState {
    PanelState captureStatusState;
    ButtonState captureButtonState;
    ButtonState loadButtonState;
    ButtonState replayButtonState;
    ButtonState removeButtonState;
    ButtonState cameraButtonState;

    PanelState calibStatusState;
    ButtonState calibButtonState;
    ButtonState calibRemoveButtonState;

    PanelState roiStatusState;
    ButtonState roiButtonState;
    ButtonState roiRemoveButtonState;

    ButtonState measureButtonState;
};

struct CalibrationPanelState {
    PanelState state;

    ButtonState calibrationButtonState;
    ButtonState removeButtonState;
    ButtonState cameraButtonState;

    ButtonState selectPointButtonState;
    ButtonState cancelCalibrationButtonState;
    ButtonState acceptCalibrationButtonState;

    ButtonState recalibrateColorButtonState;
    ButtonState manualCalibrationButtonState;

    ButtonState okButtonState;
    ButtonState cancelButtonState;
};

struct ManualCalibrationPanelState {
    PanelState state;

    ButtonState calibrationButtonState;
    ButtonState stopButtonState;
    ButtonState cameraButtonState;
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
    ButtonState stopButtonState;
    ButtonState cameraButtonState;
    ButtonState removeButtonState;

    ButtonState acceptRoiButtonState;
    ButtonState clearRoiButtonState;

    ButtonState okButtonState;
    ButtonState cancelButtonState;
};

class AppState {
  public:
    AppState();
    AppState(ModelPtr model);

    CapturePanelState getCameraPanelState(ModelPtr model);
    CalibrationPanelState getCalibrationPanelState(ModelPtr model);
    ManualCalibrationPanelState getManualCalibrationPanelState(ModelPtr model);
    ColorCalibrationPanelState getColorCalibrationPanelState(ModelPtr model);
    RoiPanelState getRoiPanelState(ModelPtr model);

  public:
    CapturePanelState cameraPanel;
    CalibrationPanelState calibrationPanel;
    ManualCalibrationPanelState manualCalibrationPanel;
    ColorCalibrationPanelState colorCalibrationPanel;
    RoiPanelState roiPanel;

  private:
    PanelState getCameraStatusState(ModelPtr model);
    PanelState getCalibrationStatusState(ModelPtr model);
    PanelState getRoiStatusState(ModelPtr model);

    // Capture Panel
    ButtonState getCaptureButtonState(ModelPtr model);
    ButtonState getLoadButtonState(ModelPtr model);
    ButtonState getCameraButtonState(ModelPtr model);
    ButtonState getReplayButtonState(ModelPtr model);
    ButtonState getRemoveButtonState(ModelPtr model);

    // Capture Panel -> Calibration
    ButtonState getCPCalibrationButtonState(ModelPtr model);
    ButtonState getCPCalibrationRemoveButtonState(ModelPtr model);

    // Capture Panel -> ROI
    ButtonState getCPROIButtonState(ModelPtr model);
    ButtonState getCPROIRemoveButtonState(ModelPtr model);

    // Capture Panel -> Measure
    ButtonState getCPMeasureButtonState(ModelPtr model);

    // Calibration Panel
    ButtonState getCalibrationRemoveButtonState(ModelPtr model);
    ButtonState getCalibrationButtonState(ModelPtr model);
    ButtonState getCLCameraButtonState(ModelPtr model);

    // Calibration Panel -> Tools
    ButtonState getSelectPointButtonState(ModelPtr model);
    ButtonState getCancelCalibrationButtonState(ModelPtr model);
    ButtonState getAcceptCalibrationButtonState(ModelPtr model);

    // Calibration Panel -> Recalibrate / Others
    ButtonState getRecalibrateColorButtonState(ModelPtr model);
    ButtonState getManualCalibrationButtonState(ModelPtr model);

    // Calibration Panel -> OK / Cancel
    ButtonState getCLOKButtonState(ModelPtr model);
    ButtonState getCLCancelButtonState(ModelPtr model);

    // Manual Calibration Panel
    ButtonState getMCButtonState(ModelPtr model);
    ButtonState getMCStopButtonState(ModelPtr model);
    ButtonState getMCCameraButtonState(ModelPtr model);
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
    ButtonState getROIStopButtonState(ModelPtr model);
    ButtonState getROICameraButtonState(ModelPtr model);
    ButtonState getROIRemoveButtonState(ModelPtr model);

    // ROI Panel -> Accept / Clear
    ButtonState getROIAcceptRoiButtonState(ModelPtr model);
    ButtonState getROIClearRoiButtonState(ModelPtr model);

    // ROI Panel -> OK / Cancel
    ButtonState getROIOKButtonState(ModelPtr model);
    ButtonState getROICancelButtonState(ModelPtr model);
};
