#include <UI/Panel2.hpp>

Panel2::Panel2(wxWindow *parent, wxWindowID id) : wxPanel(parent, id) {
    wxButton *button = new wxButton(this, wxID_ANY, "Button");
    wxBoxSizer *sizer = new wxBoxSizer(wxHORIZONTAL);
    sizer->Add(button, 0, wxALL, 5);
    SetSizer(sizer);
};

void Panel2::OnButton(wxCommandEvent &e) {
    wxNotebook *notebook = (wxNotebook *)FindWindowById(Enum::NOTEBOOK_ID);
    notebook->SetSelection(0);
}

// clang-format off
wxBEGIN_EVENT_TABLE(Panel2, wxPanel) 
EVT_BUTTON(wxID_ANY, Panel2::OnButton)
wxEND_EVENT_TABLE()
