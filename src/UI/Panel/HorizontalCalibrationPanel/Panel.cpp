#include "Controller/HorizontalCalibrationController.hpp"
#include "Event/Event_Calibration.hpp"
#include "Event/Event_ChangePanel.hpp"
#include "Event/Event_UpdateStatus.hpp"

#include "Model/AppState.hpp"
#include "UI/Layout/StatusPanel.hpp"
#include "UI/Panel/Common/BasePanel.hpp"
#include "UI/Panel/HorizontalCalibrationPanel/Panel_Button.hpp"
#include "Utils/Enum.hpp"
#include <UI/Panel/HorizontalCalibrationPanel/Panel.hpp>
#include <stdexcept>
#include <wx/event.h>
#include <wx/gdicmn.h>
#include <wx/gtk/stattext.h>
#include <wx/sizer.h>

HorizontalCalibrationPanel::HorizontalCalibrationPanel(wxWindow *parent,
                                                       wxWindowID id,
                                                       HCCPtr controller)
    : BasePanelWithTouch(parent, id, controller), controller(controller) {

    button_panel =
        new HorizontalCalibrationPanelButton(this, Enum::HC_Button_Panel_ID);
    title_panel = new TitlePanel(this, panel_id);

    size();
}

HorizontalCalibrationPanel::~HorizontalCalibrationPanel() {}

void HorizontalCalibrationPanel::OnButton(wxCommandEvent &e) {

    HorizontalCalibrationPanelButton *button_panel =
        dynamic_cast<HorizontalCalibrationPanelButton *>(this->button_panel);

    if (e.GetId() == Enum::HC_Calibration_Button_ID) {
        auto button = button_panel->MainPanel->Calibrate_Button;
        ToggleCalibrationButtonHandler(button);
    }

    if (e.GetId() == Enum::HC_SelectBottom_Button_ID) {
        controller->e_ChangeToBottom(this);
    }

    if (e.GetId() == Enum::HC_SelectTop_Button_ID) {
        controller->e_ChangeToTop(this);
    }

    if (e.GetId() == Enum::HC_RemoveBottom_Button_ID) {
        controller->e_ChangeToBottom(this);
        controller->e_RemoveBottom(this);
    }

    if (e.GetId() == Enum::HC_RemoveTop_Button_ID) {
        controller->e_ChangeToTop(this);
        controller->e_RemoveTop(this);
    }

    if (e.GetId() == Enum::HC_Preview_Button_ID) {
        auto button = button_panel->MainPanel->Preview_Button;
        TogglePreviewButtonHandler(button);
    }

    if (e.GetId() == Enum::HC_Remove_Button_ID) {
        controller->e_RemoveCalibrationData(this);
    }

    e.Skip();
}

void HorizontalCalibrationPanel::TogglePreviewButtonHandler(
    BitmapButtonT2 *button) {
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
void HorizontalCalibrationPanel::ToggleCalibrationButtonHandler(
    BitmapButtonT2 *button) {
    if (button->getState() == ButtonState::OFF) {
        controller->e_HorizontalCalibrationStart(button);
        return;
    }

    if (button->getState() == ButtonState::ON) {
        controller->e_HorizontalCalibrationEnd(button);
        return;
    }
    throw std::runtime_error("Invalid button state");
}

void HorizontalCalibrationPanel::OnCalibrationEvent(wxCommandEvent &e) {
    if (e.GetId() == CALIBRATION_CAMERA_START) {
        status_panel->SetText(SC::STATUS_CALIBRATION_CAMERA_START);
        bindLeftDown();
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
        bindLeftDown();
    }

    if (e.GetId() == CALIBRATION_CAPTURE_END) {
        status_panel->SetText(SC::STATUS_CALIBRATION_CAPTURE_END);
        unBindAll();
    }

    if (e.GetId() == CALIBRATION_CAPTURE_ERROR) {
        status_panel->SetText(SC::STATUS_CALIBRATION_CAPTURE_ERROR);
        unBindAll();
    }
}

void HorizontalCalibrationPanel::OnPreviewCapture(wxCommandEvent &e) {
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

void HorizontalCalibrationPanel::OnPreviewCamera(wxCommandEvent &e) {
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

// clang-format off
wxBEGIN_EVENT_TABLE(HorizontalCalibrationPanel, BasePanelWithTouch)
    EVT_BUTTON(wxID_ANY, HorizontalCalibrationPanel::OnButton)
    EVT_COMMAND(wxID_ANY, c_CALIBRATION_EVENT, HorizontalCalibrationPanel::OnCalibrationEvent)
    EVT_COMMAND(wxID_ANY, c_PREVIEW_CAPTURE_EVENT, HorizontalCalibrationPanel::OnPreviewCapture)
    EVT_COMMAND(wxID_ANY, c_PREVIEW_CAMERA_EVENT, HorizontalCalibrationPanel::OnPreviewCamera)
wxEND_EVENT_TABLE()
