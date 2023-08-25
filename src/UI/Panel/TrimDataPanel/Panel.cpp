#include "Controller/ManualCalibrationController.hpp"
#include "Controller/TrimDataController.hpp"
#include "Event/Event_Calibration.hpp"
#include "Event/Event_ChangePanel.hpp"
#include "Event/Event_Replay.hpp"
#include "Event/Event_RequestUpdateState.hpp"
#include "Event/Event_UpdateStatus.hpp"

#include "Model/AppState.hpp"
#include "UI/Layout/StatusPanel.hpp"
#include "Utils/Enum.hpp"
#include <UI/Panel/TrimDataPanel/Panel.hpp>
#include <stdexcept>
#include <wx/event.h>
#include <wx/gdicmn.h>
#include <wx/gtk/stattext.h>
#include <wx/sizer.h>

namespace SC = StatusCollection;

TrimDataPanel::TrimDataPanel(wxWindow *parent, wxWindowID id,
                             TDCPtr &controller)
    : wxPanel(parent, id), controller(std::move(controller)) {

    button_panel = new TrimDataPanelButton(this, Enum::CP_BUTTON_PANEL_ID);

    img_bitmap = new BaseImagePanel(this);

    title_panel = new TitlePanel(this, panel_id);

    status_panel = new StatusPanel(this, SC::STATUS_IDLE);

    main_sizer = new wxBoxSizer(wxVERTICAL);
    main_sizer->Add(title_panel, 0, wxEXPAND | wxTOP | wxLEFT | wxRIGHT, 10);
    main_sizer->Add(img_bitmap, 0, wxEXPAND | wxTOP | wxLEFT | wxRIGHT, 10);
    main_sizer->Add(status_panel, 0, wxEXPAND | wxTOP | wxLEFT | wxRIGHT, 10);
    main_sizer->Add(button_panel, 1, wxEXPAND | wxALL, 10);

    SetSizer(main_sizer);
    Fit();

    Hide();
}

TrimDataPanel::~TrimDataPanel() {}

void TrimDataPanel::OnButton(wxCommandEvent &e) {
    if (e.GetId() == Enum::G_Cancel_Button_ID) {
        controller->e_CancelButtonHandler(this);
    }

    if (e.GetId() == Enum::G_OK_Button_ID) {
        controller->e_OKButtonHandler(this);
    }

    if (e.GetId() == Enum::TD_Start_Button_ID) {
        auto button = button_panel->main_status_panel->start_Button;
        ToggleTrimDataButtonHandler(button);
    }

    if (e.GetId() == Enum::TD_Preview_Button_ID) {
        controller->e_ReplayStart(this);
    }

    if (e.GetId() == Enum::TD_Reset_Button_ID) {
        controller->e_RestoreDefault(this);
    }

    if (e.GetId() == Enum::TD_IncrementStart_Button_ID) {
        controller->e_IncrementStartPos(this);
    }

    if (e.GetId() == Enum::TD_DecrementStart_Button_ID) {
        controller->e_DecrementStartPos(this);
    }

    if (e.GetId() == Enum::TD_IncrementEnd_Button_ID) {
        controller->e_IncrementEndPos(this);
    }

    if (e.GetId() == Enum::TD_DecrementEnd_Button_ID) {
        controller->e_DecrementEndPos(this);
    }

    if (e.GetId() == Enum::TD_Range_Button_ID) {
        controller->e_PreviewCurrentRange(this);
    }

    // if (e.GetId() == Enum::MC_Start_Button_ID) {
    //     auto button = button_panel->main_status_panel->calibrate_Button;
    //     ToggleCalibrationButtonHandler(button);
    // }
    // if (e.GetId() == Enum::MC_StartCapture_Button_ID) {
    //     auto button = button_panel->main_status_panel->cCapture_Button;
    //     ToggleCalibrationCaptureButtonHandler(button);
    // }

    // if (e.GetId() == Enum::MC_SelectLeft_Button_ID) {
    //     controller->e_ChangeToLeft(this);
    // }

    // if (e.GetId() == Enum::MC_SelectRight_Button_ID) {
    //     controller->e_ChangeToRight(this);
    // }

    // if (e.GetId() == Enum::MC_RemoveLeft_Button_ID) {
    //     controller->e_ChangeToLeft(this);
    //     controller->e_RemoveLeft(this);
    // }

    // if (e.GetId() == Enum::MC_RemoveRight_Button_ID) {
    //     controller->e_ChangeToRight(this);
    //     controller->e_RemoveRight(this);
    // }

    // if (e.GetId() == Enum::MC_ToggleCamera_Button_ID) {
    //     auto button = button_panel->preview_panel->pCamera_button;
    //     TogglePreviewButtonHandler(button);
    // }

    // if (e.GetId() == Enum::MC_ToggleCapture_Button_ID) {
    //     auto button = button_panel->preview_panel->pCapture_button;
    //     TogglePreviewCaptureButtonHandler(button);
    // }

    // if (e.GetId() == Enum::MC_Remove_Button_ID) {
    //     controller->e_RemoveCalibData(this);
    // }

    controller->e_UpdateState(this);

    e.Skip();
}

