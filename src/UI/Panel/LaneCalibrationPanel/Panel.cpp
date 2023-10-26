#include "Controller/ColorCalibrationController.hpp"
#include "Controller/LaneCalibrationController.hpp"
#include "Event/Event_Calibration.hpp"
#include "Event/Event_ChangePanel.hpp"
#include "Event/Event_Error.hpp"
#include "Event/Event_UpdateStatus.hpp"

#include "UI/Data/StatusData.hpp"
#include "UI/Layout/StatusPanel.hpp"
#include "UI/Panel/LaneCalibrationPanel/Panel_Button.hpp"
#include "Utils/Enum.hpp"
#include <UI/Panel/LaneCalibrationPanel/Panel.hpp>
#include <stdexcept>
#include <wx/event.h>

/**
 * @brief Construct a new Lane Calibration Panel:: Lane Calibration Panel object
 *
 * @param parent Pointer to the parent window
 * @param id ID of the panel
 * @param controller Pointer to the LaneCalibrationController
 */
LaneCalibrationPanel::LaneCalibrationPanel(wxWindow *parent, wxWindowID id,
                                           LCCPtr controller)
    : BasePanelWithTouch(parent, id, controller), controller(controller) {

    button_panel =
        new LaneCalibrationPanelButton(this, Enum::LC_Button_Panel_ID);
    title_panel = new TitlePanel(this, panel_id);

    size();
}

/**
 * @brief Destroy the Lane Calibration Panel:: Lane Calibration Panel object
 *
 */
LaneCalibrationPanel::~LaneCalibrationPanel() {}

/**
 * @brief Handle button events
 *
 */
void LaneCalibrationPanel::OnButton(wxCommandEvent &e) {

    LaneCalibrationPanelButton *button_panel =
        dynamic_cast<LaneCalibrationPanelButton *>(this->button_panel);

    if (e.GetId() == Enum::LC_ChangeManual_Button_ID) {
        controller->e_ChangeToManualPanel(this);
    }

    if (e.GetId() == Enum::LC_ChangeColor_Button_ID) {
        controller->e_ChangeToColorPanel(this);
    }

    if (e.GetId() == Enum::LC_Preview_Button_ID) {
        auto button = button_panel->MainPanel->Preview_Button;
        TogglePreviewButtonHandler(button);
    }

    if (e.GetId() == Enum::LC_Calibration_Button_ID) {
        auto button = button_panel->MainPanel->Calibrate_Button;
        ToggleCalibrationButtonHandler(button);
    }

    if (e.GetId() == Enum::LC_ClearCalibration_Button_ID) {
        controller->e_RemoveCalibrationData(this);
    }

    if (e.GetId() == Enum::LC_SelectPoint_Button_ID) {
        bindLeftDown();
        UpdateStatusEvent::Submit(this,
                                  SC::STATUS_LANE_CALIBRATION_SELECTPOINT);
    }

    if (e.GetId() == Enum::LC_ClearPoint_Button_ID) {
        controller->e_ClearPoint(this);
    }

    e.Skip();
}

/**
 * @brief Handle toggle preview button
 *
 */
void LaneCalibrationPanel::TogglePreviewButtonHandler(BitmapButtonT2 *button) {
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
void LaneCalibrationPanel::ToggleCalibrationButtonHandler(
    BitmapButtonT2 *button) {
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

/**
 * @brief Handle calibration events
 *
 */
void LaneCalibrationPanel::OnCalibrationEvent(wxCommandEvent &e) {
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
        status_panel->SetText(SC::STATUS_LANE_CALIBRATION_LINEOK);
    }

    if (e.GetId() == CALIBRATION_LINE_NOT_FOUND) {
        status_panel->SetText(SC::STATUS_LANE_CALIBRATION_LINENOTFOUND);
    }

    controller->e_UpdateState(this);
}

/**
 * @brief Handle preview capture events
 *
 */
void LaneCalibrationPanel::OnPreviewCapture(wxCommandEvent &e) {
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
 */
void LaneCalibrationPanel::OnPreviewCamera(wxCommandEvent &e) {
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

/**
 * @brief Handle left down event (override)
 *
 */
void LaneCalibrationPanel::doPostLeftDown() { unBindAll(); }

// clang-format off
wxBEGIN_EVENT_TABLE(LaneCalibrationPanel, BasePanelWithTouch)
    EVT_BUTTON(wxID_ANY,LaneCalibrationPanel::OnButton) 
    EVT_COMMAND(wxID_ANY, c_CALIBRATION_EVENT, LaneCalibrationPanel::OnCalibrationEvent)
    EVT_COMMAND(wxID_ANY, c_PREVIEW_CAPTURE_EVENT, LaneCalibrationPanel::OnPreviewCapture)
    EVT_COMMAND(wxID_ANY, c_PREVIEW_CAMERA_EVENT, LaneCalibrationPanel::OnPreviewCamera)
wxEND_EVENT_TABLE()
