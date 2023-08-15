#include "Controller/ManualCalibrationController.hpp"
#include "Controller/ResultController.hpp"
#include "Event/Event_Calibration.hpp"
#include "Event/Event_ChangePanel.hpp"
#include "Event/Event_ProcessImage.hpp"
#include "Event/Event_UpdateStatus.hpp"

#include "Model/AppState.hpp"
#include "UI/Layout/StatusPanel.hpp"
#include "UI/Panel/ResultPanel/Panel_Button.hpp"
#include "Utils/Enum.hpp"
#include <UI/Panel/ResultPanel/Panel.hpp>
#include <stdexcept>
#include <utility>
#include <wx/event.h>
#include <wx/gdicmn.h>
#include <wx/gtk/stattext.h>
#include <wx/sizer.h>

namespace SC = StatusCollection;

ResultPanel::ResultPanel(wxWindow *parent, wxWindowID id, RSCPtr &controller)
    : wxPanel(parent, id), controller(std::move(controller)) {

    button_panel = new ResultPanelButton(this, Enum::CP_BUTTON_PANEL_ID);

    img_bitmap = new BaseImagePanel(this);

    title_panel = new TitlePanel(this, panel_id);

    status_panel = new StatusPanel(this, SC::STATUS_IDLE);

    main_sizer = new wxBoxSizer(wxVERTICAL);
    main_sizer->Add(title_panel, 0, wxEXPAND | wxTOP | wxLEFT | wxRIGHT, 10);
    main_sizer->Add(img_bitmap, 0, wxEXPAND | wxTOP | wxLEFT | wxRIGHT, 10);
    main_sizer->Add(status_panel, 0, wxEXPAND | wxTOP | wxLEFT | wxRIGHT, 10);
    main_sizer->Add(button_panel, 1, wxEXPAND | wxALL, 10);

    SetSizer(main_sizer);
    Fit();

    Hide();
}

ResultPanel::~ResultPanel() {}

void ResultPanel::OnButton(wxCommandEvent &e) {
    if (e.GetId() == Enum::G_Cancel_Button_ID) {
        // controller->e_RestoreSessionData(this);
        controller->e_ChangeToCapturePanel(this);
    }

    if (e.GetId() == Enum::G_OK_Button_ID) {
        // controller->e_SaveSessionData(this);
        controller->e_ChangeToCapturePanel(this);
    }

    if (e.GetId() == Enum::RE_Start_Button_ID) {
        controller->e_ProcessThreadStart(this);
    }

    if (e.GetId() == Enum::RE_Stop_Button_ID) {
        controller->e_ProcessThreadEnd(this);
    }

    if (e.GetId() == Enum::RE_Preview_Button_ID) {
        auto button = button_panel->main_status_panel->camera_Button;
        ToggleReplayButtonHandler(button);
    }

    if (e.GetId() == Enum::RE_Box_Button_ID) {
        auto button = button_panel->preview_status_panel->box_Button;
        ToggleBoxButtonHandler(button);
    }

    if (e.GetId() == Enum::RE_Lines_Button_ID) {
        auto button = button_panel->preview_status_panel->intersection_Button;
        ToggleLinesButtonHandler(button);
    }

    if (e.GetId() == Enum::RE_Lanes_Button_ID) {
        auto button = button_panel->preview_status_panel->lanes_Button;
        ToggleLanesButtonHandler(button);
    }

    if (e.GetId() == Enum::RE_Replay_Button_ID) {
        controller->e_SetIndexToZero(this);
    }

    controller->e_UpdateState(this);

    e.Skip();
}

void ResultPanel::ToggleReplayButtonHandler(BitmapButtonT2 *button) {
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

void ResultPanel::OnUpdatePreview(UpdatePreviewEvent &e) {
    if (e.GetId() == UPDATE_PREVIEW) {
        wxBitmap image = e.GetImage();
        img_bitmap->setImage(image);
    }

    if (e.GetId() == CLEAR_PREVIEW) {
        img_bitmap->setNoImage();
    }
}

void ResultPanel::OnUpdateStatus(UpdateStatusEvent &e) {
    if (e.GetId() == UPDATE_STATUS) {
        wxString status = e.GetStatus();
        status_panel->SetText(status);
    }
}

void ResultPanel::OnUpdateState(UpdateStateEvent &e) {
    try {
        auto state = e.GetState();

        button_panel->main_status_panel->update(state);
        button_panel->preview_status_panel->update(state);

        Refresh();
    } catch (const std::exception &e) {
        ErrorEvent::Submit(this, e.what());
    }
}

void ResultPanel::OnShow(wxShowEvent &e) {
    if (e.IsShown()) {
        // controller->e_CreateTempSessionData(this);
        controller->e_UpdateState(this);
    }
}

void ResultPanel::OnProcessImage(wxCommandEvent &e) {
    if (e.GetId() == PROCESS_END) {
        controller->e_ProcessThreadEnd(this);
    }

    controller->e_UpdateState(this);
}

// clang-format off
wxBEGIN_EVENT_TABLE(ResultPanel, wxPanel)
    EVT_UPDATE_PREVIEW(wxID_ANY, ResultPanel::OnUpdatePreview)
    EVT_UPDATE_STATUS(wxID_ANY, ResultPanel::OnUpdateStatus)
    EVT_UPDATE_STATE(wxID_ANY, ResultPanel::OnUpdateState)
    EVT_BUTTON(wxID_ANY,ResultPanel::OnButton) 
    EVT_COMMAND(wxID_ANY, c_PROCESS_IMAGE_EVENT, ResultPanel::OnProcessImage)
    EVT_SHOW(ResultPanel::OnShow)
wxEND_EVENT_TABLE()
