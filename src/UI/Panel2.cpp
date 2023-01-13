#include <UI/Panel2.hpp>

Panel2::Panel2(wxWindow *parent, wxWindowID id) : wxPanel(parent, id) {
    wxButton *next_button = new wxButton(this, Enum::NEXT_PANEL_ID, "Next");
    wxButton *prev_button = new wxButton(this, Enum::PREV_PANEL_ID, "Prev");
    wxBoxSizer *sizer = new wxBoxSizer(wxHORIZONTAL);
    sizer->Add(next_button, 0, wxALL, 5);
    sizer->Add(prev_button, 0, wxALL, 5);

    SetSizer(sizer);
};

void Panel2::OnButton(wxCommandEvent &e) {
    wxNotebook *notebook = (wxNotebook *)FindWindowById(Enum::NOTEBOOK_ID);
    int current_page = notebook->GetSelection();
    if (e.GetId() == Enum::NEXT_PANEL_ID) {
        if (current_page < notebook->GetPageCount() - 1) {
            notebook->SetSelection(current_page + 1);
        }
    } else if (e.GetId() == Enum::PREV_PANEL_ID) {
        if (current_page > 0) {
            notebook->SetSelection(current_page - 1);
        }
    }
}

// clang-format off
wxBEGIN_EVENT_TABLE(Panel2, wxPanel) 
EVT_BUTTON(wxID_ANY, Panel2::OnButton)
wxEND_EVENT_TABLE()
