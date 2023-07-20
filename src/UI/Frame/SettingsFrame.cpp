#include <UI/Frame/SettingsFrame.hpp>

SettingsFrame::SettingsFrame() : wxFrame(nullptr, wxID_ANY, "Settings") {
    ShowFullScreen(true);

    wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);
    wxStaticText *text =
        new wxStaticText(this, wxID_ANY, "Not implemented for now");
    sizer->Add(text, 0, wxALIGN_CENTER | wxALL, 20);

    wxButton *closeButton = new wxButton(this, wxID_ANY, "Close Settings");
    closeButton->Bind(wxEVT_BUTTON, &SettingsFrame::OnButton, this);
    sizer->Add(closeButton, 0, wxALIGN_CENTER | wxALL, 10);

    SetSizer(sizer);
}

void SettingsFrame::OnButton(wxCommandEvent &e) { Close(); }

BEGIN_EVENT_TABLE(SettingsFrame, wxFrame)
EVT_BUTTON(wxID_ANY, SettingsFrame::OnButton)
END_EVENT_TABLE()