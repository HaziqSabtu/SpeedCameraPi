#include "Event/Event_ChangePanel.hpp"
#include "Model/ModelEnum.hpp"
#include "UI/StaticText/Statustext.hpp"
#include "UI/StaticText/Titletext.hpp"
#include "Utils/Enum.hpp"
#include <UI/Panel/CapturePanel/Panel.hpp>
#include <stdexcept>
#include <wx/gdicmn.h>

CapturePanel::CapturePanel(wxWindow *parent, wxWindowID id,
                           std::unique_ptr<CaptureModel> &model)
    : wxPanel(parent, id), model(std::move(model)) {
    button_panel = new CaptureButtonPanel(this, Enum::CP_BUTTON_PANEL_ID);

    img_bitmap = new BaseImagePanel(this);

    titleText = new TitleText(this, wxID_ANY, this->panel_id);

    statusText = new StatusText(this, wxID_ANY, wxT("  IDLE"));

    exit_Button = new ButtonExit(this);

    title_Sizer = new wxBoxSizer(wxHORIZONTAL);
    title_Sizer->Add(titleText->sizer, 1, wxEXPAND);
    title_Sizer->Add(exit_Button, 0, wxEXPAND);

    main_sizer = new wxBoxSizer(wxVERTICAL);
    main_sizer->Add(title_Sizer, 0, wxEXPAND | wxTOP | wxLEFT | wxRIGHT, 10);
    main_sizer->Add(img_bitmap, 1, wxEXPAND | wxTOP | wxLEFT | wxRIGHT, 10);
    main_sizer->Add(statusText, 0, wxEXPAND | wxTOP | wxLEFT | wxRIGHT, 10);
    main_sizer->Add(button_panel, 0, wxEXPAND | wxALL, 10);

    SetSizer(main_sizer);
    Fit();
}

CapturePanel::~CapturePanel() {}

void CapturePanel::OnButton(wxCommandEvent &e) {
    if (e.GetId() == Enum::CP_ToggleCamera_Button_ID) {
        OnToggleCameraButton(button_panel->ToggleCamera_Button);
    }

    if (e.GetId() == Enum::CP_Capture_Button_ID) {
        OnCaptureButton(button_panel->Capture_Button);
    }

    if (e.GetId() == Enum::CP_Load_Button_ID) {
        OnLoadButton(button_panel->Load_Button);
    }

    if (e.GetId() == Enum::CP_SWITCH_Button_ID) {
        OnChangePanelButton(button_panel->switch_Button);
    }

    if (e.GetId() == Enum::CP_CALIBRATE_Button_ID) {
        model->endPoint(button_panel->calibrate_Button,
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

void CapturePanel::OnCaptureButton(ButtonWState *button) {
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
    if (e.GetId() == LOAD_END_FILE) {
        model->endPoint(button_panel->Load_Button,
                        ModelEnum::MODEL_END_LOADFILE);
    }

    if (e.GetId() == LOAD_END_CAMERA) {
        model->endPoint(button_panel->Capture_Button,
                        ModelEnum::MODEL_END_LOADCAPTURE);
    }
    e.Skip();
}

// clang-format off
wxBEGIN_EVENT_TABLE(CapturePanel, wxPanel)
    EVT_UPDATE_PREVIEW(wxID_ANY, CapturePanel::OnUpdatePreview)
    EVT_BUTTON(wxID_ANY,CapturePanel::OnButton) 
    EVT_COMMAND(wxID_ANY, c_LOAD_IMAGE_EVENT, CapturePanel::OnLoadImage)
wxEND_EVENT_TABLE()
