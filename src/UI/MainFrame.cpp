#include <UI/MainFrame.hpp>

MainFrame::MainFrame(const wxString &title, wxString filename,
                     wxString dirLocation, wxSize size)
    : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, size) {
    std::string filePath2 =
        "C:/Users/kakik/Desktop/P1/data/bin/29012023093818.bin";
    // FILEWR::ReadFile(filePath2, imgData);
    wxString filePath = dirLocation + filename;
    // std::string filePath = "C:/Users/kakik/Desktop/P1/data/avi/output2.avi";
    FILEH264::ReadFile(filePath, imgData);

    int rotationAngle = 0;
    if (rotationAngle != 0) {
        ImageUtils::RotateImage(imgData, rotationAngle);
    }

    notebook = new wxNotebook(this, Enum::NOTEBOOK_ID, wxDefaultPosition,
                              wxSize(800, 600));

    select_line_panel = new SelectLinePanel(notebook, wxID_ANY, imgData);
    // object_detection_panel =
    // new ObjectDetectionPanel(notebook, wxID_ANY, imgData);

    p3 = new Panel2(notebook, wxID_ANY);

    notebook->AddPage(select_line_panel, "Select ROI", true);
    // notebook->AddPage(object_detection_panel, "Object Detection", false);
    notebook->AddPage(p3, "Panel3", false);

    notebook->Bind(wxEVT_NOTEBOOK_PAGE_CHANGED, &MainFrame::OnPageChange, this);
}

MainFrame::~MainFrame() {}

void MainFrame::OnPageChange(wxNotebookEvent &event) {
    int page = event.GetSelection();
    if (page == 0) {
        wxLogMessage("Changing To Page: Line Selection");
        // optical_flow_panel->OnPageChange();
    }

    if (page == 1) {
        wxLogMessage("Changing To Page: Object Detection");
        object_detection_panel->OnPageChange();
    }
}
