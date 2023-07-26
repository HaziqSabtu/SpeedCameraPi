#include "Event/Event_ChangePanel.hpp"
#include "Model/CalibrationModel.hpp"
#include "Model/ModelFactory.hpp"
#include "Model/SessionData.hpp"
#include "Model/SharedModel.hpp"
#include "UI/Dialog/ConfirmationDialog.hpp"
#include "UI/Frame/InfoFrame.hpp"
#include "UI/Frame/SettingsFrame.hpp"
#include "UI/Panel/ManualCalibrationPanel/Panel.hpp"
#include "UI/Theme/Theme.hpp"
#include "Utils/Enum.hpp"
#include <UI/Frame/MainFrame.hpp>
#include <iostream>
#include <memory>
#include <wx/display.h>
#include <wx/event.h>
#include <wx/generic/panelg.h>
#include <wx/utils.h>

MainFrame::MainFrame(const wxString &title) : wxFrame(NULL, wxID_ANY, title) {

    wxIcon icon("Speed.ico", wxBITMAP_TYPE_ICO);
    SetIcon(icon);

    SetBackgroundColour(Theme::Background);

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

    std::unique_ptr<CalibrationModel> manualCalibrationModel = nullptr;
    manual_calibration_panel =
        new ManualCalibrationPanel(this, wxID_ANY, manualCalibrationModel);
    panels[PANEL_MANUAL_CALIBRATION] = manual_calibration_panel;

    color_calibration_panel =
        new ColorCalibrationPanel(this, wxID_ANY, manualCalibrationModel);
    panels[PANEL_COLOR_CALIBRATION] = color_calibration_panel;

    sizer = new wxBoxSizer(wxVERTICAL);
    sizer->Add(capture_panel, 1, wxEXPAND);
    sizer->Add(roi_panel, 1, wxEXPAND);
    sizer->Add(calibration_panel, 1, wxEXPAND);
    sizer->Add(manual_calibration_panel, 1, wxEXPAND);
    sizer->Add(color_calibration_panel, 1, wxEXPAND);
    SetSizer(sizer);

    capture_panel->Show();
    sharedModel->sessionData.currentPanelID = PANEL_CAPTURE;
    // calibration_panel->Show();
    // sharedModel->sessionData.currentPanelID = PANEL_CALIBRATION;
}

MainFrame::~MainFrame() { wxWakeUpIdle(); }

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
        // ConfirmationDialog dialog(
        //     this, "Are you sure you want to exit the application?");
        // if (dialog.ShowModal() == wxID_YES) {
        //     Close();
        // }
        sharedModel->killAllThreads();

        Close();
    }

    if (e.GetId() == Enum::G_Setting_Button_ID) {
        SettingsFrame *settingsFrame = new SettingsFrame();
        settingsFrame->Show();
    }

    if (e.GetId() == Enum::G_Info_Button_ID) {
        InfoFrame *infoFrame = new InfoFrame();
        infoFrame->Show();
    }
}

//clang-format off
BEGIN_EVENT_TABLE(MainFrame, wxFrame)
EVT_ERROR(wxID_ANY, MainFrame::OnError)
EVT_CHANGEPANEL(wxID_ANY, MainFrame::OnChangePanel)
EVT_BUTTON(wxID_ANY, MainFrame::OnButton)
END_EVENT_TABLE()
