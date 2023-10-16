#include "UI/Button/BitmapButton/Button_Remove.hpp"
#include "UI/Button/BitmapButton/Button_Right.hpp"
#include "UI/Panel/Common/TextOutlinePanel.hpp"
#include "UI/StaticText/RichText.hpp"
#include "Utils/Enum.hpp"
#include <UI/Panel/ManualCalibrationPanel/PanelRightStatus.hpp>

ManualCalibrationButtonRight::ManualCalibrationButtonRight(wxWindow *parent)
    : TextOutlinePanel(parent, RTC::RIGHT_NONE) {

    Right_Button = new BitmapR(this, Enum::MC_SelectRight_Button_ID);
    Clear_Button = new BitmapRemove(this, Enum::MC_RemoveRight_Button_ID);

    buttonSizer = new wxBoxSizer(wxHORIZONTAL);
    buttonSizer->Add(Right_Button, 1, wxEXPAND);
    buttonSizer->Add(Clear_Button, 1, wxEXPAND);

    SetButtonSizer(buttonSizer);
}

void ManualCalibrationButtonRight::OnButtonClicked(wxCommandEvent &e) {
    e.Skip();
}

void ManualCalibrationButtonRight::update(const AppState &state) {
    // set panel
    ManualCalibrationPanelState ps = state.manualCalibrationPanel;

    setPanelState(ps.rightStatusState);
    Right_Button->update(ps.selectRightButtonState);
    Clear_Button->update(ps.removeRightButtonState);
}

void ManualCalibrationButtonRight::setPanelState(PanelState state) {
    if (state == PanelState::PANEL_OK) {
        this->Show();
        SetTextData(RTC::RIGHT_OK);
        return;
    }

    if (state == PanelState::PANEL_NOT_OK) {
        this->Show();
        SetTextData(RTC::RIGHT_NONE);
        return;
    }

    if (state == PanelState::PANEL_HIDDEN) {
        this->Hide();
        return;
    }

    throw std::runtime_error("Invalid panel state");
}
