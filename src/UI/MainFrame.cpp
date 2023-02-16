#include <UI/MainFrame.hpp>

MainFrame::MainFrame(const wxString &title, wxString filename,
                     wxString dirLocation, wxSize size)
    : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, size) {
    wxString filePath = dirLocation + filename;
    FILEH264::ReadFile(filePath, imgData);

    notebook = new wxNotebook(this, Enum::NOTEBOOK_ID, wxDefaultPosition,
                              wxSize(800, 600));

    select_line_panel =
        new SelectLinePanel(notebook, Enum::SL_Panel_ID, imgData);
    object_detection_panel =
        new ObjectDetectionPanel(notebook, Enum::OD_Panel_ID, imgData);

    camera_panel = new CameraPanel(notebook, Enum::CP_Panel_ID, filePath);

    capture_view_panel = new CaptureViewPanel(notebook, Enum::CV_Panel_ID);

    notebook->AddPage(camera_panel, "Camera", true);
    notebook->AddPage(capture_view_panel, "Capture View", false);
    notebook->AddPage(select_line_panel, "Select ROI", false);
    notebook->AddPage(object_detection_panel, "Object Detection", false);

    notebook->Bind(wxEVT_NOTEBOOK_PAGE_CHANGED, &MainFrame::OnPageChange, this);
}

MainFrame::~MainFrame() {}

void MainFrame::OnPageChange(wxNotebookEvent &event) {
    int page = event.GetSelection();
    if (page == 1) {
        wxLogMessage("Changing To Page: Capture View");
        capture_view_panel->OnPageChange();
    }
    if (page == 2) {
        wxLogMessage("Changing To Page: Line Selection");
        select_line_panel->OnPageChange();
    }

    if (page == 3) {
        wxLogMessage("Changing To Page: Object Detection");
        object_detection_panel->OnPageChange();
    }
}
