#include "UI/Button/BitmapButton/Button_ColorPicker.hpp"
#include "UI/Button/BitmapButton/Button_User.hpp"
#include "Utils/Enum.hpp"
#include <UI/Panel/CalibrationPanel/PanelStatusOther.hpp>

CalibrationOtherPanel::CalibrationOtherPanel(wxWindow *parent)
    : TextOutlinePanel(parent, RTC::CALIB_OTHER) {

    recalibrate_button =
        new BitmapColorPicker(this, Enum::CL_ChangeColor_Button_ID);
    manual_button = new BitmapUser(this, Enum::CL_ChangeManual_Button_ID);

    buttonSizer = new wxBoxSizer(wxHORIZONTAL);
    buttonSizer->Add(recalibrate_button, 1, wxEXPAND);
    buttonSizer->Add(manual_button, 1, wxEXPAND);

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

void CalibrationOtherPanel::update(const AppState &state) {
    // set panel
    CalibrationPanelState ps = state.calibrationPanel;

    recalibrate_button->update(ps.recalibrateColorButtonState);
    manual_button->update(ps.manualCalibrationButtonState);
}