#include "UI/Panel/ColorCalibrationPanel/Panel.hpp"
#include "Controller/BaseController.hpp"
#include "Controller/ColorCalibrationController.hpp"
#include "Event/Event_Calibration.hpp"
#include "Event/Event_ChangePanel.hpp"
#include "Event/Event_UpdateState.hpp"
#include "Event/Event_UpdateStatus.hpp"

#include "UI/Layout/StatusPanel.hpp"
#include "UI/Panel/ColorCalibrationPanel/Panel_Button.hpp"
#include "UI/Panel/Common/BasePanel.hpp"
#include "Utils/Enum.hpp"
#include <UI/Panel/ColorCalibrationPanel/Panel.hpp>
#include <stdexcept>
#include <wx/gtk/stattext.h>
#include <wx/sizer.h>

/**
 * @brief Construct a new Color Calibration Panel:: Color Calibration Panel
 * object
 *
 * @param parent Pointer to the parent window
 * @param id ID of the panel
 * @param controller Pointer to the ColorCalibrationController
 */
ColorCalibrationPanel::ColorCalibrationPanel(wxWindow *parent, wxWindowID id,
                                             CCCPtr controller)
    : BasePanelWithTouch(parent, id, controller), controller(controller) {

    button_panel =
        new ColorCalibrationPanelButton(this, Enum::CC_Button_Panel_ID);

    title_panel = new TitlePanel(this, panel_id);

    size();
}

/**
 * @brief Destroy the Color Calibration Panel:: Color Calibration Panel object
 *
 */
ColorCalibrationPanel::~ColorCalibrationPanel() {}

/**
 * @brief Handle button events
 *
 */
void ColorCalibrationPanel::OnButton(wxCommandEvent &e) {

    ColorCalibrationPanelButton *button_panel =
        dynamic_cast<ColorCalibrationPanelButton *>(this->button_panel);

    if (e.GetId() == Enum::CC_ToggleCamera_Button_ID) {
        auto button = button_panel->MainPanel->Preview_Button;
        ToggleCameraButtonHandler(button);
    }

    if (e.GetId() == Enum::CC_Start_Button_ID) {
        auto button = button_panel->MainPanel->Calibrate_Button;
        ToggleCalibrationButtonHandler(button);
    }

    if (e.GetId() == Enum::CC_Stop_Button_ID) {
        controller->e_ColorCalibrationEnd(this);
    }

    if (e.GetId() == Enum::CC_SelectBlue_Button_ID) {
        controller->e_SetTypeBlue(this);
    }

    if (e.GetId() == Enum::CC_AcceptBlue_Button_ID) {
        controller->e_RemoveBlue(this);
    }

    if (e.GetId() == Enum::CC_SelectYellow_Button_ID) {
        controller->e_SetTypeYellow(this);
    }

    if (e.GetId() == Enum::CC_AcceptYellow_Button_ID) {
        controller->e_RemoveYellow(this);
    }

    if (e.GetId() == Enum::CC_Restore_Button_ID) {
        controller->e_RestoreRange(this);
    }

    e.Skip();
}

/**
 * @brief Handle toggle camera button
 *
 * @param button Pointer to the button
 */
void ColorCalibrationPanel::ToggleCameraButtonHandler(BitmapButtonT2 *button) {
    if (button->getState() == ButtonState::OFF) {
        controller->e_ColorCalibrationPreviewStart(button);
        return;
    }

    if (button->getState() == ButtonState::ON) {
        controller->e_ColorCalibrationPreviewEnd(button);
        return;
    }
    throw std::runtime_error("Invalid button state");
}

/**
 * @brief Handle toggle calibration button
 *
 * @param button Pointer to the button
 */
void ColorCalibrationPanel::ToggleCalibrationButtonHandler(
    BitmapButtonT2 *button) {
    if (button->getState() == ButtonState::OFF) {
        controller->e_ColorCalibrationStart(button);
        return;
    }

    if (button->getState() == ButtonState::ON) {
        controller->e_ColorCalibrationEnd(button);
        return;
    }
    throw std::runtime_error("Invalid button state");
}

/**
 * @brief Handle calibration events
 *
 * @param e Event
 */
void ColorCalibrationPanel::OnCalibrationEvent(wxCommandEvent &e) {
    if (e.GetId() == CALIBRATION_CAMERA_START) {
        status_panel->SetText(SC::STATUS_START_CALIBRATION);

        bindLeftDown();
    }

    if (e.GetId() == CALIBRATION_CAMERA_END) {
        status_panel->SetText(SC::STATUS_CALIBRATION_END);

        unBindAll();
    }

    controller->e_UpdateState(this);
}

/**
 * @brief Handle left down events (override)
 *
 */
void ColorCalibrationPanel::doPostLeftDown() {
    // do nothing
}

// clang-format off
wxBEGIN_EVENT_TABLE(ColorCalibrationPanel, BasePanelWithTouch)  
    EVT_BUTTON(wxID_ANY,ColorCalibrationPanel::OnButton) 
    EVT_COMMAND(wxID_ANY, c_CALIBRATION_EVENT, ColorCalibrationPanel::OnCalibrationEvent)
wxEND_EVENT_TABLE()
