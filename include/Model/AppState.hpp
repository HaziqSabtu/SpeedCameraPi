#pragma once

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

struct AppState {
    CameraPanelState cameraPanel;
    CalibrationPanelState calibrationPanel;
};
