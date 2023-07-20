#include <UI/Frame/InfoFrame.hpp>

InfoFrame::InfoFrame() : wxFrame(nullptr, wxID_ANY, "Info") {
    ShowFullScreen(true);

    wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);
    wxStaticText *text = new wxStaticText(
        this, wxID_ANY, "Info Frame --- Not implemented for now");
    sizer->Add(text, 0, wxALIGN_CENTER | wxALL, 20);

    wxButton *closeButton = new wxButton(this, wxID_ANY, "Close Info");
    closeButton->Bind(wxEVT_BUTTON, &InfoFrame::OnButton, this);
    sizer->Add(closeButton, 0, wxALIGN_CENTER | wxALL, 10);

    SetSizer(sizer);
}

void InfoFrame::OnButton(wxCommandEvent &e) { Close(); }

BEGIN_EVENT_TABLE(InfoFrame, wxFrame)
EVT_BUTTON(wxID_ANY, InfoFrame::OnButton)
END_EVENT_TABLE()