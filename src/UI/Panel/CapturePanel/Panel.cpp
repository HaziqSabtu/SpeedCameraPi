#include <UI/Panel/CapturePanel/Panel.hpp>

CapturePanel::CapturePanel(wxWindow *parent, wxWindowID id, Model *model)
    : wxPanel(parent, id), model(model) {
    button_panel = new CaptureButtonPanel(this, Enum::CP_BUTTON_PANEL_ID);

    img_bitmap = new BaseImagePanel(this);

    main_sizer = new wxBoxSizer(wxVERTICAL);
    main_sizer->Add(button_panel, 0, wxEXPAND);
    main_sizer->Add(img_bitmap, 1, wxEXPAND);

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
    if (button->GetState()) {
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

void CapturePanel::onLoadImage(wxCommandEvent &e) {
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

void CapturePanel::OnError(ErrorEvent &e) {
    std::string msg = e.GetErrorData();
    wxMessageBox(msg, "Error", wxOK | wxICON_ERROR);
    Close();
}

// clang-format off
wxBEGIN_EVENT_TABLE(CapturePanel, wxPanel)
    EVT_UPDATE_PREVIEW(wxID_ANY, CapturePanel::OnUpdatePreview)
    EVT_BUTTON(wxID_ANY,CapturePanel::OnButton) 
    EVT_COMMAND(wxID_ANY, c_LOAD_IMAGE_EVENT, CapturePanel::onLoadImage)
    EVT_ERROR(wxID_ANY, CapturePanel::OnError)
wxEND_EVENT_TABLE()
