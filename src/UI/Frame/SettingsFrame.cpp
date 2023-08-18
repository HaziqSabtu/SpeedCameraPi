#include "UI/Layout/TitlePanel.hpp"
#include "UI/Panel/SettingsPanel/SettingsPanel.hpp"
#include "Utils/Config/ConfigStruct.hpp"
#include "Utils/Enum.hpp"
#include <UI/Frame/SettingsFrame.hpp>

SettingsFrame::SettingsFrame() : wxFrame(nullptr, wxID_ANY, "Settings") {
    ShowFullScreen(true);

    wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);

    title_panel = new TitlePanel(this, panel_id);
    sizer->Add(title_panel, 0, wxEXPAND | wxTOP | wxLEFT | wxRIGHT, 10);

    scrolled_panel = new SettingsScrollPanel(this);
    sizer->Add(scrolled_panel, 1, wxEXPAND | wxTOP | wxLEFT | wxRIGHT, 10);

    ok_cancel_panel = new OKCancelResetPanel(this);
    sizer->Add(ok_cancel_panel, 0, wxEXPAND | wxALL, 10);

    title_panel->exit_Button->setDisabled();
    title_panel->info_Button->setDisabled();
    SetSizer(sizer);

    SetBackgroundColour(Theme::Background);
}

void SettingsFrame::OnButton(wxCommandEvent &e) {
    if (e.GetId() == Enum::G_Setting_Button_ID) {
        CancelButtonHandler();
    }

    if (e.GetId() == Enum::G_OK_Button_ID) {
        OkButtonHandler();
    }

    if (e.GetId() == Enum::G_Cancel_Button_ID) {
        CancelButtonHandler();
    }

    if (e.GetId() == Enum::G_Reset_Button_ID) {
        ResetButtonHandler();
    }
}

void SettingsFrame::OkButtonHandler() {
    SettingsModel model = scrolled_panel->getSettingsModel();

    AppConfig c;
    c.SaveConfig(model);

    Close();
}

void SettingsFrame::CancelButtonHandler() {
    SettingsModel model = scrolled_panel->getSettingsModel();

    AppConfig c;

    if (c.GetSettingsModel() == model) {
        Close();
        return;
    }

    wxMessageDialog *dialog = new wxMessageDialog(
        this, "Do you want to save changes?", "Save Changes",
        wxYES_NO | wxCANCEL | wxICON_QUESTION);
    int result = dialog->ShowModal();

    if (result == wxID_NO) {
        Close();
        return;
    }

    OkButtonHandler();
}

void SettingsFrame::ResetButtonHandler() {
    SettingsModel model = scrolled_panel->getSettingsModel();

    AppConfig c;
    c.ResetConfig();

    auto new_model = c.GetSettingsModel();
    scrolled_panel->setSettingsModel(new_model);
}

BEGIN_EVENT_TABLE(SettingsFrame, wxFrame)
EVT_BUTTON(wxID_ANY, SettingsFrame::OnButton)
END_EVENT_TABLE()