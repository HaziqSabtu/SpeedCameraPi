#include "Controller/ManualCalibrationController.hpp"
#include "Event/Event_Calibration.hpp"
#include "Event/Event_ChangePanel.hpp"
#include "Event/Event_UpdateStatus.hpp"

#include "Model/AppState.hpp"
#include "UI/Button/Button_wState.hpp"
#include "UI/Layout/StatusPanel.hpp"
#include "UI/Panel/RoiPanel/Panel_Button.hpp"
#include "Utils/Enum.hpp"
#include <UI/Panel/RoiPanel/Panel.hpp>
#include <stdexcept>
#include <utility>
#include <wx/event.h>
#include <wx/gdicmn.h>
#include <wx/gtk/stattext.h>
#include <wx/sizer.h>

namespace SC = StatusCollection;

RoiPanel::RoiPanel(wxWindow *parent, wxWindowID id, ROCPtr &controller)
    : wxPanel(parent, id), controller(std::move(controller)) {

    button_panel = new RoiPanelButton(this, Enum::CP_BUTTON_PANEL_ID);

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

RoiPanel::~RoiPanel() {}

void RoiPanel::OnButton(wxCommandEvent &e) {
    if (e.GetId() == Enum::G_Cancel_Button_ID) {
        // controller->e_RestoreSessionData(this);
        controller->e_ChangeToCapturePanel(this);
    }

    if (e.GetId() == Enum::G_OK_Button_ID) {
        // controller->e_SaveSessionData(this);
        controller->e_ChangeToCapturePanel(this);
    }

    if (e.GetId() == Enum::RO_Start_Button_ID) {
        controller->e_RoiThreadStart(this);
    }

    if (e.GetId() == Enum::RO_Stop_Button_ID) {
        controller->e_RoiThreadEnd(this);
    }

    if (e.GetId() == Enum::RO_RemoveRect_Button_ID) {
        controller->e_ClearRect(this);
    }

    // if (e.GetId() == Enum::MC_Stop_Button_ID) {
    //     controller->e_ManualCalibEnd(this);
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
    //     auto button = button_panel->main_status_panel->camera_Button;
    //     OnToggleCameraButton(button);
    // }

    // controller->e_UpdateState(this);

    e.Skip();
}

void RoiPanel::OnToggleCameraButton(BitmapButtonT2 *button) {
    // if (button->getState() == ButtonState::OFF) {
    //     controller->e_CalibPrevStart(button);
    //     return;
    // }

    // if (button->getState() == ButtonState::ON) {
    //     controller->e_CalibPrevEnd(button);
    //     return;
    // }
    throw std::runtime_error("Invalid button state");
}

void RoiPanel::OnUpdatePreview(UpdatePreviewEvent &e) {
    if (e.GetId() == UPDATE_PREVIEW) {
        wxBitmap image = e.GetImage();
        img_bitmap->setImage(image);
    }

    if (e.GetId() == CLEAR_PREVIEW) {
        img_bitmap->setNoImage();
    }
}

void RoiPanel::OnCalibrationEvent(wxCommandEvent &e) {
    if (e.GetId() == CALIBRATION_START) {
        status_panel->SetText(SC::STATUS_START_CALIBRATION);

        // Bind Left Down Event
        img_bitmap->Bind(wxEVT_LEFT_DOWN, &RoiPanel::OnLeftDown, this);
    }

    if (e.GetId() == CALIBRATION_END) {
        status_panel->SetText(SC::STATUS_CALIBRATION_SUCCESS);
    }
}

void RoiPanel::OnCapture(wxCommandEvent &e) {
    if (e.GetId() == CAPTURE_START) {
        status_panel->SetText(SC::STATUS_CAMERA_ON);
        img_bitmap->Bind(wxEVT_LEFT_DOWN, &RoiPanel::OnLeftDown, this);
    }

    if (e.GetId() == CAPTURE_END) {
        status_panel->SetText(SC::STATUS_CAMERA_OFF);
    }
}

void RoiPanel::OnLeftDown(wxMouseEvent &e) {
    wxPoint pos = e.GetPosition();
    wxSize size = img_bitmap->GetSize();
    wxSize img_size = img_bitmap->getImageSize();

    if (pos.x > 0 && pos.x < size.x && pos.y > 0 && pos.y < size.y) {
        if (img_size.x > 0 && img_size.y > 0) {
            int x = pos.x * img_size.x / size.x;
            int y = pos.y * img_size.y / size.y;
            controller->e_SetPoint2(this, wxPoint(-1, -1));
            controller->e_SetPoint1(this, wxPoint(x, y));

            // Unbind Left Down Event
            img_bitmap->Unbind(wxEVT_LEFT_DOWN, &RoiPanel::OnLeftDown, this);

            // Bind Cursor Move Event and Left Up Event
            img_bitmap->Bind(wxEVT_MOTION, &RoiPanel::OnMotion, this);
            img_bitmap->Bind(wxEVT_LEFT_UP, &RoiPanel::OnLeftUp, this);
        }
    }
}

void RoiPanel::OnUpdateStatus(UpdateStatusEvent &e) {
    if (e.GetId() == UPDATE_STATUS) {
        wxString status = e.GetStatus();
        status_panel->SetText(status);
    }
}

void RoiPanel::OnMotion(wxMouseEvent &e) {
    wxPoint pos = e.GetPosition();
    wxSize size = img_bitmap->GetSize();
    wxSize img_size = img_bitmap->getImageSize();

    if (pos.x > 0 && pos.x < size.x && pos.y > 0 && pos.y < size.y) {
        if (img_size.x > 0 && img_size.y > 0) {
            int x = pos.x * img_size.x / size.x;
            int y = pos.y * img_size.y / size.y;
            controller->e_SetPoint2(this, wxPoint(x, y));
        }
    }
}

void RoiPanel::OnLeftUp(wxMouseEvent &e) {
    wxPoint pos = e.GetPosition();
    wxSize size = img_bitmap->GetSize();
    wxSize img_size = img_bitmap->getImageSize();

    if (pos.x > 0 && pos.x < size.x && pos.y > 0 && pos.y < size.y) {
        if (img_size.x > 0 && img_size.y > 0) {
            int x = pos.x * img_size.x / size.x;
            int y = pos.y * img_size.y / size.y;
            controller->e_SetPoint2(this, wxPoint(x, y));

            // Unbind Cursor Move Event and Left Up Event
            img_bitmap->Unbind(wxEVT_MOTION, &RoiPanel::OnMotion, this);
            img_bitmap->Unbind(wxEVT_LEFT_UP, &RoiPanel::OnLeftUp, this);

            // controller->e_SaveLine(this, wxPoint(x, y));

            // Bind Left Down Event
            img_bitmap->Bind(wxEVT_LEFT_DOWN, &RoiPanel::OnLeftDown, this);

            controller->e_UpdateState(this);
        }
    }
}

void RoiPanel::OnUpdateState(UpdateStateEvent &e) {
    try {
        auto state = e.GetState();

        // button_panel->main_status_panel->update(state);
        // button_panel->left_status_panel->update(state);
        // button_panel->right_status_panel->update(state);

        // auto okState = state.RoiPanel.okButtonState;
        // auto cancelState = state.RoiPanel.cancelButtonState;
        // button_panel->ok_cancel_panel->update(okState, cancelState);

        Refresh();
    } catch (const std::exception &e) {
        ErrorEvent::Submit(this, e.what());
    }
}

void RoiPanel::OnShow(wxShowEvent &e) {
    if (e.IsShown()) {
        // controller->e_CreateTempSessionData(this);
        // controller->e_UpdateState(this);
    }
}

// clang-format off
wxBEGIN_EVENT_TABLE(RoiPanel, wxPanel)
    EVT_UPDATE_PREVIEW(wxID_ANY, RoiPanel::OnUpdatePreview)
    EVT_UPDATE_STATUS(wxID_ANY, RoiPanel::OnUpdateStatus)
    // EVT_UPDATE_STATE(wxID_ANY, RoiPanel::OnUpdateState)
    EVT_BUTTON(wxID_ANY,RoiPanel::OnButton) 
    EVT_COMMAND(wxID_ANY, c_CALIBRATION_EVENT, RoiPanel::OnCalibrationEvent)
    EVT_COMMAND(wxID_ANY, c_CAPTURE_EVENT, RoiPanel::OnCapture)
    EVT_SHOW(RoiPanel::OnShow)
wxEND_EVENT_TABLE()
