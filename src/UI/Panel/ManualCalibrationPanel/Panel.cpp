#include "Controller/ManualCalibrationController.hpp"
#include "Event/Event_Calibration.hpp"
#include "Event/Event_ChangePanel.hpp"
#include "Event/Event_UpdateStatus.hpp"

#include "Model/AppState.hpp"
#include "UI/Layout/StatusPanel.hpp"
#include "UI/Panel/ManualCalibrationPanel/Panel_Button.hpp"
#include "Utils/Enum.hpp"
#include <UI/Panel/ManualCalibrationPanel/Panel.hpp>
#include <stdexcept>
#include <wx/event.h>
#include <wx/gdicmn.h>
#include <wx/gtk/stattext.h>
#include <wx/sizer.h>

namespace SC = StatusCollection;

ManualCalibrationPanel::ManualCalibrationPanel(wxWindow *parent, wxWindowID id,
                                               MCCPtr &controller)
    : wxPanel(parent, id), controller(std::move(controller)) {

    button_panel =
        new ManualCalibrationPanelButton(this, Enum::CP_BUTTON_PANEL_ID);

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

ManualCalibrationPanel::~ManualCalibrationPanel() {}

void ManualCalibrationPanel::OnButton(wxCommandEvent &e) {
    if (e.GetId() == Enum::G_Cancel_Button_ID) {
        // controller->e_RestoreSessionData(this);
        controller->e_ChangeToCapturePanel(this);
    }

    if (e.GetId() == Enum::G_OK_Button_ID) {
        controller->e_SaveSessionData(this);
        controller->e_ChangeToCapturePanel(this);
    }

    if (e.GetId() == Enum::MC_Start_Button_ID) {
        auto button = button_panel->main_status_panel->calibrate_Button;
        ToggleCalibrationButtonHandler(button);
    }
    if (e.GetId() == Enum::MC_StartCapture_Button_ID) {
        auto button = button_panel->main_status_panel->cCapture_Button;
        ToggleCalibrationCaptureButtonHandler(button);
    }

    if (e.GetId() == Enum::MC_SelectLeft_Button_ID) {
        controller->e_ChangeToLeft(this);
    }

    if (e.GetId() == Enum::MC_SelectRight_Button_ID) {
        controller->e_ChangeToRight(this);
    }

    if (e.GetId() == Enum::MC_RemoveLeft_Button_ID) {
        controller->e_ChangeToLeft(this);
        controller->e_RemoveLeft(this);
    }

    if (e.GetId() == Enum::MC_RemoveRight_Button_ID) {
        controller->e_ChangeToRight(this);
        controller->e_RemoveRight(this);
    }

    if (e.GetId() == Enum::MC_ToggleCamera_Button_ID) {
        auto button = button_panel->preview_panel->pCamera_button;
        TogglePreviewButtonHandler(button);
    }

    if (e.GetId() == Enum::MC_ToggleCapture_Button_ID) {
        auto button = button_panel->preview_panel->pCapture_button;
        TogglePreviewCaptureButtonHandler(button);
    }

    if (e.GetId() == Enum::MC_Remove_Button_ID) {
        controller->e_RemoveCalibData(this);
    }

    controller->e_UpdateState(this);

    e.Skip();
}

void ManualCalibrationPanel::unBindImagePanel() {
    img_bitmap->Unbind(wxEVT_LEFT_DOWN, &ManualCalibrationPanel::OnLeftDown,
                       this);
    img_bitmap->Unbind(wxEVT_LEFT_UP, &ManualCalibrationPanel::OnLeftUp, this);
    img_bitmap->Unbind(wxEVT_MOTION, &ManualCalibrationPanel::OnMotion, this);
}

void ManualCalibrationPanel::TogglePreviewButtonHandler(
    BitmapButtonT2 *button) {
    if (button->getState() == ButtonState::OFF) {
        controller->e_CalibPrevStart(button);
        return;
    }

    if (button->getState() == ButtonState::ON) {
        controller->e_CalibPrevEnd(button);
        return;
    }
    throw std::runtime_error("Invalid button state");
}

void ManualCalibrationPanel::TogglePreviewCaptureButtonHandler(
    BitmapButtonT2 *button) {
    if (button->getState() == ButtonState::OFF) {
        controller->e_CalibCapturePrevStart(button);
        return;
    }

    if (button->getState() == ButtonState::ON) {
        controller->e_CalibCapturePrevEnd(button);
        return;
    }
    throw std::runtime_error("Invalid button state");
}

void ManualCalibrationPanel::ToggleCalibrationButtonHandler(
    BitmapButtonT2 *button) {
    if (button->getState() == ButtonState::OFF) {
        controller->e_ManualCalibStart(button);
        return;
    }

    if (button->getState() == ButtonState::ON) {
        controller->e_ManualCalibEnd(button);
        return;
    }
    throw std::runtime_error("Invalid button state");
}

void ManualCalibrationPanel::ToggleCalibrationCaptureButtonHandler(
    BitmapButtonT2 *button) {
    if (button->getState() == ButtonState::OFF) {
        controller->e_ManualCalibCaptureStart(button);
        return;
    }

    if (button->getState() == ButtonState::ON) {
        controller->e_ManualCalibCaptureEnd(button);
        return;
    }
    throw std::runtime_error("Invalid button state");
}

void ManualCalibrationPanel::OnUpdatePreview(UpdatePreviewEvent &e) {
    if (e.GetId() == UPDATE_PREVIEW) {
        wxBitmap image = e.GetImage();
        img_bitmap->setImage(image);
    }

    if (e.GetId() == CLEAR_PREVIEW) {
        img_bitmap->setNoImage();
    }
}

void ManualCalibrationPanel::OnCalibrationEvent(wxCommandEvent &e) {
    if (e.GetId() == CALIBRATION_START) {
        status_panel->SetText(SC::STATUS_START_CALIBRATION);

        // Bind Left Down Event
        img_bitmap->Bind(wxEVT_LEFT_DOWN, &ManualCalibrationPanel::OnLeftDown,
                         this);
    }

    if (e.GetId() == CALIBRATION_END) {
        status_panel->SetText(SC::STATUS_CALIBRATION_SUCCESS);
    }
}

void ManualCalibrationPanel::OnCapture(wxCommandEvent &e) {
    if (e.GetId() == CAPTURE_START) {
        status_panel->SetText(SC::STATUS_CAMERA_ON);
    }

    if (e.GetId() == CAPTURE_END) {
        status_panel->SetText(SC::STATUS_CAMERA_OFF);
    }
}

void ManualCalibrationPanel::OnLeftDown(wxMouseEvent &e) {
    wxPoint pos = e.GetPosition();
    wxSize size = img_bitmap->GetSize();
    wxSize img_size = img_bitmap->getImageSize();

    if (pos.x > 0 && pos.x < size.x && pos.y > 0 && pos.y < size.y) {
        if (img_size.x > 0 && img_size.y > 0) {
            int x = pos.x * img_size.x / size.x;
            int y = pos.y * img_size.y / size.y;
            controller->e_SetPoint1(this, wxPoint(x, y));

            // Unbind Left Down Event
            img_bitmap->Unbind(wxEVT_LEFT_DOWN,
                               &ManualCalibrationPanel::OnLeftDown, this);

            // Bind Cursor Move Event and Left Up Event
            img_bitmap->Bind(wxEVT_MOTION, &ManualCalibrationPanel::OnMotion,
                             this);
            img_bitmap->Bind(wxEVT_LEFT_UP, &ManualCalibrationPanel::OnLeftUp,
                             this);
        }
    }
}

void ManualCalibrationPanel::OnUpdateStatus(UpdateStatusEvent &e) {
    if (e.GetId() == UPDATE_STATUS) {
        wxString status = e.GetStatus();
        status_panel->SetText(status);
    }
}

void ManualCalibrationPanel::OnMotion(wxMouseEvent &e) {
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

void ManualCalibrationPanel::OnLeftUp(wxMouseEvent &e) {
    wxPoint pos = e.GetPosition();
    wxSize size = img_bitmap->GetSize();
    wxSize img_size = img_bitmap->getImageSize();

    if (pos.x > 0 && pos.x < size.x && pos.y > 0 && pos.y < size.y) {
        if (img_size.x > 0 && img_size.y > 0) {
            int x = pos.x * img_size.x / size.x;
            int y = pos.y * img_size.y / size.y;
            controller->e_SetPoint2(this, wxPoint(x, y));

            // Unbind Cursor Move Event and Left Up Event
            img_bitmap->Unbind(wxEVT_MOTION, &ManualCalibrationPanel::OnMotion,
                               this);
            img_bitmap->Unbind(wxEVT_LEFT_UP, &ManualCalibrationPanel::OnLeftUp,
                               this);

            controller->e_SaveLine(this, wxPoint(x, y));

            // Bind Left Down Event
            img_bitmap->Bind(wxEVT_LEFT_DOWN,
                             &ManualCalibrationPanel::OnLeftDown, this);

            controller->e_UpdateState(this);
        }
    }
}

void ManualCalibrationPanel::OnUpdateState(UpdateStateEvent &e) {
    try {
        auto state = e.GetState();

        button_panel->main_status_panel->update(state);
        button_panel->left_status_panel->update(state);
        button_panel->right_status_panel->update(state);
        button_panel->preview_panel->update(state);

        auto okState = state.manualCalibrationPanel.okButtonState;
        auto cancelState = state.manualCalibrationPanel.cancelButtonState;
        button_panel->ok_cancel_panel->update(okState, cancelState);

        Refresh();
    } catch (const std::exception &e) {
        ErrorEvent::Submit(this, e.what());
    }
}

void ManualCalibrationPanel::OnShow(wxShowEvent &e) {
    if (e.IsShown()) {
        // controller->e_CreateTempSessionData(this);
        controller->e_UpdateState(this);
    }
}

// clang-format off
wxBEGIN_EVENT_TABLE(ManualCalibrationPanel, wxPanel)
    EVT_UPDATE_PREVIEW(wxID_ANY, ManualCalibrationPanel::OnUpdatePreview)
    EVT_UPDATE_STATUS(wxID_ANY, ManualCalibrationPanel::OnUpdateStatus)
    EVT_UPDATE_STATE(wxID_ANY, ManualCalibrationPanel::OnUpdateState)
    EVT_BUTTON(wxID_ANY,ManualCalibrationPanel::OnButton) 
    EVT_COMMAND(wxID_ANY, c_CALIBRATION_EVENT, ManualCalibrationPanel::OnCalibrationEvent)
    EVT_COMMAND(wxID_ANY, c_CAPTURE_EVENT, ManualCalibrationPanel::OnCapture)
    EVT_SHOW(ManualCalibrationPanel::OnShow)
wxEND_EVENT_TABLE()
