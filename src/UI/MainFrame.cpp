#include <UI/MainFrame.hpp>

MainFrame::MainFrame(const wxString &title) : wxFrame(NULL, wxID_ANY, title) {
    std::string filePath =
        "C:/Users/kakik/Desktop/P1/data/bin/29012023093818.bin";
    FILEWR::ReadFile(filePath, imgData);

    notebook = new wxNotebook(this, Enum::NOTEBOOK_ID);

    select_line_panel = new SelectLinePanel(notebook, wxID_ANY, imgData);

    p3 = new Panel2(notebook, wxID_ANY);
    p4 = new Panel2(notebook, wxID_ANY);

    notebook->AddPage(select_line_panel, "Select ROI", true);
    notebook->AddPage(p3, "Panel3", false);
    notebook->AddPage(p4, "Panel4", false);

    notebook->Bind(wxEVT_NOTEBOOK_PAGE_CHANGED, &MainFrame::OnPageChange, this);

    // select_roi_panel->Show(true);
    SetSize(800, 600);
    Center();
}

void MainFrame::OnPageChange(wxNotebookEvent &event) {
    int page = event.GetSelection();
    // if (page == 1) {
    //     optical_flow_panel->OnPageChange();
    // }

    // if (page == 2) {
    //     lane_detection_panel->OnPageChange();
    // }
}
