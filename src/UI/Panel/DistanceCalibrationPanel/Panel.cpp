#include "Controller/DistanceCalibrationController.hpp"
#include "Event/Event_Calibration.hpp"
#include "Event/Event_ChangePanel.hpp"
#include "Event/Event_UpdateStatus.hpp"

#include "Model/AppState.hpp"
#include "UI/Layout/StatusPanel.hpp"
#include "UI/Panel/Common/BasePanel.hpp"
#include "UI/Panel/DistanceCalibrationPanel/Panel_Button.hpp"
#include "Utils/Enum.hpp"
#include <UI/Panel/DistanceCalibrationPanel/Panel.hpp>
#include <stdexcept>
#include <wx/event.h>
#include <wx/gdicmn.h>
#include <wx/gtk/stattext.h>
#include <wx/sizer.h>

/**
 * @brief Construct a new Distance Calibration Panel:: Distance Calibration
 * Panel object
 *
 * @param parent Pointer to the parent window
 * @param id ID of the panel
 * @param controller Pointer to the DistanceCalibrationController
 */
DistanceCalibrationPanel::DistanceCalibrationPanel(wxWindow *parent,
                                                   wxWindowID id,
                                                   DCCPtr controller)
    : BasePanelWithTouch(parent, id, controller), controller(controller) {

    button_panel =
        new DistanceCalibrationPanelButton(this, Enum::DC_Button_Panel_ID);
    title_panel = new TitlePanel(this, panel_id);

    size();
}

/**
 * @brief Destroy the Distance Calibration Panel:: Distance Calibration Panel
 * object
 *
 */
DistanceCalibrationPanel::~DistanceCalibrationPanel() {}

/**
 * @brief Handle button events
 *
 */
void DistanceCalibrationPanel::OnButton(wxCommandEvent &e) {

    DistanceCalibrationPanelButton *button_panel =
        dynamic_cast<DistanceCalibrationPanelButton *>(this->button_panel);

    if (e.GetId() == Enum::DC_Calibration_Button_ID) {
        auto button = button_panel->MainPanel->Calibrate_Button;
        ToggleCalibrationButtonHandler(button);
    }

    if (e.GetId() == Enum::DC_SelectBottom_Button_ID) {
        controller->e_ChangeToBottom(this);
    }

    if (e.GetId() == Enum::DC_SelectTop_Button_ID) {
        controller->e_ChangeToTop(this);
    }

    if (e.GetId() == Enum::DC_RemoveBottom_Button_ID) {
        controller->e_ChangeToBottom(this);
        controller->e_RemoveBottom(this);
    }

    if (e.GetId() == Enum::DC_RemoveTop_Button_ID) {
        controller->e_ChangeToTop(this);
        controller->e_RemoveTop(this);
    }

    if (e.GetId() == Enum::DC_Preview_Button_ID) {
        auto button = button_panel->MainPanel->Preview_Button;
        TogglePreviewButtonHandler(button);
    }

    if (e.GetId() == Enum::DC_Remove_Button_ID) {
        controller->e_RemoveCalibrationData(this);
    }

    e.Skip();
}

/**
 * @brief Handle toggle of preview button
 *
 */
void DistanceCalibrationPanel::TogglePreviewButtonHandler(
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
 * @brief Handle toggle of calibration button
 *
 */
void DistanceCalibrationPanel::ToggleCalibrationButtonHandler(
    BitmapButtonT2 *button) {
    if (button->getState() == ButtonState::OFF) {
        controller->e_DistanceCalibrationStart(button);
        return;
    }

    if (button->getState() == ButtonState::ON) {
        controller->e_DistanceCalibrationEnd(button);
        return;
    }
    throw std::runtime_error("Invalid button state");
}

/**
 * @brief Handle calibration events
 *
 */
void DistanceCalibrationPanel::OnCalibrationEvent(wxCommandEvent &e) {
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
 * @brief Handle preview events
 *
 */
void DistanceCalibrationPanel::OnPreviewCapture(wxCommandEvent &e) {
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
void DistanceCalibrationPanel::OnPreviewCamera(wxCommandEvent &e) {
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
wxBEGIN_EVENT_TABLE(DistanceCalibrationPanel, BasePanelWithTouch)
    EVT_BUTTON(wxID_ANY, DistanceCalibrationPanel::OnButton)
    EVT_COMMAND(wxID_ANY, c_CALIBRATION_EVENT, DistanceCalibrationPanel::OnCalibrationEvent)
    EVT_COMMAND(wxID_ANY, c_PREVIEW_CAPTURE_EVENT, DistanceCalibrationPanel::OnPreviewCapture)
    EVT_COMMAND(wxID_ANY, c_PREVIEW_CAMERA_EVENT, DistanceCalibrationPanel::OnPreviewCamera)
wxEND_EVENT_TABLE()
