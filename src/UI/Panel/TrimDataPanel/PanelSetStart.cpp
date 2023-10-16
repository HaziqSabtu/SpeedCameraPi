#include "Model/AppState.hpp"
#include "UI/Button/BitmapButton/Button_Next.hpp"
#include "UI/Button/BitmapButton/Button_Previous.hpp"
#include "UI/Panel/Common/TextOutlinePanel.hpp"
#include "UI/StaticText/RichText.hpp"
#include "Utils/Enum.hpp"
#include <UI/Panel/TrimDataPanel/PanelSetStart.hpp>

TrimButtonSetStart::TrimButtonSetStart(wxWindow *parent)
    : TextOutlinePanel(parent, RTC::TRIM_START) {

    Next_Button = new BitmapNext(this, Enum::TD_IncrementStart_Button_ID);
    Previous_Button =
        new BitmapPrevious(this, Enum::TD_DecrementStart_Button_ID);

    buttonSizer = new wxBoxSizer(wxHORIZONTAL);
    buttonSizer->Add(Previous_Button, 1, wxEXPAND);
    buttonSizer->Add(Next_Button, 1, wxEXPAND);

    SetButtonSizer(buttonSizer);
}

void TrimButtonSetStart::setPanelState(PanelState state) {
    if (state == PanelState::PANEL_OK) {
        this->Show();
        return;
    }

    if (state == PanelState::PANEL_NOT_OK) {
        this->Show();
        return;
    }

    if (state == PanelState::PANEL_HIDDEN) {
        this->Hide();
        return;
    }

    throw std::runtime_error("Invalid panel state");
}

void TrimButtonSetStart::OnButtonClicked(wxCommandEvent &e) { e.Skip(); }

void TrimButtonSetStart::update(const AppState &state) {
    // set panel
    TrimDataPanelState ps = state.trimDataPanel;

    setPanelState(ps.startStatusState);
    Next_Button->update(ps.incStartButtonState);
    Previous_Button->update(ps.decStartButtonState);
}
