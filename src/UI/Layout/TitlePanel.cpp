#include "UI/StaticText/Titletext.hpp"
#include <UI/Layout/TitlePanel.hpp>

TitlePanel::TitlePanel(wxWindow *parent, PanelID panelID)
    : wxPanel(parent, wxID_ANY),
      titleText(new TitleText(this, wxID_ANY, panelID)),
      exit_Button(new ButtonExit(this)) {

    sizer = new wxBoxSizer(wxHORIZONTAL);
    sizer->Add(titleText->sizer, 1, wxEXPAND);
    sizer->Add(exit_Button, 0, wxEXPAND);

    this->SetSizer(sizer);
}

TitlePanel::TitlePanel(wxWindow *parent, PanelID panelID, TitleText *titleText,
                       ButtonExit *exit_Button)
    : wxPanel(parent, wxID_ANY), titleText(titleText),
      exit_Button(exit_Button) {

    sizer = new wxBoxSizer(wxHORIZONTAL);
    sizer->Add(titleText->sizer, 1, wxEXPAND);
    sizer->Add(exit_Button, 0, wxEXPAND);

    this->SetSizer(sizer);
}

TitlePanel::~TitlePanel() {}