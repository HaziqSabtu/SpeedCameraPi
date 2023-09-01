#include "UI/Button/BitmapButton/Button_Next.hpp"
#include "UI/Button/BitmapButton/Button_Previous.hpp"
#include "UI/Panel/Common/TextOutlinePanel.hpp"
#include "UI/StaticText/RichText.hpp"
#include "Utils/Enum.hpp"
#include <UI/Panel/TrimDataPanel/PanelSetEnd.hpp>

TrimButtonSetEnd::TrimButtonSetEnd(wxWindow *parent)
    : TextOutlinePanel(parent, RTC::TRIM_END) {

    Next_Button = new BitmapNext(this, Enum::TD_IncrementEnd_Button_ID);
    Previous_Button = new BitmapPrevious(this, Enum::TD_DecrementEnd_Button_ID);

    buttonSizer = new wxBoxSizer(wxHORIZONTAL);
    buttonSizer->Add(Previous_Button, 1, wxEXPAND);
    buttonSizer->Add(Next_Button, 1, wxEXPAND);

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

void TrimButtonSetEnd::setPanelState(PanelState state) {
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

void TrimButtonSetEnd::OnButtonClicked(wxCommandEvent &e) { e.Skip(); }

void TrimButtonSetEnd::update(const AppState &state) {
    // set panel
    TrimDataPanelState ps = state.trimDataPanel;

    setPanelState(ps.endStatusState);
    Next_Button->update(ps.incEndButtonState);
    Previous_Button->update(ps.decEndButtonState);
}
