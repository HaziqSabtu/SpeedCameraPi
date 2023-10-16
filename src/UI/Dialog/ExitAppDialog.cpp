#include "UI/Dialog/ExitAppDialog.hpp"

ExitAppDialog::ExitAppDialog(wxWindow *parent)
    : DialogBaseYesNo(parent, Data::Dialog::ExitApp::Title,
                      Data::Dialog::ExitApp::Text) {
    shutdown_Button = new wxButton(this, wxID_ANY, "Shutdown");
    shutdown_ButtonID = shutdown_Button->GetId();

    buttonSizer->Add(shutdown_Button, 0, wxALL, 5);

    shutdown_Button->Bind(wxEVT_BUTTON, &ExitAppDialog::OnShutdownButton, this);
}

void ExitAppDialog::OnShutdownButton(wxCommandEvent &event) {
    result = true;
    EndModal(shutdown_ButtonID);
}

int ExitAppDialog::getShutdownButtonID() { return shutdown_ButtonID; }