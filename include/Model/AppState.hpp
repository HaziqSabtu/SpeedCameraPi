#pragma once

#include "Model/SharedModel.hpp"
#include <memory>
enum ButtonState { NORMAL, ACTIVE, DISABLED, ON, OFF };

enum PanelState { PANEL_NOT_OK, PANEL_OK };

struct CameraPanelState {
    PanelState state;
    ButtonState captureButtonState;
    ButtonState loadButtonState;
    ButtonState replayButtonState;
    ButtonState removeButtonState;
    ButtonState cameraButtonState;
};

struct CalibrationPanelState {
    PanelState state;

    ButtonState calibrationButtonState;
    ButtonState removeButtonState;
    ButtonState cameraButtonState;
};

class AppState {
  public:
    AppState();
    AppState(ModelPtr model);

    CameraPanelState getCameraPanelState(ModelPtr model);
    CalibrationPanelState getCalibrationPanelState(ModelPtr model);

  public:
    CameraPanelState cameraPanel;
    CalibrationPanelState calibrationPanel;

  private:
    ButtonState getCaptureButtonState(ModelPtr model);
    ButtonState getLoadButtonState(ModelPtr model);
    ButtonState getReplayButtonState(ModelPtr model);
    ButtonState getRemoveButtonState(ModelPtr model);
    ButtonState getRemoveButtonState2(ModelPtr model);
    ButtonState getCameraButtonState(ModelPtr model);
    ButtonState getCalibrationButtonState(ModelPtr model);
};
