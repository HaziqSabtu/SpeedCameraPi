#include "Controller/ManualCalibrationController.hpp"
#include "Controller/ResultController.hpp"
#include "Event/Event_Calibration.hpp"
#include "Event/Event_ChangePanel.hpp"
#include "Event/Event_ProcessImage.hpp"
#include "Event/Event_UpdateStatus.hpp"

#include "Model/AppState.hpp"
#include "UI/Layout/StatusPanel.hpp"
#include "UI/Panel/Common/BasePanel.hpp"
#include "UI/Panel/ResultPanel/Panel_Button.hpp"
#include "Utils/Enum.hpp"
#include <UI/Panel/ResultPanel/Panel.hpp>
#include <stdexcept>
#include <utility>
#include <wx/event.h>
#include <wx/gdicmn.h>
#include <wx/gtk/stattext.h>
#include <wx/sizer.h>

ResultPanel::ResultPanel(wxWindow *parent, wxWindowID id, RSCPtr controller)
    : BasePanel(parent, id, controller), controller(controller) {

    button_panel = new ResultPanelButton(this, Enum::RE_Button_Panel_ID);

    title_panel = new TitlePanel(this, panel_id);

    size();
}

ResultPanel::~ResultPanel() {}

void ResultPanel::OnButton(wxCommandEvent &e) {

    ResultPanelButton *button_panel =
        dynamic_cast<ResultPanelButton *>(this->button_panel);

    if (e.GetId() == Enum::RE_Start_Button_ID) {
        controller->e_ProcessThreadStart(this);
    }

    if (e.GetId() == Enum::RE_Redundant_Button_ID) {
        controller->e_ProcessRedundantThreadStart(this);
    }

    if (e.GetId() == Enum::RE_Preview_Button_ID) {
        auto button = button_panel->MainPanel->Preview_Button;
        TogglePreviewButtonHandler(button);
    }

    if (e.GetId() == Enum::RE_Box_Button_ID) {
        auto button = button_panel->PreviewPanel->Box_Button;
        ToggleBoxButtonHandler(button);
    }

    if (e.GetId() == Enum::RE_Lines_Button_ID) {
        auto button = button_panel->PreviewPanel->Intersection_Button;
        ToggleLinesButtonHandler(button);
    }

    if (e.GetId() == Enum::RE_Lanes_Button_ID) {
        auto button = button_panel->PreviewPanel->Lanes_Button;
        ToggleLanesButtonHandler(button);
    }

    if (e.GetId() == Enum::RE_Replay_Button_ID) {
        controller->e_SetIndexToZero(this);
    }

    e.Skip();
}

void ResultPanel::TogglePreviewButtonHandler(BitmapButtonT2 *button) {
    if (button->getState() == ButtonState::OFF) {
        controller->e_ResultPreviewStart(button);
        return;
    }

    if (button->getState() == ButtonState::ON) {
        controller->e_ResultPreviewEnd(button);
        return;
    }
    throw std::runtime_error("Invalid button state");
}

void ResultPanel::ToggleBoxButtonHandler(BitmapButtonT2 *button) {
    if (button->getState() == ButtonState::OFF) {
        controller->e_ToggleShowBox(button, true);
        return;
    }

    if (button->getState() == ButtonState::ON) {
        controller->e_ToggleShowBox(button, false);
        return;
    }
    throw std::runtime_error("Invalid button state");
}

void ResultPanel::ToggleLinesButtonHandler(BitmapButtonT2 *button) {
    if (button->getState() == ButtonState::OFF) {
        controller->e_ToggleShowLines(button, true);
        return;
    }

    if (button->getState() == ButtonState::ON) {
        controller->e_ToggleShowLines(button, false);
        return;
    }
    throw std::runtime_error("Invalid button state");
}

void ResultPanel::ToggleLanesButtonHandler(BitmapButtonT2 *button) {
    if (button->getState() == ButtonState::OFF) {
        controller->e_ToggleShowLanes(button, true);
        return;
    }

    if (button->getState() == ButtonState::ON) {
        controller->e_ToggleShowLanes(button, false);
        return;
    }
    throw std::runtime_error("Invalid button state");
}

void ResultPanel::OnProcessImage(wxCommandEvent &e) {
    if (e.GetId() == PROCESS_END) {
        controller->e_ProcessEnd(this);
    }

    controller->e_UpdateState(this);
}

// clang-format off
wxBEGIN_EVENT_TABLE(ResultPanel, BasePanel)
    EVT_BUTTON(wxID_ANY,ResultPanel::OnButton) 
    EVT_COMMAND(wxID_ANY, c_PROCESS_IMAGE_EVENT, ResultPanel::OnProcessImage)
wxEND_EVENT_TABLE()
