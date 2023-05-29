#include "Model/ModelFactory.hpp"
#include "Model/SharedModel.hpp"
#include <UI/MainFrame.hpp>
#include <memory>

MainFrame::MainFrame(const wxString &title, wxSize size, AppConfig *config)
    : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, size) {

    wxIcon icon("Speed.ico", wxBITMAP_TYPE_ICO);
    SetIcon(icon);

    ModelFactory modelFactory(this);

    auto captureModel = modelFactory.createCaptureModel();
    capture_panel = new CapturePanel(this, Enum::CP_Panel_ID, captureModel);

    // roi_panel = new RoiPanel(this, Enum::CP_Panel_ID, model);
    // roi_panel->Hide();
    // capture_panel->setNextPanel(roi_panel);

    sizer = new wxBoxSizer(wxVERTICAL);
    sizer->Add(capture_panel, 1, wxEXPAND);
    // sizer->Add(roi_panel, 1, wxEXPAND);
    SetSizer(sizer);
}

MainFrame::~MainFrame() {}

void MainFrame::OnPageChange(wxCommandEvent &e) { GetSizer()->Layout(); }

void MainFrame::OnError(ErrorEvent &e) {
    std::string msg = e.GetErrorData();
    wxMessageBox(msg, "Error", wxOK | wxICON_ERROR);
}

//clang-format off
BEGIN_EVENT_TABLE(MainFrame, wxFrame)
// EVT_BUTTON(wxID_ANY, MainFrame::OnButton)
EVT_COMMAND(wxID_ANY, c_CHANGE_PANEL_EVENT, MainFrame::OnPageChange)
EVT_ERROR(wxID_ANY, MainFrame::OnError)

END_EVENT_TABLE()
