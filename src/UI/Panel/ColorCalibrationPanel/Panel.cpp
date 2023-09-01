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

namespace SC = StatusCollection;

ColorCalibrationPanel::ColorCalibrationPanel(wxWindow *parent, wxWindowID id,
                                             CCCPtr controller)
    : BasePanelWithTouch(parent, id, controller), controller(controller) {

    button_panel =
        new ColorCalibrationPanelButton(this, Enum::CC_Button_Panel_ID);

    title_panel = new TitlePanel(this, panel_id);

    size();
}

ColorCalibrationPanel::~ColorCalibrationPanel() {}

void ColorCalibrationPanel::OnButton(wxCommandEvent &e) {

    ColorCalibrationPanelButton *button_panel =
        dynamic_cast<ColorCalibrationPanelButton *>(this->button_panel);

    if (e.GetId() == Enum::CC_ToggleCamera_Button_ID) {
        auto button = button_panel->MainPanel->Preview_Button;
        ToggleCameraButtonHandler(button);
    }

    if (e.GetId() == Enum::CC_Start_Button_ID) {
        controller->e_ColorCalibrationStart(this);
    }

    if (e.GetId() == Enum::CC_Stop_Button_ID) {
        controller->e_ColorCalibrationEnd(this);
    }

    if (e.GetId() == Enum::CC_Remove_Button_ID) {
        controller->e_RemoveCalibratedRange(this);
    }

    if (e.GetId() == Enum::CC_SelectBlue_Button_ID) {
        controller->e_SetTypeBlue(this);
    }

    if (e.GetId() == Enum::CC_AcceptBlue_Button_ID) {
        controller->e_SaveBlue(this);
    }

    if (e.GetId() == Enum::CC_SelectYellow_Button_ID) {
        controller->e_SetTypeYellow(this);
    }

    if (e.GetId() == Enum::CC_AcceptYellow_Button_ID) {
        controller->e_SaveYellow(this);
    }

    if (e.GetId() == Enum::CC_Save_Button_ID) {
        controller->e_SaveToConfig(this);
    }

    if (e.GetId() == Enum::CC_Restore_Button_ID) {
        controller->e_RestoreRange(this);
    }

    e.Skip();
}

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

void ColorCalibrationPanel::OnCalibrationEvent(wxCommandEvent &e) {
    if (e.GetId() == CALIBRATION_START) {
        status_panel->SetText(SC::STATUS_START_CALIBRATION);

        bindLeftDown();
    }

    if (e.GetId() == CALIBRATION_END) {
        status_panel->SetText(SC::STATUS_CALIBRATION_END);

        unBindAll();
    }

    controller->e_UpdateState(this);
}

void ColorCalibrationPanel::doPostLeftDown() {
    // do nothing
    //  unBindAll();
}

// clang-format off
wxBEGIN_EVENT_TABLE(ColorCalibrationPanel, BasePanelWithTouch)  
    EVT_BUTTON(wxID_ANY,ColorCalibrationPanel::OnButton) 
    EVT_COMMAND(wxID_ANY, c_CALIBRATION_EVENT, ColorCalibrationPanel::OnCalibrationEvent)
wxEND_EVENT_TABLE()
