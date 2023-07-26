#pragma once

#include "Model/SharedModel.hpp"
#include <memory>
enum ButtonState { NORMAL, ACTIVE, DISABLED, ON, OFF };

enum PanelState { PANEL_NOT_OK, PANEL_OK };

#define modelPtr std::shared_ptr<SharedModel>

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
    AppState(modelPtr model);

    CameraPanelState getCameraPanelState(modelPtr model);
    CalibrationPanelState getCalibrationPanelState(modelPtr model);

  public:
    CameraPanelState cameraPanel;
    CalibrationPanelState calibrationPanel;

  private:
    ButtonState getCaptureButtonState(modelPtr model);
    ButtonState getLoadButtonState(modelPtr model);
    ButtonState getReplayButtonState(modelPtr model);
    ButtonState getRemoveButtonState(modelPtr model);
    ButtonState getRemoveButtonState2(modelPtr model);
    ButtonState getCameraButtonState(modelPtr model);
    ButtonState getCalibrationButtonState(modelPtr model);
};
