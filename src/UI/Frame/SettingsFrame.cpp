#include "UI/Layout/TitlePanel.hpp"
#include "Utils/Enum.hpp"
#include <UI/Frame/SettingsFrame.hpp>

SettingsFrame::SettingsFrame() : wxFrame(nullptr, wxID_ANY, "Settings") {
    ShowFullScreen(true);

    wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);

    title_panel = new TitlePanel(this, panel_id);
    title_panel->exit_Button->setDisabled();
    title_panel->info_Button->setDisabled();

    sizer->Add(title_panel, 0, wxEXPAND | wxTOP | wxLEFT | wxRIGHT, 10);

    wxStaticText *text =
        new wxStaticText(this, wxID_ANY, "Not implemented for now");
    sizer->Add(text, 0, wxALIGN_CENTER | wxALL, 20);

    wxButton *closeButton = new wxButton(this, wxID_ANY, "Close Settings");
    closeButton->Bind(wxEVT_BUTTON, &SettingsFrame::OnButton, this);
    sizer->Add(closeButton, 0, wxALIGN_CENTER | wxALL, 10);

    SetSizer(sizer);
}

void SettingsFrame::OnButton(wxCommandEvent &e) {
    if (e.GetId() == Enum::G_Setting_Button_ID) {
        Close();
    }
}

BEGIN_EVENT_TABLE(SettingsFrame, wxFrame)
EVT_BUTTON(wxID_ANY, SettingsFrame::OnButton)
END_EVENT_TABLE()