#include "Event/Event_Capture.hpp"
#include "Event/Event_ChangePanel.hpp"
#include "Event/Event_LoadImage.hpp"
#include "Event/Event_UpdateState.hpp"
#include "Event/Event_UpdateStatus.hpp"
#include "Model/AppState.hpp"
#include "Model/ModelEnum.hpp"
#include "UI/StaticText/Statustext.hpp"
#include "UI/StaticText/Titletext.hpp"
#include "Utils/Enum.hpp"
#include <UI/Panel/CapturePanel/Panel.hpp>
#include <iostream>
#include <stdexcept>
#include <wx/gdicmn.h>

CapturePanel::CapturePanel(wxWindow *parent, wxWindowID id,
                           std::unique_ptr<CaptureModel> &model)
    : wxPanel(parent, id), model(std::move(model)) {
    button_panel = new CaptureButtonPanel(this, Enum::CP_BUTTON_PANEL_ID);

    img_bitmap = new BaseImagePanel(this);

    title_panel = new TitlePanel(this, panel_id);

    status_panel = new StatusPanel(this, wxT("Status"));

    main_sizer = new wxBoxSizer(wxVERTICAL);
    main_sizer->Add(title_panel, 0, wxEXPAND | wxTOP | wxLEFT | wxRIGHT, 10);
    main_sizer->Add(img_bitmap, 0, wxEXPAND | wxTOP | wxLEFT | wxRIGHT, 10);
    main_sizer->Add(status_panel, 0, wxEXPAND | wxTOP | wxLEFT | wxRIGHT, 10);
    main_sizer->Add(button_panel, 1, wxEXPAND | wxALL, 10);

    SetSizer(main_sizer);
    Fit();
}

CapturePanel::~CapturePanel() {}

void CapturePanel::OnButton(wxCommandEvent &e) {
    if (e.GetId() == Enum::CP_ToggleCamera_Button_ID) {
        OnToggleCameraButton(button_panel->dPanel->ToggleCamera_Button);
    }

    if (e.GetId() == Enum::CP_Capture_Button_ID) {
        OnCaptureButton(button_panel->cPanel->Capture_Button->button);
    }

    if (e.GetId() == Enum::CP_Load_Button_ID) {
        //OnLoadButton(button_panel->cPanel->Load_Button->button);
    }

    if (e.GetId() == Enum::CP_Reset_Button_ID) {
        model->e_ClearImageData(this);
        model->e_UpdateState(this);
        UpdateStatusEvent::Submit(this, StatusCollection::STATUS_REMOVE_DATA);
    }

    if (e.GetId() == Enum::CP_Replay_Button_ID) {
        model->e_ReplayStart(this);
    }

    //TODO: Change panel
    if (e.GetId() == Enum::CP_SWITCH_Button_ID) {
        // OnChangePanelButton(button_panel->switch_Button);
    }

    //TODO: Calibrate panel
    if (e.GetId() == Enum::CP_CALIBRATE_Button_ID) {
        model->endPoint(button_panel->csPanel->calibrate_Button,
                        ModelEnum::MODEL_SWITCH_TO_CALIB);
    }

    e.Skip();
}

void CapturePanel::OnLoadButton(ButtonWState *button) {
    wxFileDialog openFileDialog(this, _("Open .bin file"), "", "",
                                "XYZ files (*.bin)|*.bin",
                                wxFD_OPEN | wxFD_FILE_MUST_EXIST);

    if (openFileDialog.ShowModal() == wxID_CANCEL) {
        return;
    }

    std::string path = Utils::wxStringToString(openFileDialog.GetPath());
    model->endPoint(button, ModelEnum::MODEL_START_LOADFILE, path);
}

void CapturePanel::OnCaptureButton(wxButton *button) {
    model->endPoint(button, ModelEnum::MODEL_START_LOADCAPTURE);
}

void CapturePanel::OnToggleCameraButton(ButtonWState *button) {
    if (!button->GetState()) {
        model->endPoint(button, ModelEnum::MODEL_START_CAPTURE);
        return;
    }

    model->endPoint(button, ModelEnum::MODEL_END_CAPTURE);
}

void CapturePanel::OnUpdatePreview(UpdatePreviewEvent &e) {
    if (e.GetId() == UPDATE_PREVIEW) {
        wxBitmap image = e.GetImage();
        img_bitmap->setImage(image);
    }

    if (e.GetId() == CLEAR_PREVIEW) {
        img_bitmap->setNoImage();
    }
}

void CapturePanel::OnChangePanelButton(wxButton *button) {
    model->endPoint(button, ModelEnum::MODEL_SWITCH_PANEL);
}

void CapturePanel::OnLoadImage(wxCommandEvent &e) {
    if (e.GetId() == LOAD_START_CAMERA) {
        UpdateStatusEvent::Submit(this, StatusCollection::STATUS_CAPTURE_START);
    }
    if (e.GetId() == LOAD_END_FILE) {
        model->endPoint(button_panel->cPanel->Load_Button,
                        ModelEnum::MODEL_END_LOADFILE);
    }

    if (e.GetId() == LOAD_END_CAMERA) {
        model->endPoint(this, ModelEnum::MODEL_END_LOADCAPTURE);
        UpdateStatusEvent::Submit(this, StatusCollection::STATUS_CAPTURE_END);
    }

    model->e_UpdateState(this);

    e.Skip();
}

void CapturePanel::OnUpdateState(UpdateStateEvent &e) {
    auto state = e.GetState();
    button_panel->cPanel->update(state);
    Refresh();
}

void CapturePanel::OnUpdateStatus(UpdateStatusEvent &e) {
    auto status = e.GetStatus();
    status_panel->SetText(status);
    Refresh();
}

void CapturePanel::OnReplay(wxCommandEvent &e) {
    if (e.GetId() == REPLAY_START) {
        UpdateStatusEvent::Submit(this, StatusCollection::STATUS_REPLAY_START);
    }

    if (e.GetId() == REPLAY_END) {
        model->e_ReplayEnd(this);
        UpdateStatusEvent::Submit(this, StatusCollection::STATUS_REPLAY_END);
    }

    model->e_UpdateState(this);
    e.Skip();
}

// clang-format off
wxBEGIN_EVENT_TABLE(CapturePanel, wxPanel)
    EVT_UPDATE_PREVIEW(wxID_ANY, CapturePanel::OnUpdatePreview)
    EVT_BUTTON(wxID_ANY,CapturePanel::OnButton) 
    EVT_COMMAND(wxID_ANY, c_LOAD_IMAGE_EVENT, CapturePanel::OnLoadImage)
    EVT_UPDATE_STATE(wxID_ANY, CapturePanel::OnUpdateState)
    EVT_UPDATE_STATUS(wxID_ANY, CapturePanel::OnUpdateStatus)
    EVT_COMMAND(wxID_ANY, c_REPLAY_EVENT, CapturePanel::OnReplay)
wxEND_EVENT_TABLE()
