#include <UI/MainFrame.hpp>

MainFrame::MainFrame(const wxString &title) : wxFrame(NULL, wxID_ANY, title) {

    notebook = new wxNotebook(this, Enum::NOTEBOOK_ID);

    select_roi_panel = new SelectRoiPanel(notebook, wxID_ANY);
    p2 = new Panel2(notebook, wxID_ANY);
    p3 = new Panel2(notebook, wxID_ANY);
    p4 = new Panel2(notebook, wxID_ANY);
    p5 = new Panel2(notebook, wxID_ANY);

    notebook->AddPage(select_roi_panel, "Select ROI", true);
    notebook->AddPage(p2, "Panel2", false);
    notebook->AddPage(p3, "Panel3", false);
    notebook->AddPage(p4, "Panel4", false);
    notebook->AddPage(p5, "Panel5", false);

    // select_roi_panel->Show(true);
    SetSize(800, 600);
    Center();
}
