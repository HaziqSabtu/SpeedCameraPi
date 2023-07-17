#include "Event/Event_ChangePanel.hpp"
#include "Model/ModelFactory.hpp"
#include "Model/SharedModel.hpp"
#include "UI/Dialog/ConfirmationDialog.hpp"
#include "Utils/Enum.hpp"
#include <UI/MainFrame.hpp>
#include <memory>
#include <wx/display.h>
#include <wx/event.h>
#include <wx/generic/panelg.h>

MainFrame::MainFrame(const wxString &title) : wxFrame(NULL, wxID_ANY, title) {

    wxIcon icon("Speed.ico", wxBITMAP_TYPE_ICO);
    SetIcon(icon);

    wxDisplay display;
    wxRect screenRect = display.GetClientArea();

    // Set the frame size and position
    SetSize(screenRect.GetSize());
    SetPosition(screenRect.GetPosition());

    // Show the frame
    ShowFullScreen(true);

    ModelFactory modelFactory(this);
    sharedModel = modelFactory.getSharedModel();

    auto captureModel = modelFactory.createCaptureModel();
    capture_panel = new CapturePanel(this, Enum::CP_Panel_ID, captureModel);
    panels[PANEL_CAPTURE] = capture_panel;

    auto roiModel = modelFactory.createRoiModel();
    roi_panel = new RoiPanel(this, Enum::CP_Panel_ID, roiModel);
    panels[PANEL_ROI] = roi_panel;

    auto calibrationModel = modelFactory.createCalibrationModel();
    calibration_panel =
        new CalibrationPanel(this, Enum::CP_Panel_ID, calibrationModel);
    panels[PANEL_CALIBRATION] = calibration_panel;

    sizer = new wxBoxSizer(wxVERTICAL);
    sizer->Add(capture_panel, 1, wxEXPAND);
    sizer->Add(roi_panel, 1, wxEXPAND);
    sizer->Add(calibration_panel, 1, wxEXPAND);
    SetSizer(sizer);
}

MainFrame::~MainFrame() {}

void MainFrame::OnError(ErrorEvent &e) {
    std::string msg = e.GetErrorData();
    wxMessageBox(msg, "Error", wxOK | wxICON_ERROR);
}

void MainFrame::OnChangePanel(ChangePanelEvent &e) {
    try {

        ChangePanelData data = e.GetPanelData();
        wxPanel *nextPanel = panels[data.nextPanelID];
        wxPanel *currentPanel = panels[data.currentPanelID];

        if (currentPanel == nullptr) {
            throw std::runtime_error("Error fetching current panel");
        }

        if (nextPanel == nullptr) {
            throw std::runtime_error("Error fetching next panel");
        }

        sharedModel->sessionData.currentPanelID = data.nextPanelID;

        currentPanel->Hide();
        nextPanel->Show();

        GetSizer()->Layout();

    } catch (std::exception &e) {
        ErrorEvent errorEvent(c_ERROR_EVENT, wxID_ANY);
        errorEvent.SetErrorData(e.what());
        wxPostEvent(this, errorEvent);
    }
}

void MainFrame::OnButton(wxCommandEvent &e) {
    if (e.GetId() == Enum::G_Exit_Button_ID) {
        ConfirmationDialog dialog(
            this, "Are you sure you want to exit the application?");
        if (dialog.ShowModal() == wxID_YES) {
            Close();
        }
    }
}

//clang-format off
BEGIN_EVENT_TABLE(MainFrame, wxFrame)
EVT_ERROR(wxID_ANY, MainFrame::OnError)
EVT_CHANGEPANEL(wxID_ANY, MainFrame::OnChangePanel)
EVT_BUTTON(wxID_ANY, MainFrame::OnButton)
END_EVENT_TABLE()
