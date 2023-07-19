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

    hSizer = new wxBoxSizer(wxHORIZONTAL);
    hSizer->Add(vSizer, 1, wxEXPAND);
    this->SetSizer(hSizer);
}

StatusPanel::~StatusPanel() {}