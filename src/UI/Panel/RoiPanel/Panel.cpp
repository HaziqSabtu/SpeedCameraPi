#include <UI/Panel/RoiPanel/Panel.hpp>

RoiPanel::RoiPanel(wxWindow *parent, wxWindowID id, Model *model)
    : wxPanel(parent, id), model(model) {
    button_panel = new RoiButtonPanel(this, Enum::CP_BUTTON_PANEL_ID);

    img_bitmap = new RoiImagePanel(this);

    main_sizer = new wxBoxSizer(wxVERTICAL);
    main_sizer->Add(button_panel, 0, wxEXPAND);
    main_sizer->Add(img_bitmap, 1, wxEXPAND);

    SetSizer(main_sizer);
    Fit();
}

RoiPanel::~RoiPanel() {}

void RoiPanel::OnButton(wxCommandEvent &e) { e.Skip(); }

void RoiPanel::OnUpdatePreview(UpdatePreviewEvent &e) {
    if (e.GetId() == UPDATE_PREVIEW) {
        wxBitmap image = e.GetImage();
        img_bitmap->setImage(image);
    }

    if (e.GetId() == CLEAR_PREVIEW) {
        img_bitmap->setNoImage();
    }
}

void RoiPanel::OnError(ErrorEvent &e) {
    std::string msg = e.GetErrorData();
    wxMessageBox(msg, "Error", wxOK | wxICON_ERROR);
    Close();
}

// clang-format off
wxBEGIN_EVENT_TABLE(RoiPanel, wxPanel)
    EVT_UPDATE_PREVIEW(wxID_ANY, RoiPanel::OnUpdatePreview)
    EVT_BUTTON(wxID_ANY,RoiPanel::OnButton) 
    EVT_ERROR(wxID_ANY, RoiPanel::OnError)
wxEND_EVENT_TABLE()
