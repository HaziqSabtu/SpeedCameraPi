#include <UI/Panel/ResultPanel/SpeedPanel.hpp>
#include <wx/gdicmn.h>
#include <wx/stringimpl.h>

SpeedPanel::SpeedPanel(wxWindow *parent)
    : wxPanel(parent, wxID_ANY, wxDefaultPosition, wxSize(50, 50)) {

    statusText = new StatusText(this, wxID_ANY, "NONE", wxDefaultPosition,
                                wxDefaultSize, wxALIGN_CENTER_HORIZONTAL);
    Spacer *spacer1 = new Spacer(this);
    spacer1->SetBackgroundColour(statusText->GetBackgroundColour());
    Spacer *spacer2 = new Spacer(this);
    spacer2->SetBackgroundColour(statusText->GetBackgroundColour());

    vSizer = new wxBoxSizer(wxVERTICAL);
    vSizer->Add(spacer1, 1, wxEXPAND);
    vSizer->Add(statusText, 1, wxEXPAND);
    vSizer->Add(spacer2, 1, wxEXPAND);

    hSizer = new wxBoxSizer(wxHORIZONTAL);
    hSizer->AddStretchSpacer();
    hSizer->Add(vSizer, 1, wxEXPAND);
    this->SetSizer(hSizer);
}

SpeedPanel::~SpeedPanel() {}

void SpeedPanel::SetSpeed(double Speed) {
    wxString value = wxString::Format("%.2f", Speed) + " km/h";
    statusText->SetText(value);
}

void SpeedPanel::update(const AppState &state) {
    // set panel
    ResultPanelState ps = state.resultPanel;
    setPanelState(ps.speedStatusState);
}

void SpeedPanel::setPanelState(PanelState state) {
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
