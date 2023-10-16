#include <UI/Layout/StatusPanel.hpp>
#include <wx/gdicmn.h>

StatusPanel::StatusPanel(wxWindow *parent, wxString stat)
    : wxPanel(parent, wxID_ANY, wxDefaultPosition, wxSize(50, 50)),
      statusText(new StatusText(this, wxID_ANY, stat)) {

    SetBackgroundColour(statusText->GetBackgroundColour());

    vSizer = new wxBoxSizer(wxVERTICAL);
    vSizer->AddStretchSpacer();
    vSizer->Add(statusText, 0, wxEXPAND);
    vSizer->AddStretchSpacer();

    emptySpacerLeft = new wxStaticText(this, wxID_ANY, wxEmptyString,
                                       wxDefaultPosition, wxSize(12, 12));

    emptySpacerRight = new wxStaticText(this, wxID_ANY, wxEmptyString,
                                        wxDefaultPosition, wxSize(12, 12));

    hSizer = new wxBoxSizer(wxHORIZONTAL);
    hSizer->Add(emptySpacerLeft, 0, wxEXPAND);
    hSizer->Add(vSizer, 1, wxEXPAND);
    hSizer->Add(emptySpacerRight, 0, wxEXPAND);
    this->SetSizer(hSizer);
}

StatusPanel::~StatusPanel() {}

void StatusPanel::SetText(wxString text) { statusText->SetText(text); }