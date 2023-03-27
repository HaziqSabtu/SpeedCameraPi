#include <UI/MainFrame.hpp>

MainFrame::MainFrame(const wxString &title, wxSize size, AppConfig *config)
    : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, size), config(config) {
    wxString filePath = "dirLocation + filename";

    wxIcon icon("Speed.ico", wxBITMAP_TYPE_ICO);
    SetIcon(icon);

    notebook = new wxNotebook(this, Enum::NOTEBOOK_ID, wxDefaultPosition,
                              wxSize(800, 600));

    camera_panel =
        new CameraPanel(notebook, Enum::CP_Panel_ID, new AppConfig());

    notebook->AddPage(camera_panel, "Camera", true);

    notebook->Bind(wxEVT_NOTEBOOK_PAGE_CHANGED, &MainFrame::OnPageChange, this);
}

MainFrame::~MainFrame() {}

void MainFrame::OnPageChange(wxNotebookEvent &event) {
    int page = event.GetSelection();
    if (page == 1) {
        wxLogMessage("Changing To Page: Line Selection");
        // select_line_panel->OnPageChange();
    }

    // if (page == 2) {
    //     wxLogMessage("Changing To Page: Object Detection");
    //     object_detection_panel->OnPageChange();
    // }
}
