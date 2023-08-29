#include "Controller/CaptureController.hpp"
#include "Event/Event_Capture.hpp"
#include "Event/Event_ChangePanel.hpp"
#include "Event/Event_Error.hpp"
#include "Event/Event_LoadImage.hpp"
#include "Event/Event_SaveData.hpp"
#include "Event/Event_UpdateState.hpp"
#include "Event/Event_UpdateStatus.hpp"
#include "Model/AppState.hpp"

#include "UI/Button/BitmapButton/BitmapButton.hpp"
#include "UI/Panel/Common/BasePanel.hpp"
#include "UI/StaticText/Statustext.hpp"
#include "UI/StaticText/Titletext.hpp"
#include "Utils/Enum.hpp"
#include <UI/Panel/CapturePanel/Panel.hpp>
#include <iostream>
#include <stdexcept>
#include <wx/event.h>
#include <wx/gdicmn.h>

CapturePanel::CapturePanel(wxWindow *parent, wxWindowID id, CPCPtr controller)
    : BasePanel(parent, id, controller), controller(controller) {

    button_panel = new CaptureButtonPanel(this, Enum::CP_BUTTON_PANEL_ID);
    title_panel = new TitlePanel(this, panel_id);

    size();
}

CapturePanel::~CapturePanel() {}

void CapturePanel::OnButton(wxCommandEvent &e) {

    CaptureButtonPanel *button_panel =
        dynamic_cast<CaptureButtonPanel *>(this->button_panel);

    if (e.GetId() == Enum::CP_ToggleCamera_Button_ID) {
        auto button = button_panel->cPanel->camera_Button;
        ToggleCameraButtonHandler(button);
    }

    if (e.GetId() == Enum::CP_Capture_Button_ID) {
        controller->e_LoadCaptureStart(this);
    }

    if (e.GetId() == Enum::CP_Load_Button_ID) {
        LoadButtonHandler();
    }

    if (e.GetId() == Enum::CP_ClearCapture_Button_ID) {
        controller->e_ClearImageData(this);
    }

    if (e.GetId() == Enum::CP_Replay_Button_ID) {
        controller->e_ReplayStart(this);
    }

    if (e.GetId() == Enum::CP_SWITCH_Button_ID) {
        controller->e_ChangeToResultPanel(this);
    }

    if (e.GetId() == Enum::CP_Calibration_Button_ID) {
        controller->e_ChangeToCalibPanel(this);
    }

    if (e.GetId() == Enum::CP_RemoveCalibration_Button_ID) {
        controller->e_RemoveCalibration(this);
    }

    if (e.GetId() == Enum::CP_Roi_Button_ID) {
        controller->e_ChangeToRoiPanel(this);
    }

    if (e.GetId() == Enum::CP_RemoveRoi_Button_ID) {
        controller->e_RemoveRoi(this);
    }

    if (e.GetId() == Enum::CP_Save_Button_ID) {
        controller->e_SaveSessionDataStart(this);
    }

    if (e.GetId() == Enum::CP_Reset_Button_ID) {
        controller->e_ResetSessionData(this);
    }

    if (e.GetId() == Enum::CP_Trim_Button_ID) {
        controller->e_ChangeToTrimDataPanel(this);
    }

    e.Skip();
}

void CapturePanel::LoadButtonHandler() {
#if DEBUG
    std::string path = "./2023823_15547.scpdata";

    controller->e_LoadFileStart(this, path);
#else
    wxFileDialog openFileDialog(this, _("Open .scpdata file"), "", "",
                                "XYZ files (*.scpdata)|*.scpdata",
                                wxFD_OPEN | wxFD_FILE_MUST_EXIST);

    if (openFileDialog.ShowModal() == wxID_CANCEL) {
        return;
    }

    std::string path = Utils::wxStringToString(openFileDialog.GetPath());
    controller->e_LoadFileStart(this, path);
#endif
}

void CapturePanel::ToggleCameraButtonHandler(BitmapButtonT2 *button) {
    if (button->getState() == ButtonState::OFF) {
        controller->e_CameraStart(button);
        return;
    }

    if (button->getState() == ButtonState::ON) {
        controller->e_CameraEnd(button);
        return;
    }
    throw std::runtime_error("Invalid button state");
}

void CapturePanel::OnLoadImage(wxCommandEvent &e) {
    if (e.GetId() == LOAD_START_CAMERA) {
        UpdateStatusEvent::Submit(this, StatusCollection::STATUS_CAPTURE_START);
    }

    if (e.GetId() == LOAD_END_FILE) {
        controller->e_LoadFileEnd(this);
    }

    if (e.GetId() == LOAD_END_CAMERA) {
        controller->e_LoadCaptureEnd(this);
    }

    controller->e_UpdateState(this);

    e.Skip();
}

void CapturePanel::OnReplay(wxCommandEvent &e) {
    if (e.GetId() == REPLAY_START) {
        UpdateStatusEvent::Submit(this, StatusCollection::STATUS_REPLAY_START);
    }

    if (e.GetId() == REPLAY_END) {
        controller->e_ReplayEnd(this);
        UpdateStatusEvent::Submit(this, StatusCollection::STATUS_REPLAY_END);
    }

    controller->e_UpdateState(this);
    e.Skip();
}

void CapturePanel::OnSaveData(wxCommandEvent &e) {
    if (e.GetId() == SAVE_DATA_START) {
        wxString msg = "Saving";
        UpdateStatusEvent::Submit(this, msg);
    }

    if (e.GetId() == SAVE_DATA_END) {
        controller->e_SaveSessionDataEnd(this);

        wxString msg = "Save complete";
        UpdateStatusEvent::Submit(this, msg);
    }

    if (e.GetId() == SAVE_DATA_ERROR) {
        controller->e_SaveSessionDataEnd(this);

        wxString msg = "Error saving data";
        UpdateStatusEvent::Submit(this, msg);
    }

    controller->e_UpdateState(this);
    e.Skip();
}

// clang-format off
wxBEGIN_EVENT_TABLE(CapturePanel, BasePanel)
    EVT_BUTTON(wxID_ANY,CapturePanel::OnButton) 
    EVT_COMMAND(wxID_ANY, c_LOAD_IMAGE_EVENT, CapturePanel::OnLoadImage)
    EVT_COMMAND(wxID_ANY, c_REPLAY_EVENT, CapturePanel::OnReplay)
    EVT_COMMAND(wxID_ANY, c_SAVE_DATA_EVENT, CapturePanel::OnSaveData)
wxEND_EVENT_TABLE()
