#include "UI/Button/BitmapButton/Button_ColorPicker.hpp"
#include "UI/Button/BitmapButton/Button_User.hpp"
#include "Utils/Enum.hpp"
#include <UI/Panel/CalibrationPanel/PanelStatusOther.hpp>

CalibrationButtonOther::CalibrationButtonOther(wxWindow *parent)
    : TextOutlinePanel(parent, RTC::CALIB_OTHER) {

    ColorCalibration_Button =
        new BitmapColorPicker(this, Enum::CL_ChangeColor_Button_ID);
    ManualCalibration_Button =
        new BitmapUser(this, Enum::CL_ChangeManual_Button_ID);

    buttonSizer = new wxBoxSizer(wxHORIZONTAL);
    buttonSizer->Add(ColorCalibration_Button, 1, wxEXPAND);
    buttonSizer->Add(ManualCalibration_Button, 1, wxEXPAND);

    SetButtonSizer(buttonSizer);
}

void CalibrationButtonOther::update(const AppState &state) {
    // set panel
    CalibrationPanelState ps = state.calibrationPanel;

    setPanelState(ps.otherStatusState);

    ColorCalibration_Button->update(ps.recalibrateColorButtonState);
    ManualCalibration_Button->update(ps.manualCalibrationButtonState);
}

void CalibrationButtonOther::setPanelState(PanelState state) {
    if (state == PanelState::PANEL_HIDDEN) {
        this->Hide();
        return;
    }

    if (state == PanelState::PANEL_OK) {
        this->Show();
        return;
    }

    throw std::runtime_error("Invalid panel state");
}