void TrimDataPanel::ToggleTrimDataButtonHandler(BitmapButtonT2 *button) {
    if (button->getState() == ButtonState::OFF) {
        controller->e_TrimDataStart(button);
        return;
    }

    if (button->getState() == ButtonState::ON) {
        controller->e_TrimDataEnd(button);
        return;
    }
    throw std::runtime_error("Invalid button state");
}

void TrimDataPanel::OnUpdatePreview(UpdatePreviewEvent &e) {
    if (e.GetId() == UPDATE_PREVIEW) {
        wxBitmap image = e.GetImage();
        img_bitmap->setImage(image);
    }

    if (e.GetId() == CLEAR_PREVIEW) {
        img_bitmap->setNoImage();
    }
}

void TrimDataPanel::OnUpdateStatus(UpdateStatusEvent &e) {
    if (e.GetId() == UPDATE_STATUS) {
        wxString status = e.GetStatus();
        status_panel->SetText(status);
    }
}

void TrimDataPanel::OnUpdateState(UpdateStateEvent &e) {
    try {
        auto state = e.GetState();

        button_panel->main_status_panel->update(state);
        button_panel->set_start_panel->update(state);
        button_panel->set_end_panel->update(state);

        auto okState = state.trimDataPanel.okButtonState;
        auto cancelState = state.trimDataPanel.cancelButtonState;
        button_panel->ok_cancel_panel->update(okState, cancelState);

        Refresh();
    } catch (const std::exception &e) {
        ErrorEvent::Submit(this, e.what());
    }
}

void TrimDataPanel::OnReplay(wxCommandEvent &e) {
    if (e.GetId() == REPLAY_END) {
        controller->e_ReplayEnd(this);
    }
}

void TrimDataPanel::OnRequestUpdateState(wxCommandEvent &e) {
    if (e.GetId() == REQUEST_UPDATE_STATE) {
        controller->e_UpdateState(this);
    }
}

void TrimDataPanel::OnShow(wxShowEvent &e) {
    if (e.IsShown()) {
        controller->e_PanelShow(this);
    }
}

// clang-format off
wxBEGIN_EVENT_TABLE(TrimDataPanel, wxPanel)
    EVT_UPDATE_PREVIEW(wxID_ANY, TrimDataPanel::OnUpdatePreview)
    EVT_UPDATE_STATUS(wxID_ANY, TrimDataPanel::OnUpdateStatus)
    EVT_UPDATE_STATE(wxID_ANY, TrimDataPanel::OnUpdateState)
    EVT_COMMAND(wxID_ANY, c_REPLAY_EVENT, TrimDataPanel::OnReplay)
    EVT_COMMAND(wxID_ANY, c_REQUEST_UPDATE_STATE_EVENT, TrimDataPanel::OnRequestUpdateState)
    EVT_BUTTON(wxID_ANY,TrimDataPanel::OnButton) 
    EVT_SHOW(TrimDataPanel::OnShow)
wxEND_EVENT_TABLE()
