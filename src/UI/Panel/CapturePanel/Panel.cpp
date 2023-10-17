#include "Controller/CaptureController.hpp"
#include "Event/Event_ChangePanel.hpp"
#include "Event/Event_Error.hpp"
#include "Event/Event_LoadImage.hpp"
#include "Event/Event_Preview.hpp"
#include "Event/Event_SaveData.hpp"
#include "Event/Event_UpdateState.hpp"
#include "Event/Event_UpdateStatus.hpp"
#include "Model/AppState.hpp"

#include "UI/Button/BitmapButton/BitmapButton.hpp"
#include "UI/Dialog/DataSavedDialog.hpp"
#include "UI/Panel/Common/BasePanel.hpp"
#include "UI/StaticText/Statustext.hpp"
#include "UI/StaticText/Titletext.hpp"
#include "Utils/Enum.hpp"
#include <UI/Panel/CapturePanel/Panel.hpp>
#include <iostream>
#include <stdexcept>
#include <wx/app.h>
#include <wx/event.h>
#include <wx/gdicmn.h>

CapturePanel::CapturePanel(wxWindow *parent, wxWindowID id, CPCPtr controller)
    : BasePanel(parent, id, controller), controller(controller) {

    button_panel = new CaptureButtonPanel(this, Enum::CP_Button_Panel_ID);
    title_panel = new TitlePanel(this, panel_id);

    size();
}

CapturePanel::~CapturePanel() {}

