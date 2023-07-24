#pragma once

enum ButtonState { NORMAL, ACTIVE, DISABLED };

enum PanelState { PANEL_NOT_OK, PANEL_OK };

struct CameraPanelState {
    PanelState state;
    ButtonState captureButtonState;
    ButtonState loadButtonState;
    ButtonState replayButtonState;
    ButtonState removeButtonState;
};

struct AppState {
    CameraPanelState cameraPanel;
};
