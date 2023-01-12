#include <UI/MainFrame.hpp>

MainFrame::MainFrame(const wxString &title) : wxFrame(NULL, wxID_ANY, title) {

    notebook = new wxNotebook(this, Enum::NOTEBOOK_ID);

    select_roi_panel = new SelectRoiPanel(notebook, wxID_ANY);
    p2 = new Panel2(notebook, wxID_ANY);

    notebook->AddPage(select_roi_panel, "Select ROI", true);
    notebook->AddPage(p2, "Panel2", false);

    // select_roi_panel->Show(true);
    SetSize(800, 600);
    Center();
}
