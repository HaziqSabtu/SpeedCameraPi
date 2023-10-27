#include "UI/Button/BitmapButton/Button_Left.hpp"
#include "UI/Button/BitmapButton/Button_Remove.hpp"
#include "UI/Panel/Common/TextOutlinePanel.hpp"
#include "UI/StaticText/RichText.hpp"
#include "Utils/Enum.hpp"
#include <UI/Panel/LaneManualCalibrationPanel/PanelLeftStatus.hpp>

LaneManualCalibrationButtonLeft::LaneManualCalibrationButtonLeft(
    wxWindow *parent)
    : TextOutlinePanel(parent, RTC::LEFT_NONE) {

    Left_Button = new BitmapL(this, Enum::LM_SelectLeft_Button_ID);
    Clear_Button = new BitmapRemove(this, Enum::LM_RemoveLeft_Button_ID);

    buttonSizer = new wxBoxSizer(wxHORIZONTAL);
    buttonSizer->Add(Left_Button, 1, wxEXPAND);
    buttonSizer->Add(Clear_Button, 1, wxEXPAND);

    SetButtonSizer(buttonSizer);
}

void LaneManualCalibrationButtonLeft::OnButtonClicked(wxCommandEvent &e) {
    e.Skip();
}

void LaneManualCalibrationButtonLeft::update(const AppState &state) {
    // set panel
    LaneManualCalibrationPanelState ps = state.laneManualCalibrationPanel;

    setPanelState(ps.leftStatusState);
    Left_Button->update(ps.selectLeftButtonState);
    Clear_Button->update(ps.removeLeftButtonState);
}

void LaneManualCalibrationButtonLeft::setPanelState(PanelState state) {
    if (state == PanelState::PANEL_OK) {
        this->Show();
        SetTextData(RTC::LEFT_OK);
        return;
    }

    if (state == PanelState::PANEL_NOT_OK) {
        this->Show();
        SetTextData(RTC::LEFT_NONE);
        return;
    }

    if (state == PanelState::PANEL_HIDDEN) {
        this->Hide();
        return;
    }

    throw std::runtime_error("Invalid panel state");
}
