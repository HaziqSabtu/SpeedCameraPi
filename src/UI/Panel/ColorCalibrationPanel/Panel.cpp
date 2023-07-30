#include "UI/Panel/ColorCalibrationPanel/Panel.hpp"
#include "Controller/ColorCalibrationController.hpp"
#include "Event/Event_Calibration.hpp"
#include "Event/Event_ChangePanel.hpp"
#include "Event/Event_UpdateStatus.hpp"

#include "UI/Button/Button_wState.hpp"
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

    if (e.GetId() == Enum::CC_Start_Button_ID) {
        controller->e_ColorCalibrationStart(this);
    }

    if (e.GetId() == Enum::CC_Stop_Button_ID) {
        controller->e_ColorCalibrationEnd(this);
    }

    e.Skip();
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
    }

    if (e.GetId() == CALIBRATION_END) {
        status_panel->SetText(SC::STATUS_CALIBRATION_SUCCESS);
    }
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
            // model->e_SetPoint(this, wxPoint(x, y));
        }
    }
}

void ColorCalibrationPanel::OnUpdateStatus(UpdateStatusEvent &e) {
    if (e.GetId() == UPDATE_STATUS) {
        wxString status = e.GetStatus();
        status_panel->SetText(status);
    }
}

// clang-format off
wxBEGIN_EVENT_TABLE(ColorCalibrationPanel, wxPanel)
    EVT_UPDATE_PREVIEW(wxID_ANY, ColorCalibrationPanel::OnUpdatePreview)
    EVT_UPDATE_STATUS(wxID_ANY, ColorCalibrationPanel::OnUpdateStatus)
    EVT_BUTTON(wxID_ANY,ColorCalibrationPanel::OnButton) 
    EVT_COMMAND(wxID_ANY, c_CALIBRATION_EVENT, ColorCalibrationPanel::OnCalibrationEvent)
    EVT_COMMAND(wxID_ANY, c_CAPTURE_EVENT, ColorCalibrationPanel::OnCapture)
wxEND_EVENT_TABLE()
