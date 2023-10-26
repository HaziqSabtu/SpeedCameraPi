#include "Controller/LaneManualCalibrationController.hpp"
#include "Event/Event_Calibration.hpp"
#include "Event/Event_ChangePanel.hpp"
#include "Event/Event_Roi.hpp"
#include "Event/Event_UpdateStatus.hpp"

#include "Model/AppState.hpp"
#include "UI/Data/StatusData.hpp"
#include "UI/Layout/StatusPanel.hpp"
#include "UI/Panel/Common/BasePanel.hpp"
#include "UI/Panel/RoiPanel/Panel_Button.hpp"
#include "Utils/Enum.hpp"
#include <UI/Panel/RoiPanel/Panel.hpp>
#include <stdexcept>
#include <utility>
#include <wx/event.h>
#include <wx/gdicmn.h>
#include <wx/gtk/stattext.h>
#include <wx/sizer.h>

/**
 * @brief Construct a new RoiPanel::RoiPanel object
 *
 * @param parent Pointer to the parent window
 * @param id ID of the panel
 * @param controller Pointer to the RoiController
 */
RoiPanel::RoiPanel(wxWindow *parent, wxWindowID id, ROCPtr controller)
    : BasePanelWithTouch(parent, id, controller), controller(controller) {

    button_panel = new RoiPanelButton(this, Enum::RO_Button_Panel_ID);
    title_panel = new TitlePanel(this, panel_id);

    size();
}

/**
 * @brief Destroy the RoiPanel:: RoiPanel
 * object
 *
 */
RoiPanel::~RoiPanel() {}

/**
 * @brief Handle button events
 *
 */
void RoiPanel::OnButton(wxCommandEvent &e) {

    RoiPanelButton *button_panel =
        dynamic_cast<RoiPanelButton *>(this->button_panel);

    if (e.GetId() == Enum::RO_Calibration_Button_ID) {
        auto button = button_panel->MainPanel->Roi_Button;
        ToggleRoiButtonHandler(button);
    }

    if (e.GetId() == Enum::RO_Preview_Button_ID) {
        auto button = button_panel->MainPanel->Preview_Button;
        TogglePreviewButtonHandler(button);
    }

    if (e.GetId() == Enum::RO_Remove_Button_ID) {
        controller->e_RemoveRect(this);
    }

    if (e.GetId() == Enum::RO_RemoveRect_Button_ID) {
        controller->e_ClearRect(this);
    }

    if (e.GetId() == Enum::RO_AcceptRect_Button_ID) {
        controller->e_RoiThreadSave(this);
    }

    e.Skip();
}

/**
 * @brief Handle toggle roi button
 *
 */
void RoiPanel::ToggleRoiButtonHandler(BitmapButtonT2 *button) {
    if (button->getState() == ButtonState::OFF) {
        controller->e_RoiThreadStart(this);
        return;
    }

    if (button->getState() == ButtonState::ON) {
        controller->e_RoiThreadCancel(this);
        return;
    }

    throw std::runtime_error("Invalid button state");
}

/**
 * @brief Handle toggle preview button
 *
 */
void RoiPanel::TogglePreviewButtonHandler(BitmapButtonT2 *button) {
    if (button->getState() == ButtonState::OFF) {
        controller->e_RoiPreviewStart(button);
        return;
    }

    if (button->getState() == ButtonState::ON) {
        controller->e_RoiPreviewEnd(button);
        return;
    }

    throw std::runtime_error("Invalid button state");
}

/**
 * @brief Handle roi events
 *
 */
void RoiPanel::OnRoi(wxCommandEvent &e) {
    if (e.GetId() == ROI_START) {
        status_panel->SetText(SC::STATUS_ROI_SELECT);

        // Bind Left Down Event
        bindLeftDown();
    }

    if (e.GetId() == ROI_END) {
        status_panel->SetText(SC::STATUS_ROI_SAVE);
        unBindAll();
    }

    if (e.GetId() == ROI_ERROR) {
        status_panel->SetText(SC::STATUS_ROI_ERROR);
        unBindAll();
    }
}

/**
 * @brief Handle preview capture events
 *
 */
void RoiPanel::OnPreviewCapture(wxCommandEvent &e) {
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

// clang-format off
wxBEGIN_EVENT_TABLE(RoiPanel, BasePanelWithTouch)
    EVT_BUTTON(wxID_ANY,RoiPanel::OnButton) 
    EVT_COMMAND(wxID_ANY, c_ROI_EVENT, RoiPanel::OnRoi)
    EVT_COMMAND(wxID_ANY, c_PREVIEW_CAPTURE_EVENT, RoiPanel::OnPreviewCapture)
wxEND_EVENT_TABLE()
