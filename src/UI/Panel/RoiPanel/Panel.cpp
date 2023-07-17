#include "Model/RoiModel.hpp"
#include "Model/SessionData.hpp"
#include <UI/Panel/RoiPanel/Panel.hpp>
#include <memory>

RoiPanel::RoiPanel(wxWindow *parent, wxWindowID id,
                   std::unique_ptr<RoiModel> &model)
    : wxPanel(parent, id), model(std::move(model)) {
    button_panel = new RoiButtonPanel(this, Enum::CP_BUTTON_PANEL_ID);

    img_bitmap = new RoiImagePanel(this);
    img_bitmap->Bind(wxEVT_LEFT_DOWN, &RoiPanel::OnLeftDown, this);
    img_bitmap->Bind(wxEVT_MOTION, &RoiPanel::OnMotion, this);
    img_bitmap->Bind(wxEVT_LEFT_UP, &RoiPanel::OnLeftUp, this);

    main_sizer = new wxBoxSizer(wxVERTICAL);
    main_sizer->Add(button_panel, 0, wxEXPAND);
    main_sizer->Add(img_bitmap, 1, wxEXPAND);

    SetSizer(main_sizer);
    Fit();

    Hide();

    Bind(wxEVT_LEFT_UP, &RoiPanel::OnLeftUp, this);
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

void RoiPanel::OnLeftDown(wxMouseEvent &e) {
    img_bitmap->p1 = e.GetPosition();
    img_bitmap->isDown = true;
}

void RoiPanel::OnLeftUp(wxMouseEvent &e) {

    if (!img_bitmap->isDown) {
        return;
    }

    img_bitmap->isDown = false;

    img_bitmap->p2 = e.GetPosition();

    img_bitmap->rect = img_bitmap->getRect(img_bitmap->p1, img_bitmap->p2);

    Refresh();

    model->endPoint(this, PANEL_ROI, img_bitmap->rect);
}

void RoiPanel::OnMotion(wxMouseEvent &e) {

    if (!img_bitmap->isDown) {
        return;
    }

    img_bitmap->p2 = e.GetPosition();

    img_bitmap->rect = img_bitmap->getRect(img_bitmap->p1, img_bitmap->p2);

    Refresh();
}

void RoiPanel::Init() { model->endPoint(this, ModelEnum::MODEL_START_PROCESS); }

// clang-format off
wxBEGIN_EVENT_TABLE(RoiPanel, wxPanel)
    EVT_UPDATE_PREVIEW(wxID_ANY, RoiPanel::OnUpdatePreview)
    EVT_BUTTON(wxID_ANY,RoiPanel::OnButton) 
    EVT_ERROR(wxID_ANY, RoiPanel::OnError)
wxEND_EVENT_TABLE()