void CapturePanel::OnButton(wxCommandEvent &e) {

    CaptureButtonPanel *button_panel =
        dynamic_cast<CaptureButtonPanel *>(this->button_panel);

    if (e.GetId() == Enum::CP_ToggleCamera_Button_ID) {
        auto button = button_panel->MainPanel->Camera_Button;
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
        controller->e_CapturePreviewStart(this);
    }

    if (e.GetId() == Enum::CP_Measure_Button_ID) {
        controller->e_ChangeToResultPanel(this);
    }

    if (e.GetId() == Enum::CP_LaneCalibration_Button_ID) {
        controller->e_ChangeToLaneCalibrationPanel(this);
    }

    if (e.GetId() == Enum::CP_DistCalibration_Button_ID) {
        controller->e_ChangeToDistanceCalibrationPanel(this);
    }

    if (e.GetId() == Enum::CP_RemoveLaneCalibration_Button_ID ||
        e.GetId() == Enum::CP_RemoveDistCalibration_Button_ID) {
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

    if (e.GetId() == Enum::G_SwitchMode_Button_ID) {
        controller->e_ToggleMode(this);
    }

    e.Skip();
}

void CapturePanel::LoadButtonHandler() {
    wxFileDialog openFileDialog(this, _("Open .scpdata file"), "", "",
                                "XYZ files (*.scpdata)|*.scpdata",
                                wxFD_OPEN | wxFD_FILE_MUST_EXIST);

    if (openFileDialog.ShowModal() == wxID_CANCEL) {
        status_panel->SetText(SC::STATUS_IDLE);
        return;
    }

    std::string path = Utils::wxStringToString(openFileDialog.GetPath());
    controller->e_LoadFileStart(this, path);
}

void CapturePanel::ToggleCameraButtonHandler(BitmapButtonT2 *button) {
    if (button->getState() == ButtonState::OFF) {
        controller->e_CameraPreviewStart(button);
        return;
    }

    if (button->getState() == ButtonState::ON) {
        controller->e_CameraPreviewEnd(button);
        return;
    }
    throw std::runtime_error("Invalid button state");
}

void CapturePanel::OnLoadImage(wxCommandEvent &e) {
    if (e.GetId() == LOAD_START_CAMERA) {
        UpdateStatusEvent::Submit(this, SC::STATUS_CAPTURE_START);
    }

    if (e.GetId() == LOAD_END_CAMERA) {
        controller->e_LoadCaptureEnd(this);
        UpdateStatusEvent::Submit(this, SC::STATUS_CAPTURE_END);
    }

    if (e.GetId() == LOAD_ERROR_CAMERA) {
        controller->e_LoadCaptureEnd(this);
        UpdateStatusEvent::Submit(this, SC::STATUS_CAPTURE_ERROR);
    }

    if (e.GetId() == LOAD_START_FILE) {
        UpdateStatusEvent::Submit(this, SC::STATUS_LOAD_DATA_START);
    }

    if (e.GetId() == LOAD_END_FILE) {
        controller->e_LoadFileEnd(this);
        UpdateStatusEvent::Submit(this, SC::STATUS_LOAD_DATA_END);
    }

    if (e.GetId() == LOAD_ERROR_FILE) {
        controller->e_LoadFileEnd(this);
        UpdateStatusEvent::Submit(this, SC::STATUS_LOAD_DATA_ERROR);
    }

    controller->e_UpdateState(this);

    e.Skip();
}

void CapturePanel::OnPreviewCapture(wxCommandEvent &e) {
    if (e.GetId() == PREVIEW_START) {
        UpdateStatusEvent::Submit(this, SC::STATUS_PREVIEW_CAPTURE_START);
    }

    if (e.GetId() == PREVIEW_END) {
        controller->e_CapturePreviewEnd(this);
        UpdateStatusEvent::Submit(this, SC::STATUS_PREVIEW_CAPTURE_END);
    }

    if (e.GetId() == PREVIEW_ERROR) {
        controller->e_CapturePreviewEnd(this);
        UpdateStatusEvent::Submit(this, SC::STATUS_PREVIEW_CAPTURE_ERROR);
    }

    controller->e_UpdateState(this);
    e.Skip();
}

void CapturePanel::OnPreviewCamera(wxCommandEvent &e) {
    if (e.GetId() == PREVIEW_START) {
        UpdateStatusEvent::Submit(this, SC::STATUS_PREVIEW_CAMERA_START);
    }

    if (e.GetId() == PREVIEW_END) {
        UpdateStatusEvent::Submit(this, SC::STATUS_PREVIEW_CAMERA_END);
    }

    if (e.GetId() == PREVIEW_ERROR) {
        UpdateStatusEvent::Submit(this, SC::STATUS_PREVIEW_CAMERA_ERROR);
    }

    controller->e_UpdateState(this);
    e.Skip();
}

void CapturePanel::OnSaveData(wxCommandEvent &e) {
    if (e.GetId() == SAVE_DATA_START) {
        UpdateStatusEvent::Submit(this, SC::STATUS_SAVE_DATA_START);
    }

    if (e.GetId() == SAVE_DATA_END) {
        controller->e_SaveSessionDataEnd(this);
        UpdateStatusEvent::Submit(this, SC::STATUS_SAVE_DATA_END);

        auto dialog = new DataSavedDialog(this);
        auto result = dialog->ShowModal();

        if (result == wxID_YES) {
            controller->e_ClearImageData(this);
        }

        if (result == dialog->resetButtonID) {
            controller->e_ResetSessionData(this);
        }
    }

    if (e.GetId() == SAVE_DATA_ERROR) {
        controller->e_SaveSessionDataEnd(this);

        ErrorEvent::Submit(this, "Error saving data");
        UpdateStatusEvent::Submit(this, SC::STATUS_SAVE_DATA_ERROR);
    }

    controller->e_UpdateState(this);
    e.Skip();
}

void CapturePanel::OnSwitchMode(wxCommandEvent &e) {
    if (e.GetId() == SWITCH_MODE_OK) {
        UpdateStatusEvent::Submit(this, SC::STATUS_SWITCH_MODE_OK);
    }

    if (e.GetId() == SWITCH_MODE_CANCEL) {
        UpdateStatusEvent::Submit(this, SC::STATUS_SWITCH_MODE_CANCEL);
    }

    if (e.GetId() == SWITCH_MODE_ERROR) {
        UpdateStatusEvent::Submit(this, SC::STATUS_SWITCH_MODE_ERROR);
    }

    controller->e_UpdateState(this);
    e.Skip();
}

// clang-format off
wxBEGIN_EVENT_TABLE(CapturePanel, BasePanel)
    EVT_BUTTON(wxID_ANY,CapturePanel::OnButton) 
    EVT_COMMAND(wxID_ANY, c_LOAD_IMAGE_EVENT, CapturePanel::OnLoadImage)
    EVT_COMMAND(wxID_ANY, c_PREVIEW_CAPTURE_EVENT, CapturePanel::OnPreviewCapture)
    EVT_COMMAND(wxID_ANY, c_PREVIEW_CAMERA_EVENT, CapturePanel::OnPreviewCamera)
    EVT_COMMAND(wxID_ANY, c_SAVE_DATA_EVENT, CapturePanel::OnSaveData)
    EVT_COMMAND(wxID_ANY, c_SWITCH_MODE_EVENT, CapturePanel::OnSwitchMode)
wxEND_EVENT_TABLE()
