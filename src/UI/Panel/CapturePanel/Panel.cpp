#include "Controller/CaptureController.hpp"
#include "Event/Event_Capture.hpp"
#include "Event/Event_ChangePanel.hpp"
#include "Event/Event_Error.hpp"
#include "Event/Event_LoadImage.hpp"
#include "Event/Event_UpdateState.hpp"
#include "Event/Event_UpdateStatus.hpp"
#include "Model/AppState.hpp"

#include "UI/Button/BitmapButton/BitmapButton.hpp"
#include "UI/StaticText/Statustext.hpp"
#include "UI/StaticText/Titletext.hpp"
#include "Utils/Enum.hpp"
#include <UI/Panel/CapturePanel/Panel.hpp>
#include <iostream>
#include <stdexcept>
#include <wx/event.h>
#include <wx/gdicmn.h>

CapturePanel::CapturePanel(wxWindow *parent, wxWindowID id, CPCPtr &controller)
    : wxPanel(parent, id), controller(std::move(controller)) {
    button_panel = new CaptureButtonPanel(this, Enum::CP_BUTTON_PANEL_ID);

    img_bitmap = new BaseImagePanel(this);

    title_panel = new TitlePanel(this, panel_id);

    status_panel = new StatusPanel(this, wxT("Status"));

    main_sizer = new wxBoxSizer(wxVERTICAL);
    main_sizer->Add(title_panel, 0, wxEXPAND | wxTOP | wxLEFT | wxRIGHT, 10);
    main_sizer->Add(img_bitmap, 0, wxEXPAND | wxTOP | wxLEFT | wxRIGHT, 10);
    main_sizer->Add(status_panel, 0, wxEXPAND | wxTOP | wxLEFT | wxRIGHT, 10);
    main_sizer->Add(button_panel, 1, wxEXPAND | wxALL, 10);

    SetSizer(main_sizer);
    Fit();

    Hide();
}

CapturePanel::~CapturePanel() {}

void CapturePanel::OnButton(wxCommandEvent &e) {
    try {
        if (e.GetId() == Enum::CP_ToggleCamera_Button_ID) {
            auto button = button_panel->cPanel->camera_Button;
            ToggleCameraButtonHandler(button);
        }

        if (e.GetId() == Enum::CP_Capture_Button_ID) {
            auto button = button_panel->cPanel->Capture_Button->button;
            CaptureButtonHandler(button);
        }

        if (e.GetId() == Enum::CP_Load_Button_ID) {
            auto button = button_panel->cPanel->Load_Button->button;
            LoadButtonHandler(button);
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
            controller->e_SaveSessionData(this);
        }

        if (e.GetId() == Enum::CP_Reset_Button_ID) {
            controller->e_ResetSessionData(this);
        }

        controller->e_UpdateState(this);

        e.Skip();

    } catch (std::exception &e) {
        ErrorEvent::Submit(this, e.what());
    }
}

void CapturePanel::LoadButtonHandler(wxButton *button) {
#if DEBUG
    std::string path = "./2023823_15547.scpdata";

    controller->e_LoadFileStart(this, path);
#else
    wxFileDialog openFileDialog(this, _("Open .bin file"), "", "",
                                "XYZ files (*.bin)|*.bin",
                                wxFD_OPEN | wxFD_FILE_MUST_EXIST);

    if (openFileDialog.ShowModal() == wxID_CANCEL) {
        return;
    }

    std::string path = Utils::wxStringToString(openFileDialog.GetPath());
    controller->e_LoadFileStart(this, path);
#endif
}

void CapturePanel::CaptureButtonHandler(wxButton *button) {
    controller->e_LoadCaptureStart(this);
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

void CapturePanel::OnUpdatePreview(UpdatePreviewEvent &e) {
    if (e.GetId() == UPDATE_PREVIEW) {
        wxBitmap image = e.GetImage();
        img_bitmap->setImage(image);
    }

    if (e.GetId() == CLEAR_PREVIEW) {
        img_bitmap->setNoImage();
    }
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

void CapturePanel::OnUpdateState(UpdateStateEvent &e) {
    auto state = e.GetState();
    button_panel->cPanel->update(state);
    button_panel->csPanel->update(state);
    button_panel->rPanel->update(state);
    button_panel->tPanel->update(state);

    auto ms = state.cameraPanel.measureButtonState;
    button_panel->switch_Button->update(ms);

    Refresh();
}

void CapturePanel::OnUpdateStatus(UpdateStatusEvent &e) {
    auto status = e.GetStatus();
    status_panel->SetText(status);
    Refresh();
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

void CapturePanel::OnShow(wxShowEvent &e) {
    if (e.IsShown()) {
        controller->e_UpdateState(this);
    }
}

// clang-format off
wxBEGIN_EVENT_TABLE(CapturePanel, wxPanel)
    EVT_UPDATE_PREVIEW(wxID_ANY, CapturePanel::OnUpdatePreview)
    EVT_BUTTON(wxID_ANY,CapturePanel::OnButton) 
    EVT_COMMAND(wxID_ANY, c_LOAD_IMAGE_EVENT, CapturePanel::OnLoadImage)
    EVT_UPDATE_STATE(wxID_ANY, CapturePanel::OnUpdateState)
    EVT_UPDATE_STATUS(wxID_ANY, CapturePanel::OnUpdateStatus)
    EVT_COMMAND(wxID_ANY, c_REPLAY_EVENT, CapturePanel::OnReplay)
    EVT_SHOW(CapturePanel::OnShow)
wxEND_EVENT_TABLE()
