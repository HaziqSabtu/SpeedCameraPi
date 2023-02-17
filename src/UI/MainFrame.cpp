#include <UI/MainFrame.hpp>

MainFrame::MainFrame(const wxString &title, wxString filename,
                     wxString dirLocation, wxSize size)
    : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, size) {
    wxString filePath = dirLocation + filename;

    wxIcon icon("Speed.ico", wxBITMAP_TYPE_ICO);
    SetIcon(icon);

    notebook = new wxNotebook(this, Enum::NOTEBOOK_ID, wxDefaultPosition,
                              wxSize(800, 600));

    camera_panel = new CameraPanel(notebook, Enum::CP_Panel_ID, filePath);

    select_line_panel = new SelectLinePanel(notebook, Enum::SL_Panel_ID);

    object_detection_panel =
        new ObjectDetectionPanel(notebook, Enum::OD_Panel_ID);

    notebook->AddPage(camera_panel, "Camera", true);
    notebook->AddPage(select_line_panel, "Select Line", false);
    notebook->AddPage(object_detection_panel, "Result", false);

    notebook->Bind(wxEVT_NOTEBOOK_PAGE_CHANGED, &MainFrame::OnPageChange, this);
}

MainFrame::~MainFrame() {}

void MainFrame::OnPageChange(wxNotebookEvent &event) {
    int page = event.GetSelection();
    if (page == 1) {
        wxLogMessage("Changing To Page: Line Selection");
        select_line_panel->OnPageChange();
    }

    if (page == 2) {
        wxLogMessage("Changing To Page: Object Detection");
        object_detection_panel->OnPageChange();
    }
}
