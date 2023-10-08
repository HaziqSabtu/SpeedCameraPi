#include "UI/Button/BitmapButton/Button_Remove.hpp"
#include "UI/Button/BitmapButton/Button_Right.hpp"
#include "UI/Button/BitmapButton/Button_Top.hpp"
#include "UI/Panel/Common/TextOutlinePanel.hpp"
#include "UI/StaticText/RichText.hpp"
#include "Utils/Enum.hpp"
#include <UI/Panel/HorizontalCalibrationPanel/PanelTopStatus.hpp>

HorizontalCalibrationButtonTop::HorizontalCalibrationButtonTop(wxWindow *parent)
    : TextOutlinePanel(parent, RTC::TOP_NONE) {

    Top_Button = new BitmapT(this, Enum::HC_SelectTop_Button_ID);
    Clear_Button = new BitmapRemove(this, Enum::HC_RemoveTop_Button_ID);

    buttonSizer = new wxBoxSizer(wxHORIZONTAL);
    buttonSizer->Add(Top_Button, 1, wxEXPAND);
    buttonSizer->Add(Clear_Button, 1, wxEXPAND);

    SetButtonSizer(buttonSizer);
}

void HorizontalCalibrationButtonTop::OnButtonClicked(wxCommandEvent &e) {
    e.Skip();
}

void HorizontalCalibrationButtonTop::update(const AppState &state) {
    // set panel
    HorizontalCalibrationPanelState ps = state.horizontalCalibrationPanel;

    setPanelState(ps.topStatusState);
    Top_Button->update(ps.selectTopButtonState);
    Clear_Button->update(ps.removeTopButtonState);
}

void HorizontalCalibrationButtonTop::setPanelState(PanelState state) {
    if (state == PanelState::PANEL_OK) {
        this->Show();
        SetTextData(RTC::TOP_OK);
        return;
    }

    if (state == PanelState::PANEL_NOT_OK) {
        this->Show();
        SetTextData(RTC::TOP_NONE);
        return;
    }

    if (state == PanelState::PANEL_HIDDEN) {
        this->Hide();
        return;
    }

    throw std::runtime_error("Invalid panel state");
}
