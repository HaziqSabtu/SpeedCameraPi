#include "Controller/CalibrationController.hpp"
#include "Controller/ColorCalibrationController.hpp"
#include "Event/Event_Calibration.hpp"
#include "Event/Event_ChangePanel.hpp"
#include "Event/Event_Error.hpp"
#include "Event/Event_UpdateStatus.hpp"

#include "UI/Data/StatusData.hpp"
#include "UI/Layout/StatusPanel.hpp"
#include "UI/Panel/CalibrationPanel/Panel_Button.hpp"
#include "Utils/Enum.hpp"
#include <UI/Panel/CalibrationPanel/Panel.hpp>
#include <stdexcept>
#include <wx/event.h>

CalibrationPanel::CalibrationPanel(wxWindow *parent, wxWindowID id,
                                   CLCPtr controller)
    : BasePanelWithTouch(parent, id, controller), controller(controller) {

    button_panel = new CalibrationPanelButton(this, Enum::CL_Button_Panel_ID);
    title_panel = new TitlePanel(this, panel_id);

    size();
}

CalibrationPanel::~CalibrationPanel() {}

void CalibrationPanel::OnButton(wxCommandEvent &e) {

    CalibrationPanelButton *button_panel =
        dynamic_cast<CalibrationPanelButton *>(this->button_panel);

    if (e.GetId() == Enum::CL_ChangeManual_Button_ID) {
        controller->e_ChangeToManualPanel(this);
    }

    if (e.GetId() == Enum::CL_ChangeColor_Button_ID) {
        controller->e_ChangeToColorPanel(this);
    }

    if (e.GetId() == Enum::CL_Preview_Button_ID) {
        auto button = button_panel->MainPanel->Preview_Button;
        TogglePreviewButtonHandler(button);
    }

    if (e.GetId() == Enum::CL_Calibration_Button_ID) {
        auto button = button_panel->MainPanel->Calibrate_Button;
        ToggleCalibrationButtonHandler(button);
    }

    if (e.GetId() == Enum::CL_ClearCalibration_Button_ID) {
        controller->e_RemoveCalibrationData(this);
    }

    if (e.GetId() == Enum::CL_SelectPoint_Button_ID) {
        bindLeftDown();
        UpdateStatusEvent::Submit(this, SC::STATUS_CALIBRATION_SELECTPOINT);
    }

    if (e.GetId() == Enum::CL_ClearPoint_Button_ID) {
        controller->e_ClearPoint(this);
    }

    e.Skip();
}

void CalibrationPanel::TogglePreviewButtonHandler(BitmapButtonT2 *button) {
    if (button->getState() == ButtonState::OFF) {
        controller->e_CalibrationPreviewStart(button);
        return;
    }

    if (button->getState() == ButtonState::ON) {
        controller->e_CalibrationPreviewEnd(button);
        return;
    }
    throw std::runtime_error("Invalid button state");
}

void CalibrationPanel::ToggleCalibrationButtonHandler(BitmapButtonT2 *button) {
    if (button->getState() == ButtonState::OFF) {
        controller->e_CalibrationStart(button);
        return;
    }

    if (button->getState() == ButtonState::ON) {
        controller->e_CalibrationEnd(button);
        return;
    }
    throw std::runtime_error("Invalid button state");
}

void CalibrationPanel::OnCalibrationEvent(wxCommandEvent &e) {
    if (e.GetId() == CALIBRATION_CAMERA_START) {
        status_panel->SetText(SC::STATUS_CALIBRATION_CAMERA_START);
    }

    if (e.GetId() == CALIBRATION_CAMERA_END) {
        status_panel->SetText(SC::STATUS_CALIBRATION_CAMERA_END);
        unBindAll();
    }

    if (e.GetId() == CALIBRATION_CAMERA_ERROR) {
        status_panel->SetText(SC::STATUS_CALIBRATION_CAMERA_ERROR);
        unBindAll();
    }

    if (e.GetId() == CALIBRATION_CAPTURE_START) {
        status_panel->SetText(SC::STATUS_CALIBRATION_CAPTURE_START);
    }

    if (e.GetId() == CALIBRATION_CAPTURE_END) {
        status_panel->SetText(SC::STATUS_CALIBRATION_CAPTURE_END);
        unBindAll();
    }

    if (e.GetId() == CALIBRATION_CAPTURE_ERROR) {
        status_panel->SetText(SC::STATUS_CALIBRATION_CAPTURE_ERROR);
        unBindAll();
    }

    if (e.GetId() == CALIBRATION_LINE_FOUND) {
        controller->e_SaveData(this);
        status_panel->SetText(SC::STATUS_CALIBRATION_LINEOK);
    }

    if (e.GetId() == CALIBRATION_LINE_NOT_FOUND) {
        status_panel->SetText(SC::STATUS_CALIBRATION_LINENOTFOUND);
    }

    controller->e_UpdateState(this);
}

void CalibrationPanel::OnPreviewCapture(wxCommandEvent &e) {
    if (e.GetId() == PREVIEW_START) {
        UpdateStatusEvent::Submit(this, SC::STATUS_PREVIEW_CAPTURE_START);
    }

    if (e.GetId() == PREVIEW_END) {
        UpdateStatusEvent::Submit(this, SC::STATUS_PREVIEW_CAPTURE_END);
    }

    if (e.GetId() == PREVIEW_ERROR) {
        UpdateStatusEvent::Submit(this, SC::STATUS_PREVIEW_CAPTURE_ERROR);
    }

    controller->e_UpdateState(this);
    e.Skip();
}

void CalibrationPanel::OnPreviewCamera(wxCommandEvent &e) {
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

void CalibrationPanel::doPostLeftDown() { unBindAll(); }

// clang-format off
wxBEGIN_EVENT_TABLE(CalibrationPanel, BasePanelWithTouch)
    EVT_BUTTON(wxID_ANY,CalibrationPanel::OnButton) 
    EVT_COMMAND(wxID_ANY, c_CALIBRATION_EVENT, CalibrationPanel::OnCalibrationEvent)
    EVT_COMMAND(wxID_ANY, c_PREVIEW_CAPTURE_EVENT, CalibrationPanel::OnPreviewCapture)
    EVT_COMMAND(wxID_ANY, c_PREVIEW_CAMERA_EVENT, CalibrationPanel::OnPreviewCamera)
wxEND_EVENT_TABLE()
