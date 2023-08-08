#include "Controller/CalibrationController.hpp"
#include "Controller/ColorCalibrationController.hpp"
#include "Event/Event_Calibration.hpp"
#include "Event/Event_ChangePanel.hpp"
#include "Event/Event_Error.hpp"
#include "Event/Event_UpdateStatus.hpp"

#include "UI/Layout/StatusPanel.hpp"
#include "UI/Panel/CalibrationPanel/Panel_Button.hpp"
#include "Utils/Enum.hpp"
#include <UI/Panel/CalibrationPanel/Panel.hpp>
#include <stdexcept>
#include <wx/event.h>

namespace SC = StatusCollection;

CalibrationPanel::CalibrationPanel(wxWindow *parent, wxWindowID id,
                                   CLCPtr &controller)
    : wxPanel(parent, id), controller(std::move(controller)) {
    button_panel = new CalibrationPanelButton(this, Enum::CP_BUTTON_PANEL_ID);

    img_bitmap = new BaseImagePanel(this);

    title_panel = new TitlePanel(this, panel_id);

    status_panel = new StatusPanel(this, SC::STATUS_IDLE);

    main_sizer = new wxBoxSizer(wxVERTICAL);
    main_sizer->Add(title_panel, 0, wxEXPAND | wxTOP | wxLEFT | wxRIGHT, 10);
    main_sizer->Add(img_bitmap, 0, wxEXPAND | wxTOP | wxLEFT | wxRIGHT, 10);
    main_sizer->Add(status_panel, 0, wxEXPAND | wxTOP | wxLEFT | wxRIGHT, 10);
    main_sizer->Add(button_panel, 1,
                    wxEXPAND | wxTOP | wxLEFT | wxRIGHT | wxBOTTOM, 10);

    SetSizer(main_sizer);
    Fit();

    Hide();
}

CalibrationPanel::~CalibrationPanel() {}

void CalibrationPanel::OnButton(wxCommandEvent &e) {
    if (e.GetId() == Enum::G_Cancel_Button_ID) {
        controller->e_RestoreSessionData(this);
        controller->e_ChangeToCapturePanel(this);
    }

    if (e.GetId() == Enum::G_OK_Button_ID) {
        controller->e_SaveSessionData(this);
        controller->e_ChangeToCapturePanel(this);
    }

    if (e.GetId() == Enum::CL_ChangeManual_Button_ID) {
        controller->e_ChangeToManualPanel(this);
    }

    if (e.GetId() == Enum::CL_ChangeColor_Button_ID) {
        controller->e_ChangeToColorPanel(this);
    }

    if (e.GetId() == Enum::CL_ToggleCamera_Button_ID) {
        auto button = button_panel->cPanel->camera_Button;
        OnToggleCameraButton(button);
    }

    if (e.GetId() == Enum::CL_Start_Button_ID) {
        controller->e_CalibrationStart(this);
    }

    if (e.GetId() == Enum::CL_SaveCalibration_Button_ID) {
        controller->e_CalibrationSave(this);
        unBindImagePanel();
    }

    if (e.GetId() == Enum::CL_CancelCalibration_Button_ID) {
        controller->e_CalibrationEnd(this);
        unBindImagePanel();
    }

    if (e.GetId() == Enum::CL_ClearCalibration_Button_ID) {
        controller->e_RemoveCalibData(this);
    }

    if (e.GetId() == Enum::CL_SelectPoint_Button_ID) {
        img_bitmap->Bind(wxEVT_LEFT_DOWN, &CalibrationPanel::OnLeftDown, this);
    }

    controller->e_UpdateState(this);

    e.Skip();
}

void CalibrationPanel::unBindImagePanel() {
    img_bitmap->Unbind(wxEVT_LEFT_DOWN, &CalibrationPanel::OnLeftDown, this);
}

void CalibrationPanel::OnToggleCameraButton(BitmapButtonT2 *button) {
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

void CalibrationPanel::OnUpdatePreview(UpdatePreviewEvent &e) {
    if (e.GetId() == UPDATE_PREVIEW) {
        wxBitmap image = e.GetImage();
        img_bitmap->setImage(image);
    }

    if (e.GetId() == CLEAR_PREVIEW) {
        img_bitmap->setNoImage();
    }
}

void CalibrationPanel::OnCalibrationEvent(wxCommandEvent &e) {
    if (e.GetId() == CALIBRATION_START) {
        status_panel->SetText(SC::STATUS_START_CALIBRATION);
    }

    if (e.GetId() == CALIBRATION_END) {
        status_panel->SetText(SC::STATUS_CALIBRATION_SUCCESS);
    }
}

void CalibrationPanel::OnCapture(wxCommandEvent &e) {
    if (e.GetId() == CAPTURE_START) {
        status_panel->SetText(SC::STATUS_CAMERA_ON);
    }

    if (e.GetId() == CAPTURE_END) {
        status_panel->SetText(SC::STATUS_CAMERA_OFF);
    }
}

void CalibrationPanel::OnLeftDown(wxMouseEvent &e) {
    wxPoint pos = e.GetPosition();
    wxSize size = img_bitmap->GetSize();
    wxSize img_size = img_bitmap->getImageSize();

    if (pos.x > 0 && pos.x < size.x && pos.y > 0 && pos.y < size.y) {
        if (img_size.x > 0 && img_size.y > 0) {
            int x = pos.x * img_size.x / size.x;
            int y = pos.y * img_size.y / size.y;
            controller->e_SetPoint(this, wxPoint(x, y));
        }
    }
    img_bitmap->Unbind(wxEVT_LEFT_DOWN, &CalibrationPanel::OnLeftDown, this);
}

void CalibrationPanel::OnUpdateState(UpdateStateEvent &e) {
    try {
        auto state = e.GetState();
        button_panel->cPanel->update(state);
        button_panel->ctPanel->update(state);
        button_panel->cpPanel->update(state);
        button_panel->coPanel->update(state);

        auto okState = state.calibrationPanel.okButtonState;
        auto cancelState = state.calibrationPanel.cancelButtonState;
        button_panel->okCancelPanel->update(okState, cancelState);

        Refresh();
        Layout();
    } catch (const std::exception &e) {
        ErrorEvent::Submit(this, e.what());
    }
}

void CalibrationPanel::OnUpdateStatus(UpdateStatusEvent &e) {
    try {
        auto status = e.GetStatus();
        status_panel->SetText(status);
        Refresh();
    } catch (const std::exception &e) {
        ErrorEvent::Submit(this, e.what());
    }
}

void CalibrationPanel::OnShow(wxShowEvent &e) {
    if (e.IsShown()) {
        // controller->e_CreateTempSessionData(this);
        controller->e_UpdateState(this);
    }
}

// clang-format off
wxBEGIN_EVENT_TABLE(CalibrationPanel, wxPanel)
    EVT_UPDATE_PREVIEW(wxID_ANY, CalibrationPanel::OnUpdatePreview)
    EVT_UPDATE_STATUS(wxID_ANY, CalibrationPanel::OnUpdateStatus)
    EVT_UPDATE_STATE(wxID_ANY, CalibrationPanel::OnUpdateState)
    EVT_BUTTON(wxID_ANY,CalibrationPanel::OnButton) 
    EVT_COMMAND(wxID_ANY, c_CALIBRATION_EVENT, CalibrationPanel::OnCalibrationEvent)
    EVT_COMMAND(wxID_ANY, c_CAPTURE_EVENT, CalibrationPanel::OnCapture)
    EVT_SHOW(CalibrationPanel::OnShow)
wxEND_EVENT_TABLE()
