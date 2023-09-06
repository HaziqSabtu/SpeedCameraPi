#include "Controller/ManualCalibrationController.hpp"
#include "Event/Event_Calibration.hpp"
#include "Event/Event_ChangePanel.hpp"
#include "Event/Event_UpdateStatus.hpp"

#include "Model/AppState.hpp"
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

RoiPanel::RoiPanel(wxWindow *parent, wxWindowID id, ROCPtr controller)
    : BasePanelWithTouch(parent, id, controller), controller(controller) {

    button_panel = new RoiPanelButton(this, Enum::RO_Button_Panel_ID);
    title_panel = new TitlePanel(this, panel_id);

    size();
}

RoiPanel::~RoiPanel() {}

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

void RoiPanel::OnCalibrationEvent(wxCommandEvent &e) {
    if (e.GetId() == CALIBRATION_CAMERA_START) {
        status_panel->SetText(SC::STATUS_START_CALIBRATION);

        // Bind Left Down Event
        bindLeftDown();
    }

    if (e.GetId() == CALIBRATION_CAMERA_END) {
        status_panel->SetText(SC::STATUS_CALIBRATION_SUCCESS);
        unBindAll();
    }
}

// clang-format off
wxBEGIN_EVENT_TABLE(RoiPanel, BasePanelWithTouch)
    EVT_BUTTON(wxID_ANY,RoiPanel::OnButton) 
    EVT_COMMAND(wxID_ANY, c_CALIBRATION_EVENT, RoiPanel::OnCalibrationEvent)
wxEND_EVENT_TABLE()
