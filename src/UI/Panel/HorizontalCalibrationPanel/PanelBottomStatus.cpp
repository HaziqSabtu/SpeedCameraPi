#include "UI/Button/BitmapButton/Button_Left.hpp"
#include "UI/Button/BitmapButton/Button_Remove.hpp"
#include "UI/Panel/Common/TextOutlinePanel.hpp"
#include "UI/StaticText/RichText.hpp"
#include "Utils/Enum.hpp"
#include <UI/Panel/HorizontalCalibrationPanel/PanelBottomStatus.hpp>

HorizontalCalibrationButtonBottom::HorizontalCalibrationButtonBottom(
    wxWindow *parent)
    : TextOutlinePanel(parent, RTC::BOTTOM_NONE) {

    Bottom_Button = new BitmapL(this, Enum::HC_SelectBottom_Button_ID);
    Clear_Button = new BitmapRemove(this, Enum::HC_RemoveBottom_Button_ID);

    buttonSizer = new wxBoxSizer(wxHORIZONTAL);
    buttonSizer->Add(Bottom_Button, 1, wxEXPAND);
    buttonSizer->Add(Clear_Button, 1, wxEXPAND);

    SetButtonSizer(buttonSizer);
}

void HorizontalCalibrationButtonBottom::OnButtonClicked(wxCommandEvent &e) {
    e.Skip();
}

void HorizontalCalibrationButtonBottom::update(const AppState &state) {
    // set panel
    HorizontalCalibrationPanelState ps = state.horizontalCalibrationPanel;

    setPanelState(ps.bottomStatusState);
    Bottom_Button->update(ps.selectBottomButtonState);
    Clear_Button->update(ps.removeBottomButtonState);
}

void HorizontalCalibrationButtonBottom::setPanelState(PanelState state) {
    if (state == PanelState::PANEL_OK) {
        this->Show();
        SetTextData(RTC::BOTTOM_OK);
        return;
    }

    if (state == PanelState::PANEL_NOT_OK) {
        this->Show();
        SetTextData(RTC::BOTTOM_NONE);
        return;
    }

    if (state == PanelState::PANEL_HIDDEN) {
        this->Hide();
        return;
    }

    throw std::runtime_error("Invalid panel state");
}
