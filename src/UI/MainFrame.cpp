#include <UI/MainFrame.hpp>

MainFrame::MainFrame(const wxString &title, wxSize size, AppConfig *config)
    : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, size), config(config) {
    wxString filePath = "dirLocation + filename";

    wxIcon icon("Speed.ico", wxBITMAP_TYPE_ICO);
    SetIcon(icon);

    notebook = new wxNotebook(this, Enum::NOTEBOOK_ID, wxDefaultPosition,
                              wxSize(800, 600));

    camera_panel = new CameraPanel2(notebook, Enum::CP_Panel_ID,
                                    new AppConfig(), new Model(this, 0));

    notebook->AddPage(camera_panel, "Camera", true);
}

MainFrame::~MainFrame() {}
