#include <UI/MainFrame.hpp>

MainFrame::MainFrame(const wxString &title, wxSize size, AppConfig *config)
    : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, size) {

    wxIcon icon("Speed.ico", wxBITMAP_TYPE_ICO);
    SetIcon(icon);

    model = new Model(this, 0);

    capture_panel = new CapturePanel(this, Enum::CP_Panel_ID, model);

    roi_panel = new RoiPanel(this, Enum::CP_Panel_ID, model);
    roi_panel->Hide();

    sizer = new wxBoxSizer(wxVERTICAL);
    sizer->Add(capture_panel, 1, wxEXPAND);
    sizer->Add(roi_panel, 1, wxEXPAND);
    SetSizer(sizer);
}

MainFrame::~MainFrame() {}

void MainFrame::OnButton(wxCommandEvent &e) {
    if (e.GetId() == Enum::CP_SWITCH_Button_ID) {
        if (capture_panel->IsShown()) {
            capture_panel->Hide();
            roi_panel->Show();
        } else {
            capture_panel->Show();
            roi_panel->Hide();
        }
        GetSizer()->Layout();
    }
}

//clang-format off
BEGIN_EVENT_TABLE(MainFrame, wxFrame)
EVT_BUTTON(wxID_ANY, MainFrame::OnButton)
END_EVENT_TABLE()
