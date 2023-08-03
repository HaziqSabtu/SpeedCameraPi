#include "UI/Panel/ColorCalibrationPanel/Panel.hpp"
#include "Controller/ColorCalibrationController.hpp"
#include "Event/Event_Calibration.hpp"
#include "Event/Event_ChangePanel.hpp"
#include "Event/Event_UpdateState.hpp"
#include "Event/Event_UpdateStatus.hpp"

#include "UI/Layout/StatusPanel.hpp"
#include "UI/Panel/ColorCalibrationPanel/Panel_Button.hpp"
#include "Utils/Enum.hpp"
#include <UI/Panel/ColorCalibrationPanel/Panel.hpp>
#include <stdexcept>
#include <wx/gtk/stattext.h>
#include <wx/sizer.h>

namespace SC = StatusCollection;

ColorCalibrationPanel::ColorCalibrationPanel(wxWindow *parent, wxWindowID id,
                                             CCCPtr &controller)
    : wxPanel(parent, id), controller(std::move(controller)) {

    button_panel =
        new ColorCalibrationPanelButton(this, Enum::CP_BUTTON_PANEL_ID);

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

ColorCalibrationPanel::~ColorCalibrationPanel() {}

void ColorCalibrationPanel::OnButton(wxCommandEvent &e) {
    if (e.GetId() == Enum::G_Cancel_Button_ID) {
        controller->e_ChangeToCalibrationPanel(this);
    }

    // TODO: Implement this, Add Saving
    if (e.GetId() == Enum::G_OK_Button_ID) {
        controller->e_ChangeToCalibrationPanel(this);
    }

    if (e.GetId() == Enum::CC_ToggleCamera_Button_ID) {
        auto button = button_panel->main_status_panel->camera_Button;
        OnToggleCameraButton(button);
    }

    if (e.GetId() == Enum::CC_Start_Button_ID) {
        controller->e_ColorCalibrationStart(this);
    }

    if (e.GetId() == Enum::CC_Stop_Button_ID) {
        controller->e_ColorCalibrationEnd(this);
    }

    if (e.GetId() == Enum::CC_Remove_Button_ID) {
        controller->e_RemoveCalibratedRange(this);
    }

    if (e.GetId() == Enum::CC_SelectBlue_Button_ID) {
        controller->e_SetTypeBlue(this);
    }

    if (e.GetId() == Enum::CC_AcceptBlue_Button_ID) {
        controller->e_SaveBlue(this);
    }

    if (e.GetId() == Enum::CC_SelectYellow_Button_ID) {
        controller->e_SetTypeYellow(this);
    }

    if (e.GetId() == Enum::CC_AcceptYellow_Button_ID) {
        controller->e_SaveYellow(this);
    }

    if (e.GetId() == Enum::CC_Save_Button_ID) {
        controller->e_SaveToConfig(this);
    }

    if (e.GetId() == Enum::CC_Restore_Button_ID) {
        controller->e_RestoreRange(this);
    }

    controller->e_UpdateState(this);

    e.Skip();
}

void ColorCalibrationPanel::OnToggleCameraButton(BitmapButtonT2 *button) {
    if (button->getState() == ButtonState::OFF) {
        controller->e_ColorCalibrationPreviewStart(button);
        return;
    }

    if (button->getState() == ButtonState::ON) {
        controller->e_ColorCalibrationPreviewEnd(button);
        return;
    }
    throw std::runtime_error("Invalid button state");
}

void ColorCalibrationPanel::OnUpdatePreview(UpdatePreviewEvent &e) {
    if (e.GetId() == UPDATE_PREVIEW) {
        wxBitmap image = e.GetImage();
        img_bitmap->setImage(image);
    }

    if (e.GetId() == CLEAR_PREVIEW) {
        img_bitmap->setNoImage();
    }
}

void ColorCalibrationPanel::OnCalibrationEvent(wxCommandEvent &e) {
    if (e.GetId() == CALIBRATION_START) {
        status_panel->SetText(SC::STATUS_START_CALIBRATION);

        img_bitmap->Bind(wxEVT_LEFT_DOWN, &ColorCalibrationPanel::OnLeftDown,
                         this);
    }

    if (e.GetId() == CALIBRATION_END) {
        status_panel->SetText(SC::STATUS_CALIBRATION_END);

        img_bitmap->Unbind(wxEVT_LEFT_DOWN, &ColorCalibrationPanel::OnLeftDown,
                           this);
    }
    controller->e_UpdateState(this);
}

void ColorCalibrationPanel::OnCapture(wxCommandEvent &e) {
    if (e.GetId() == CAPTURE_START) {
        status_panel->SetText(SC::STATUS_CAMERA_ON);
    }

    if (e.GetId() == CAPTURE_END) {
        status_panel->SetText(SC::STATUS_CAMERA_OFF);
    }
}

void ColorCalibrationPanel::OnLeftDown(wxMouseEvent &e) {
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
}

void ColorCalibrationPanel::OnUpdateStatus(UpdateStatusEvent &e) {
    if (e.GetId() == UPDATE_STATUS) {
        wxString status = e.GetStatus();
        status_panel->SetText(status);
    }
}

void ColorCalibrationPanel::OnUpdateState(UpdateStateEvent &e) {
    try {
        auto state = e.GetState();
        button_panel->main_status_panel->update(state);
        button_panel->blue_status_panel->update(state);
        button_panel->yellow_status_panel->update(state);
        button_panel->other_status_panel->update(state);

        auto okState = state.colorCalibrationPanel.okButtonState;
        auto cancelState = state.colorCalibrationPanel.cancelButtonState;
        button_panel->ok_cancel_panel->update(okState, cancelState);

        Refresh();
    } catch (const std::exception &e) {
        ErrorEvent::Submit(this, e.what());
    }
}

void ColorCalibrationPanel::OnShow(wxShowEvent &e) {
    if (e.IsShown()) {
        controller->e_UpdateState(this);
    }
}

// clang-format off
wxBEGIN_EVENT_TABLE(ColorCalibrationPanel, wxPanel)
    EVT_UPDATE_PREVIEW(wxID_ANY, ColorCalibrationPanel::OnUpdatePreview)
    EVT_UPDATE_STATUS(wxID_ANY, ColorCalibrationPanel::OnUpdateStatus)
    EVT_UPDATE_STATE(wxID_ANY, ColorCalibrationPanel::OnUpdateState)
    EVT_BUTTON(wxID_ANY,ColorCalibrationPanel::OnButton) 
    EVT_COMMAND(wxID_ANY, c_CALIBRATION_EVENT, ColorCalibrationPanel::OnCalibrationEvent)
    EVT_COMMAND(wxID_ANY, c_CAPTURE_EVENT, ColorCalibrationPanel::OnCapture)
    EVT_SHOW(ColorCalibrationPanel::OnShow)
wxEND_EVENT_TABLE()
