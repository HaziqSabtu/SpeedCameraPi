#include "UI/StaticText/Titletext.hpp"
#include <UI/Layout/TitlePanel.hpp>

TitlePanel::TitlePanel(wxWindow *parent, PanelID panelID)
    : wxPanel(parent, wxID_ANY),
      titleText(new TitleText(this, wxID_ANY, panelID)),
      exit_Button(new ButtonExit(this)),
      setting_Button(new ButtonSettings(this)),
      info_Button(new ButtonInfo(this)) {

    addComponentsToSizer();
}

TitlePanel::TitlePanel(wxWindow *parent, PanelID panelID, TitleText *titleText,
                       ButtonExit *exit_Button, ButtonSettings *setting_Button,
                       ButtonInfo *info_Button)
    : wxPanel(parent, wxID_ANY), titleText(titleText), exit_Button(exit_Button),
      setting_Button(setting_Button), info_Button(new ButtonInfo(this)) {

    addComponentsToSizer();
}

TitlePanel::~TitlePanel() {}

void TitlePanel::addComponentsToSizer() {
    sizer = new wxBoxSizer(wxHORIZONTAL);

    sizer->Add(titleText->sizer, 1, wxEXPAND);
    sizer->Add(info_Button, 0, wxEXPAND | wxRIGHT, 5);
    sizer->Add(setting_Button, 0, wxEXPAND | wxRIGHT, 5);
    sizer->Add(exit_Button, 0, wxEXPAND);

    this->SetSizer(sizer);
}