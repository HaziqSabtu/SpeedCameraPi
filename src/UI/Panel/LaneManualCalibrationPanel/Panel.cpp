#include "Controller/LaneManualCalibrationController.hpp"
#include "Event/Event_Calibration.hpp"
#include "Event/Event_ChangePanel.hpp"
#include "Event/Event_UpdateStatus.hpp"

#include "Model/AppState.hpp"
#include "UI/Layout/StatusPanel.hpp"
#include "UI/Panel/Common/BasePanel.hpp"
#include "UI/Panel/LaneManualCalibrationPanel/Panel_Button.hpp"
#include "Utils/Enum.hpp"
#include <UI/Panel/LaneManualCalibrationPanel/Panel.hpp>
#include <stdexcept>
#include <wx/event.h>
#include <wx/gdicmn.h>
#include <wx/gtk/stattext.h>
#include <wx/sizer.h>

/**
 * @brief Construct a new LaneManualCalibrationPanel::
 * LaneManualCalibrationPanel object
 *
 * @param parent Pointer to the parent window
 * @param id ID of the panel
 * @param controller Pointer to the LaneManualCalibrationController
 */
LaneManualCalibrationPanel::LaneManualCalibrationPanel(wxWindow *parent,
                                                       wxWindowID id,
                                                       LMCPtr controller)
    : BasePanelWithTouch(parent, id, controller), controller(controller) {

    button_panel =
        new LaneManualCalibrationPanelButton(this, Enum::LM_Button_Panel_ID);
    title_panel = new TitlePanel(this, panel_id);

    size();
}

/**
 * @brief Destroy the LaneManualCalibrationPanel:: LaneManualCalibrationPanel
 *
 */
LaneManualCalibrationPanel::~LaneManualCalibrationPanel() {}

void LaneManualCalibrationPanel::OnButton(wxCommandEvent &e) {

    LaneManualCalibrationPanelButton *button_panel =
        dynamic_cast<LaneManualCalibrationPanelButton *>(this->button_panel);

    if (e.GetId() == Enum::LM_Calibration_Button_ID) {
        auto button = button_panel->MainPanel->Calibrate_Button;
        ToggleCalibrationButtonHandler(button);
    }

    if (e.GetId() == Enum::LM_SelectLeft_Button_ID) {
        controller->e_ChangeToLeft(this);
    }

    if (e.GetId() == Enum::LM_SelectRight_Button_ID) {
        controller->e_ChangeToRight(this);
    }

    if (e.GetId() == Enum::LM_RemoveLeft_Button_ID) {
        controller->e_ChangeToLeft(this);
        controller->e_RemoveLeft(this);
    }

    if (e.GetId() == Enum::LM_RemoveRight_Button_ID) {
        controller->e_ChangeToRight(this);
        controller->e_RemoveRight(this);
    }

    if (e.GetId() == Enum::LM_Preview_Button_ID) {
        auto button = button_panel->MainPanel->Preview_Button;
        TogglePreviewButtonHandler(button);
    }

    if (e.GetId() == Enum::LM_Remove_Button_ID) {
        controller->e_RemoveCalibrationData(this);
    }

    e.Skip();
}

/**
 * @brief Handle toggle preview button
 *
 */
void LaneManualCalibrationPanel::TogglePreviewButtonHandler(
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

/**
 * @brief Handle toggle calibration button
 *
 */
void LaneManualCalibrationPanel::ToggleCalibrationButtonHandler(
    BitmapButtonT2 *button) {
    if (button->getState() == ButtonState::OFF) {
        controller->e_ManualCalibrationStart(button);
        return;
    }

    if (button->getState() == ButtonState::ON) {
        controller->e_ManualCalibrationEnd(button);
        return;
    }

    throw std::runtime_error("Invalid button state");
}

/**
 * @brief Handle calibration events
 *
 * @param e Event
 */
void LaneManualCalibrationPanel::OnCalibrationEvent(wxCommandEvent &e) {
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

/**
 * @brief Handle preview capture events
 *
 * @param e Event
 */
void LaneManualCalibrationPanel::OnPreviewCapture(wxCommandEvent &e) {
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

/**
 * @brief Handle preview camera events
 *
 * @param e Event
 */
void LaneManualCalibrationPanel::OnPreviewCamera(wxCommandEvent &e) {
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
wxBEGIN_EVENT_TABLE(LaneManualCalibrationPanel, BasePanelWithTouch)
    EVT_BUTTON(wxID_ANY, LaneManualCalibrationPanel::OnButton)
    EVT_COMMAND(wxID_ANY, c_CALIBRATION_EVENT, LaneManualCalibrationPanel::OnCalibrationEvent)
    EVT_COMMAND(wxID_ANY, c_PREVIEW_CAPTURE_EVENT, LaneManualCalibrationPanel::OnPreviewCapture)
    EVT_COMMAND(wxID_ANY, c_PREVIEW_CAMERA_EVENT, LaneManualCalibrationPanel::OnPreviewCamera)
wxEND_EVENT_TABLE()
