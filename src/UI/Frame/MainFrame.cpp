#include "Controller/ControllerFactory.hpp"
#include "Controller/ManualCalibrationController.hpp"
#include "Controller/TrimDataController.hpp"
#include "Event/Event_ChangePanel.hpp"
#include "Model/SessionData.hpp"
#include "Model/SharedModel.hpp"
#include "UI/Data/Data.hpp"
#include "UI/Data/Theme.hpp"
#include "UI/Dialog/ConfirmationDialog.hpp"
#include "UI/Dialog/ExitAppDialog.hpp"
#include "UI/Frame/InfoFrame.hpp"
#include "UI/Frame/SettingsFrame.hpp"
#include "UI/Panel/ManualCalibrationPanel/Panel.hpp"
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

    CtrlFactoryPtr ctrlFactory = std::make_shared<ControllerFactory>(this);
    sharedModel = ctrlFactory->getSharedModel();

    panelFactory = std::make_shared<PanelFactory>(ctrlFactory);

    registerPanel(PANEL_CAPTURE);
    registerPanel(PANEL_ROI);
    registerPanel(PANEL_CALIBRATION);
    registerPanel(PANEL_MANUAL_CALIBRATION);
    registerPanel(PANEL_HORIZONTAL_CALIBRATION);
    registerPanel(PANEL_COLOR_CALIBRATION);
    registerPanel(PANEL_TRIM_DATA);
    registerPanel(PANEL_RESULT);

    showFirstPanel();
}

MainFrame::~MainFrame() { wxWakeUpIdle(); }

void MainFrame::registerPanel(PanelID panelID) {

    if (panelFactory == nullptr) {
        throw std::runtime_error("panelFactory is null");
    }

    auto panel = panelFactory->createPanel(this, panelID);

    if (panel == nullptr) {
        throw std::runtime_error("MainFrame::registerPanel: panel is null");
    }

    panels[panelID] = panel;

    if (sizer == nullptr) {
        sizer = new wxBoxSizer(wxVERTICAL);
    }

    sizer->Add(panel, 1, wxEXPAND);
    SetSizer(sizer);
}

void MainFrame::showFirstPanel() {
    if (panels[FIRST_PANEL_ID] == nullptr) {
        throw std::runtime_error("MainFrame::showFirstPanel: panel is null");
    }

    panels[FIRST_PANEL_ID]->Show();
    sharedModel->sessionData.setPanelID(FIRST_PANEL_ID);
}

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
    auto dialog = new ExitAppDialog(this);
    int result = dialog->ShowModal();
    if (result == wxID_YES) {
        sharedModel->killAllThreads();
        Close();
    }

    if (result == dialog->getShutdownButtonID()) {
        sharedModel->killAllThreads();
        wxShutdown();
    }
}
#endif

//clang-format off
BEGIN_EVENT_TABLE(MainFrame, wxFrame)
EVT_ERROR(wxID_ANY, MainFrame::OnError)
EVT_CHANGEPANEL(wxID_ANY, MainFrame::OnChangePanel)
EVT_BUTTON(wxID_ANY, MainFrame::OnButton)
END_EVENT_TABLE()
