#include "UI/Button/BitmapButton/Button_ColorPicker.hpp"
#include "UI/Button/BitmapButton/Button_User.hpp"
#include "Utils/Enum.hpp"
#include <UI/Panel/LaneCalibrationPanel/PanelStatusOther.hpp>

LaneCalibrationButtonOther::LaneCalibrationButtonOther(wxWindow *parent)
    : TextOutlinePanel(parent, RTC::CALIB_OTHER) {

    ColorCalibration_Button =
        new BitmapColorPicker(this, Enum::LC_ChangeColor_Button_ID);

    buttonSizer = new wxBoxSizer(wxHORIZONTAL);
    buttonSizer->Add(ColorCalibration_Button, 1, wxEXPAND);

    SetButtonSizer(buttonSizer);
}

void LaneCalibrationButtonOther::update(const AppState &state) {
    LaneCalibrationPanelState ps = state.laneCalibrationPanel;

    setPanelState(ps.otherStatusState);
    ColorCalibration_Button->update(ps.recalibrateColorButtonState);
}

void LaneCalibrationButtonOther::setPanelState(PanelState state) {
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