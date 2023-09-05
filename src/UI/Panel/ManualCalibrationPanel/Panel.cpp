#include "Controller/ManualCalibrationController.hpp"
#include "Event/Event_Calibration.hpp"
#include "Event/Event_ChangePanel.hpp"
#include "Event/Event_UpdateStatus.hpp"

#include "Model/AppState.hpp"
#include "UI/Layout/StatusPanel.hpp"
#include "UI/Panel/Common/BasePanel.hpp"
#include "UI/Panel/ManualCalibrationPanel/Panel_Button.hpp"
#include "Utils/Enum.hpp"
#include <UI/Panel/ManualCalibrationPanel/Panel.hpp>
#include <stdexcept>
#include <wx/event.h>
#include <wx/gdicmn.h>
#include <wx/gtk/stattext.h>
#include <wx/sizer.h>

namespace SC = StatusCollection;

ManualCalibrationPanel::ManualCalibrationPanel(wxWindow *parent, wxWindowID id,
                                               MCCPtr controller)
    : BasePanelWithTouch(parent, id, controller), controller(controller) {

    button_panel =
        new ManualCalibrationPanelButton(this, Enum::MC_Button_Panel_ID);
    title_panel = new TitlePanel(this, panel_id);

    size();
}

ManualCalibrationPanel::~ManualCalibrationPanel() {}

void ManualCalibrationPanel::OnButton(wxCommandEvent &e) {

    ManualCalibrationPanelButton *button_panel =
        dynamic_cast<ManualCalibrationPanelButton *>(this->button_panel);

    if (e.GetId() == Enum::MC_CalibrationCamera_Button_ID) {
        auto button = button_panel->MainPanel->CalibrateCamera_Button;
        ToggleCalibrationButtonHandler(button);
    }
    if (e.GetId() == Enum::MC_CalibrationCapture_Button_ID) {
        auto button = button_panel->MainPanel->CalibrateCapture_Button;
        ToggleCalibrationCaptureButtonHandler(button);
    }

    if (e.GetId() == Enum::MC_SelectLeft_Button_ID) {
        controller->e_ChangeToLeft(this);
    }

    if (e.GetId() == Enum::MC_SelectRight_Button_ID) {
        controller->e_ChangeToRight(this);
    }

    if (e.GetId() == Enum::MC_RemoveLeft_Button_ID) {
        controller->e_ChangeToLeft(this);
        controller->e_RemoveLeft(this);
    }

    if (e.GetId() == Enum::MC_RemoveRight_Button_ID) {
        controller->e_ChangeToRight(this);
        controller->e_RemoveRight(this);
    }

    if (e.GetId() == Enum::MC_PreviewCamera_Button_ID) {
        auto button = button_panel->PreviewPanel->PreviewCamera_Button;
        TogglePreviewButtonHandler(button);
    }

    if (e.GetId() == Enum::MC_PreviewCapture_Button_ID) {
        auto button = button_panel->PreviewPanel->PreviewCapture_Button;
        TogglePreviewCaptureButtonHandler(button);
    }

    if (e.GetId() == Enum::MC_Remove_Button_ID) {
        controller->e_RemoveCalibData(this);
    }

    e.Skip();
}

void ManualCalibrationPanel::TogglePreviewButtonHandler(
    BitmapButtonT2 *button) {
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

void ManualCalibrationPanel::TogglePreviewCaptureButtonHandler(
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

void ManualCalibrationPanel::ToggleCalibrationButtonHandler(
    BitmapButtonT2 *button) {
    if (button->getState() == ButtonState::OFF) {
        controller->e_ManualCalibrationCameraStart(button);
        return;
    }

    if (button->getState() == ButtonState::ON) {
        controller->e_ManualCalibrationCameraEnd(button);
        return;
    }
    throw std::runtime_error("Invalid button state");
}

void ManualCalibrationPanel::ToggleCalibrationCaptureButtonHandler(
    BitmapButtonT2 *button) {
    if (button->getState() == ButtonState::OFF) {
        controller->e_ManualCalibrationCaptureStart(button);
        return;
    }

    if (button->getState() == ButtonState::ON) {
        controller->e_ManualCalibrationCaptureEnd(button);
        return;
    }
    throw std::runtime_error("Invalid button state");
}

void ManualCalibrationPanel::OnCalibrationEvent(wxCommandEvent &e) {
    if (e.GetId() == CALIBRATION_START) {
        status_panel->SetText(SC::STATUS_START_CALIBRATION);

        // Bind Left Down Event
        img_bitmap->Bind(wxEVT_LEFT_DOWN, &ManualCalibrationPanel::OnLeftDown,
                         this);
    }

    if (e.GetId() == CALIBRATION_END) {
        status_panel->SetText(SC::STATUS_CALIBRATION_SUCCESS);
    }
}

void ManualCalibrationPanel::OnCapture(wxCommandEvent &e) {
    if (e.GetId() == PREVIEW_START) {
        status_panel->SetText(SC::STATUS_CAMERA_ON);
    }

    if (e.GetId() == PREVIEW_END) {
        status_panel->SetText(SC::STATUS_CAMERA_OFF);
    }
}

// clang-format off
wxBEGIN_EVENT_TABLE(ManualCalibrationPanel, BasePanelWithTouch)
    EVT_BUTTON(wxID_ANY, ManualCalibrationPanel::OnButton)
    EVT_COMMAND(wxID_ANY, c_CALIBRATION_EVENT, ManualCalibrationPanel::OnCalibrationEvent)
    EVT_COMMAND(wxID_ANY, c_PREVIEW_CAMERA_EVENT, ManualCalibrationPanel::OnCapture)
wxEND_EVENT_TABLE()
