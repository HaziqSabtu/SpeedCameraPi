#include "UI/Button/BitmapButton/Button_Bottom.hpp"
#include "UI/Button/BitmapButton/Button_Left.hpp"
#include "UI/Button/BitmapButton/Button_Remove.hpp"
#include "UI/Panel/Common/TextOutlinePanel.hpp"
#include "UI/StaticText/RichText.hpp"
#include "Utils/Enum.hpp"
#include <UI/Panel/DistanceCalibrationPanel/PanelBottomStatus.hpp>

DistanceCalibrationButtonBottom::DistanceCalibrationButtonBottom(
    wxWindow *parent)
    : TextOutlinePanel(parent, RTC::BOTTOM_NONE) {

    Bottom_Button = new BitmapB(this, Enum::DC_SelectBottom_Button_ID);
    Clear_Button = new BitmapRemove(this, Enum::DC_RemoveBottom_Button_ID);

    buttonSizer = new wxBoxSizer(wxHORIZONTAL);
    buttonSizer->Add(Bottom_Button, 1, wxEXPAND);
    buttonSizer->Add(Clear_Button, 1, wxEXPAND);

    SetButtonSizer(buttonSizer);
}

void DistanceCalibrationButtonBottom::OnButtonClicked(wxCommandEvent &e) {
    e.Skip();
}

void DistanceCalibrationButtonBottom::update(const AppState &state) {
    // set panel
    DistanceCalibrationPanelState ps = state.distanceCalibrationPanel;

    setPanelState(ps.bottomStatusState);
    Bottom_Button->update(ps.selectBottomButtonState);
    Clear_Button->update(ps.removeBottomButtonState);
}

void DistanceCalibrationButtonBottom::setPanelState(PanelState state) {
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
