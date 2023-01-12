#include <UI/MainFrame.hpp>

MainFrame::MainFrame(const wxString &title) : wxFrame(NULL, wxID_ANY, title) {
    select_roi_panel = new SelectRoiPanel(this, wxID_ANY);
    select_roi_panel->Show(true);
}
