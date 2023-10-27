#include "Model/AppState.hpp"
#include "UI/Button/BitmapButton/Button_ColorPicker.hpp"
#include "UI/Button/BitmapButton/Button_Reset.hpp"
#include "UI/Button/BitmapButton/Button_Save.hpp"
#include "UI/Button/BitmapButton/Button_User.hpp"
#include "UI/Data/Data.hpp"
#include "Utils/Enum.hpp"
#include <UI/Panel/ColorCalibrationPanel/PanelStatusOther.hpp>

ColorCalibrationButtonOther::ColorCalibrationButtonOther(wxWindow *parent)
    : TextOutlinePanel(parent, RTC::CALIB_OTHER) {

    Restore_button =
        new BitmapReset(this, Enum::CC_Restore_Button_ID, Data::BitmapRestore);

    buttonSizer = new wxBoxSizer(wxHORIZONTAL);
    buttonSizer->Add(Restore_button, 1, wxEXPAND);

    SetButtonSizer(buttonSizer);
}

void ColorCalibrationButtonOther::update(const AppState &state) {
    // set panel
    ColorCalibrationPanelState ps = state.colorCalibrationPanel;
    setPanelState(ps.otherStatusState);

    Restore_button->update(ps.restoreButtonState);
}

void ColorCalibrationButtonOther::setPanelState(PanelState state) {
    if (state == PanelState::PANEL_OK) {
        this->Show();
    }

    if (state == PanelState::PANEL_NOT_OK) {
        this->Show();
    }

    if (state == PanelState::PANEL_HIDDEN) {
        this->Hide();
    }
}