#include "UI/Layout/TitlePanel.hpp"
#include "UI/Panel/SettingsPanel/SettingsPanel.hpp"
#include "Utils/Config/ConfigStruct.hpp"
#include "Utils/Enum.hpp"
#include <UI/Button/TextButton/Button_Back.hpp>
#include <UI/Frame/InfoFrame.hpp>

InfoFrame::InfoFrame() : wxFrame(nullptr, wxID_ANY, "Settings") {
    ShowFullScreen(true);

    wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);

    title_panel = new TitlePanel(this, panel_id);
    sizer->Add(title_panel, 0, wxEXPAND | wxTOP | wxLEFT | wxRIGHT, 10);

    info_panel = new InfoPanel(this, wxID_ANY);
    sizer->Add(info_panel, 1, wxEXPAND | wxTOP | wxLEFT | wxRIGHT, 10);
    // scrolled_panel = new SettingsScrollPanel(this);
    // sizer->Add(scrolled_panel, 1, wxEXPAND | wxTOP | wxLEFT | wxRIGHT, 10);

    back_button = new BackTextButton(this, wxID_ANY);
    sizer->Add(back_button, 0, wxEXPAND | wxTOP | wxLEFT | wxRIGHT, 10);

    title_panel->exit_Button->setDisabled();
    title_panel->setting_Button->setDisabled();
    SetSizer(sizer);

    SetBackgroundColour(Theme::Background);
}

void InfoFrame::OnButton(wxCommandEvent &e) { Close(); }

BEGIN_EVENT_TABLE(InfoFrame, wxFrame)
EVT_BUTTON(wxID_ANY, InfoFrame::OnButton)
END_EVENT_TABLE()