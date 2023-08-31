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
                                   CLCPtr controller)
    : BasePanelWithTouch(parent, id, controller), controller(controller) {

    button_panel = new CalibrationPanelButton(this, Enum::CP_BUTTON_PANEL_ID);
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

    if (e.GetId() == Enum::CL_ToggleCamera_Button_ID) {
        auto button = button_panel->cpPanel->pCamera_button;
        TogglePreviewButtonHandler(button);
    }

    if (e.GetId() == Enum::CL_ToggleCapture_Button_ID) {
        auto button = button_panel->cpPanel->pCapture_button;
        TogglePreviewCaptureButtonHandler(button);
    }

    if (e.GetId() == Enum::CL_Start_Button_ID) {
        auto button = button_panel->cPanel->calibrate_Button;
        ToggleCalibrationCameraButtonHandler(button);
    }

    if (e.GetId() == Enum::CL_StartC_Button_ID) {
        auto button = button_panel->cPanel->cCapture_Button;
        ToggleCalibrationCaptureButtonHandler(button);
    }

    if (e.GetId() == Enum::CL_ClearCalibration_Button_ID) {
        controller->e_RemoveCalibData(this);
    }

    if (e.GetId() == Enum::CL_SelectPoint_Button_ID) {
        bindLeftDown();
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
    if (e.GetId() == CALIBRATION_START) {
        status_panel->SetText(SC::STATUS_START_CALIBRATION);
    }

    if (e.GetId() == CALIBRATION_END) {
        status_panel->SetText(SC::STATUS_CALIBRATION_SUCCESS);
    }
}

void CalibrationPanel::doPostLeftDown() { unBindAll(); }

// clang-format off
wxBEGIN_EVENT_TABLE(CalibrationPanel, BasePanelWithTouch)
    EVT_BUTTON(wxID_ANY,CalibrationPanel::OnButton) 
    EVT_COMMAND(wxID_ANY, c_CALIBRATION_EVENT, CalibrationPanel::OnCalibrationEvent)
wxEND_EVENT_TABLE()
