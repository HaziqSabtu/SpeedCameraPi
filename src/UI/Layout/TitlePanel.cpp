#include "UI/StaticText/Titletext.hpp"
#include <UI/Layout/TitlePanel.hpp>

/**
 * @brief Construct a new Title Panel:: Title Panel object
 *
 * @param parent Pointer to the parent window
 * @param panelID ID of the panel
 */
TitlePanel::TitlePanel(wxWindow *parent, PanelID panelID)
    : wxPanel(parent, wxID_ANY),
      titleText(new TitleText(this, wxID_ANY, panelID)),
      exit_Button(new ButtonExit(this)),
      setting_Button(new ButtonSettings(this)),
      info_Button(new ButtonInfo(this)),
      switchMode_Button(new ButtonSwitchMode(this)) {

    addComponentsToSizer();

    if (panelID != PanelID::PANEL_CAPTURE) {
        switchMode_Button->Hide();
    }
}

/**
 * @brief Construct a new Title Panel:: Title Panel object
 *
 * @param parent Pointer to the parent window
 * @param panelID ID of the panel
 * @param titleText Pointer to the title text
 * @param exit_Button Pointer to the exit button
 * @param setting_Button Pointer to the setting button
 * @param info_Button Pointer to the info button
 * @param switchMode_Button Pointer to the switch mode button
 */
TitlePanel::TitlePanel(wxWindow *parent, PanelID panelID, TitleText *titleText,
                       ButtonExit *exit_Button, ButtonSettings *setting_Button,
                       ButtonInfo *info_Button,
                       ButtonSwitchMode *switchMode_Button)
    : wxPanel(parent, wxID_ANY), titleText(titleText), exit_Button(exit_Button),
      setting_Button(setting_Button), info_Button(info_Button),
      switchMode_Button(switchMode_Button) {

    addComponentsToSizer();

    if (panelID != PanelID::PANEL_CAPTURE) {
        switchMode_Button->Hide();
    }
}

/**
 * @brief Destroy the Title Panel:: Title Panel object
 *
 */
TitlePanel::~TitlePanel() {}

/**
 * @brief process sizer
 *
 */
void TitlePanel::addComponentsToSizer() {
    sizer = new wxBoxSizer(wxHORIZONTAL);

    sizer->Add(titleText->sizer, 1, wxEXPAND);
    sizer->Add(switchMode_Button, 0, wxEXPAND | wxRIGHT, 5);
    sizer->Add(info_Button, 0, wxEXPAND | wxRIGHT, 5);
    sizer->Add(setting_Button, 0, wxEXPAND | wxRIGHT, 5);
    sizer->Add(exit_Button, 0, wxEXPAND);

    this->SetSizer(sizer);
}