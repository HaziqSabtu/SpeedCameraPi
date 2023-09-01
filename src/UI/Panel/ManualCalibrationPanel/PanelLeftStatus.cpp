#include "UI/Button/BitmapButton/Button_Left.hpp"
#include "UI/Button/BitmapButton/Button_Remove.hpp"
#include "UI/Panel/Common/TextOutlinePanel.hpp"
#include "UI/StaticText/RichText.hpp"
#include "Utils/Enum.hpp"
#include <UI/Panel/ManualCalibrationPanel/PanelLeftStatus.hpp>

ManualCalibrationButtonLeft::ManualCalibrationButtonLeft(wxWindow *parent)
    : TextOutlinePanel(parent, RTC::LEFT_NONE) {

    Left_Button = new BitmapL(this, Enum::MC_SelectLeft_Button_ID);
    Clear_Button = new BitmapRemove(this, Enum::MC_RemoveLeft_Button_ID);

    buttonSizer = new wxBoxSizer(wxHORIZONTAL);
    buttonSizer->Add(Left_Button, 1, wxEXPAND);
    buttonSizer->Add(Clear_Button, 1, wxEXPAND);

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

void ManualCalibrationButtonLeft::OnButtonClicked(wxCommandEvent &e) {
    e.Skip();
}

void ManualCalibrationButtonLeft::update(const AppState &state) {
    // set panel
    ManualCalibrationPanelState ps = state.manualCalibrationPanel;

    setPanelState(ps.leftStatusState);
    Left_Button->update(ps.selectLeftButtonState);
    Clear_Button->update(ps.removeLeftButtonState);
}

void ManualCalibrationButtonLeft::setPanelState(PanelState state) {
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
