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

    if (e.GetId() == Enum::CL_PreviewCamera_Button_ID) {
        auto button = button_panel->PreviewPanel->PreviewCamera_Button;
        TogglePreviewButtonHandler(button);
    }

    if (e.GetId() == Enum::CL_PreviewCapture_Button_ID) {
        auto button = button_panel->PreviewPanel->PreviewCapture_Button;
        TogglePreviewCaptureButtonHandler(button);
    }

    if (e.GetId() == Enum::CL_CalibrationCamera_Button_ID) {
        auto button = button_panel->MainPanel->CalibrateCamera_Button;
        ToggleCalibrationCameraButtonHandler(button);
    }

    if (e.GetId() == Enum::CL_CalibrationCapture_Button_ID) {
        auto button = button_panel->MainPanel->CalibrateCapture_Button;
        ToggleCalibrationCaptureButtonHandler(button);
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
        controller->e_CalibrationPreviewCameraStart(button);
        return;
    }

    if (button->getState() == ButtonState::ON) {
        controller->e_CalibrationPreviewCameraEnd(button);
        return;
    }
    throw std::runtime_error("Invalid button state");
}

void CalibrationPanel::TogglePreviewCaptureButtonHandler(
    BitmapButtonT2 *button) {
    if (button->getState() == ButtonState::OFF) {
        controller->e_CalibrationPreviewCaptureStart(button);
        return;
    }

    if (button->getState() == ButtonState::ON) {
        controller->e_CalibrationPreviewCaptureEnd(button);
        return;
    }
    throw std::runtime_error("Invalid button state");
}

void CalibrationPanel::ToggleCalibrationCameraButtonHandler(
    BitmapButtonT2 *button) {
    if (button->getState() == ButtonState::OFF) {
        controller->e_CalibrationCameraStart(button);
        return;
    }

    if (button->getState() == ButtonState::ON) {
        controller->e_CalibrationCameraEnd(button);
        return;
    }
    throw std::runtime_error("Invalid button state");
}

void CalibrationPanel::ToggleCalibrationCaptureButtonHandler(
    BitmapButtonT2 *button) {
    if (button->getState() == ButtonState::OFF) {
        controller->e_CalibrationCaptureStart(button);
        return;
    }

    if (button->getState() == ButtonState::ON) {
        controller->e_CalibrationCaptureEnd(button);
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
    }

    if (e.GetId() == CALIBRATION_CAMERA_ERROR) {
        status_panel->SetText(SC::STATUS_CALIBRATION_CAMERA_ERROR);
    }

    if (e.GetId() == CALIBRATION_CAPTURE_START) {
        status_panel->SetText(SC::STATUS_CALIBRATION_CAPTURE_START);
    }

    if (e.GetId() == CALIBRATION_CAPTURE_END) {
        status_panel->SetText(SC::STATUS_CALIBRATION_CAPTURE_END);
    }

    if (e.GetId() == CALIBRATION_CAPTURE_ERROR) {
        status_panel->SetText(SC::STATUS_CALIBRATION_CAPTURE_ERROR);
    }
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
