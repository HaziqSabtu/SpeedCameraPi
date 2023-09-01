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

    vSizer = new wxBoxSizer(wxVERTICAL);
    vSizer->Add(topPadding, 0, wxEXPAND);
    vSizer->Add(buttonSizer, 0, wxEXPAND | wxALL, 10);
    vSizer->Add(bottomPadding, 0, wxEXPAND);

    hSizer = new wxBoxSizer(wxHORIZONTAL);
    hSizer->Add(leftPadding, 0, wxEXPAND);
    hSizer->Add(vSizer, 1, wxEXPAND);
    hSizer->Add(rightPadding, 0, wxEXPAND);

    SetSizer(hSizer);
    Fit();
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