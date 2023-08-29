#include "Controller/ManualCalibrationController.hpp"
#include "Controller/TrimDataController.hpp"
#include "Event/Event_Calibration.hpp"
#include "Event/Event_ChangePanel.hpp"
#include "Event/Event_Replay.hpp"
#include "Event/Event_RequestUpdateState.hpp"
#include "Event/Event_UpdateStatus.hpp"

#include "Model/AppState.hpp"
#include "UI/Layout/StatusPanel.hpp"
#include "Utils/Enum.hpp"
#include <UI/Panel/TrimDataPanel/Panel.hpp>
#include <stdexcept>
#include <wx/event.h>
#include <wx/gdicmn.h>
#include <wx/gtk/stattext.h>
#include <wx/sizer.h>

namespace SC = StatusCollection;

TrimDataPanel::TrimDataPanel(wxWindow *parent, wxWindowID id, TDCPtr controller)
    : BasePanel(parent, id, controller), controller(controller) {

    button_panel = new TrimDataPanelButton(this, Enum::CP_BUTTON_PANEL_ID);
    title_panel = new TitlePanel(this, panel_id);

    size();
}

TrimDataPanel::~TrimDataPanel() {}

void TrimDataPanel::OnButton(wxCommandEvent &e) {

    TrimDataPanelButton *button_panel =
        dynamic_cast<TrimDataPanelButton *>(this->button_panel);

    if (e.GetId() == Enum::TD_Start_Button_ID) {
        auto button = button_panel->main_status_panel->start_Button;
        ToggleTrimDataButtonHandler(button);
    }

    if (e.GetId() == Enum::TD_Preview_Button_ID) {
        controller->e_ReplayStart(this);
    }

    if (e.GetId() == Enum::TD_Reset_Button_ID) {
        controller->e_RestoreDefault(this);
    }

    if (e.GetId() == Enum::TD_IncrementStart_Button_ID) {
        controller->e_IncrementStartPos(this);
    }

    if (e.GetId() == Enum::TD_DecrementStart_Button_ID) {
        controller->e_DecrementStartPos(this);
    }

    if (e.GetId() == Enum::TD_IncrementEnd_Button_ID) {
        controller->e_IncrementEndPos(this);
    }

    if (e.GetId() == Enum::TD_DecrementEnd_Button_ID) {
        controller->e_DecrementEndPos(this);
    }

    if (e.GetId() == Enum::TD_Range_Button_ID) {
        controller->e_PreviewCurrentRange(this);
    }

    e.Skip();
}

void TrimDataPanel::ToggleTrimDataButtonHandler(BitmapButtonT2 *button) {
    if (button->getState() == ButtonState::OFF) {
        controller->e_TrimDataStart(button);
        return;
    }

    if (button->getState() == ButtonState::ON) {
        controller->e_TrimDataEnd(button);
        return;
    }
    throw std::runtime_error("Invalid button state");
}

void TrimDataPanel::OnReplay(wxCommandEvent &e) {
    if (e.GetId() == REPLAY_END) {
        controller->e_ReplayEnd(this);
    }
}

// clang-format off
wxBEGIN_EVENT_TABLE(TrimDataPanel, BasePanel)
    EVT_COMMAND(wxID_ANY, c_REPLAY_EVENT, TrimDataPanel::OnReplay)
    EVT_BUTTON(wxID_ANY,TrimDataPanel::OnButton) 
wxEND_EVENT_TABLE()