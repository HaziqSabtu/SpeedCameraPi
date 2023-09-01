#include "Controller/ControllerFactory.hpp"
#include "Controller/ManualCalibrationController.hpp"
#include "Controller/TrimDataController.hpp"
#include "Event/Event_ChangePanel.hpp"
#include "Model/SessionData.hpp"
#include "Model/SharedModel.hpp"
#include "UI/Dialog/ConfirmationDialog.hpp"
#include "UI/Frame/InfoFrame.hpp"
#include "UI/Frame/SettingsFrame.hpp"
#include "UI/Panel/ManualCalibrationPanel/Panel.hpp"
#include "UI/Theme/Data.hpp"
#include "UI/Theme/Theme.hpp"
#include "Utils/Enum.hpp"
#include <UI/Frame/MainFrame.hpp>
#include <cstddef>
#include <iostream>
#include <memory>
#include <wx/display.h>
#include <wx/event.h>
#include <wx/generic/panelg.h>
#include <wx/utils.h>

MainFrame::MainFrame() : wxFrame(NULL, wxID_ANY, Data::AppName) {

    wxIcon icon(Data::AppIcon, wxBITMAP_TYPE_ICO);
    SetIcon(icon);

    SetBackgroundColour(Theme::Background);

    wxDisplay display;
    wxRect screenRect = display.GetClientArea();

    SetSize(screenRect.GetSize());
    SetPosition(screenRect.GetPosition());

    ShowFullScreen(true);

    ControllerFactory factory(this);
    sharedModel = factory.getSharedModel();

    // * IDEA : Is there a better way to do this?
    auto cpc = factory.createCaptureController();
    cpp = new CapturePanel(this, Enum::CP_Panel_ID, cpc);
    panels[PANEL_CAPTURE] = cpp;

    auto roc = factory.createRoiController();
    rop = new RoiPanel(this, Enum::RO_Panel_ID, roc);
    panels[PANEL_ROI] = rop;

    auto clc = factory.createCalibrationController();
    clp = new CalibrationPanel(this, Enum::CL_Panel_ID, clc);
    panels[PANEL_CALIBRATION] = clp;

    auto mcc = factory.createManualCalibrationController();
    mcp = new ManualCalibrationPanel(this, Enum::MC_Panel_ID, mcc);
    panels[PANEL_MANUAL_CALIBRATION] = mcp;

    auto ccc = factory.createColorCalibrationController();
    ccp = new ColorCalibrationPanel(this, Enum::CC_Panel_ID, ccc);
    panels[PANEL_COLOR_CALIBRATION] = ccp;

    auto tdc = factory.createTrimDataController();
    tdp = new TrimDataPanel(this, Enum::TR_Panel_ID, tdc);
    panels[PANEL_TRIM_DATA] = tdp;

    auto rsc = factory.createResultController();
    rsp = new ResultPanel(this, Enum::RE_Panel_ID, rsc);
    panels[PANEL_RESULT] = rsp;

    sizer = new wxBoxSizer(wxVERTICAL);
    sizer->Add(cpp, 1, wxEXPAND);
    sizer->Add(rop, 1, wxEXPAND);
    sizer->Add(clp, 1, wxEXPAND);
    sizer->Add(mcp, 1, wxEXPAND);
    sizer->Add(ccp, 1, wxEXPAND);
    sizer->Add(tdp, 1, wxEXPAND);
    sizer->Add(rsp, 1, wxEXPAND);
    SetSizer(sizer);

    cpp->Show();
    sharedModel->sessionData.setPanelID(PANEL_CAPTURE);
}

MainFrame::~MainFrame() { wxWakeUpIdle(); }

void MainFrame::OnError(ErrorEvent &e) {
    wxString msg = e.GetErrorData();
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

        sharedModel->sessionData.setPanelID(data.nextPanelID);

        currentPanel->Hide();
        nextPanel->Show();

        GetSizer()->Layout();

    } catch (std::exception &e) {
        ErrorEvent::Submit(this, e.what());
    }
}

void MainFrame::OnButton(wxCommandEvent &e) {
    if (e.GetId() == Enum::G_Exit_Button_ID) {
        ExitButtonHandler(e);
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

#ifdef DEBUG
void MainFrame::ExitButtonHandler(wxCommandEvent &e) {
    sharedModel->killAllThreads();
    Close();
}

#else
void MainFrame::ExitButtonHandler(wxCommandEvent &e) {
    ConfirmationDialog dialog(this,
                              "Are you sure you want to exit the application?");
    if (dialog.ShowModal() == wxID_YES) {
        sharedModel->killAllThreads();
        Close();
    }
}
#endif

//clang-format off
BEGIN_EVENT_TABLE(MainFrame, wxFrame)
EVT_ERROR(wxID_ANY, MainFrame::OnError)
EVT_CHANGEPANEL(wxID_ANY, MainFrame::OnChangePanel)
EVT_BUTTON(wxID_ANY, MainFrame::OnButton)
END_EVENT_TABLE()
