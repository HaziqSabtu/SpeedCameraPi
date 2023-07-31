#include "Model/AppState.hpp"
#include "UI/Button/BitmapButton/Button_ColorPicker.hpp"
#include "UI/Button/BitmapButton/Button_Reset.hpp"
#include "UI/Button/BitmapButton/Button_Save.hpp"
#include "UI/Button/BitmapButton/Button_User.hpp"
#include "UI/Theme/Data.hpp"
#include "Utils/Enum.hpp"
#include <UI/Panel/ColorCalibrationPanel/PanelStatusOther.hpp>

ColorCalibrationOtherPanel::ColorCalibrationOtherPanel(wxWindow *parent)
    : TextOutlinePanel(parent, RTC::CALIB_OTHER) {

    save_button = new BitmapSave(this, Enum::CC_Save_Button_ID);
    restore_button =
        new BitmapReset(this, Enum::CC_Restore_Button_ID, Data::BitmapRestore);

    buttonSizer = new wxBoxSizer(wxHORIZONTAL);
    buttonSizer->Add(save_button, 1, wxEXPAND);
    buttonSizer->Add(restore_button, 1, wxEXPAND);

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

void ColorCalibrationOtherPanel::update(const AppState &state) {
    // set panel
    ColorCalibrationPanelState ps = state.colorCalibrationPanel;

    save_button->update(ps.saveButtonState);
    restore_button->update(ps.restoreButtonState);
}