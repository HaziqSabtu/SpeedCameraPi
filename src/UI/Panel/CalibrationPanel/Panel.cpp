#include "Event/Event_ChangePanel.hpp"
#include "Model/ModelEnum.hpp"
#include "UI/Button/Button_wState.hpp"
#include "UI/Panel/CalibrationPanel/Panel_Button.hpp"
#include "Utils/Enum.hpp"
#include <UI/Panel/CalibrationPanel/Panel.hpp>
#include <stdexcept>

CalibrationPanel::CalibrationPanel(wxWindow *parent, wxWindowID id,
                                   std::unique_ptr<CalibrationModel> &model)
    : wxPanel(parent, id), model(std::move(model)) {
    button_panel = new CalibrationPanelButton(this, Enum::CP_BUTTON_PANEL_ID);

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

    Hide();
}

CalibrationPanel::~CalibrationPanel() {}

void CalibrationPanel::OnButton(wxCommandEvent &e) {
    if (e.GetId() == Enum::CP_SWITCH_Button_ID) {
        model->e_ChangePanel(button_panel->switch_Button);
    }

    if (e.GetId() == Enum::CL_Start_Button_ID) {
        ButtonWState *button = button_panel->start_Button;
        model->e_ToggleCamera(button, button->GetState());
    }

    e.Skip();
}

void CalibrationPanel::OnUpdatePreview(UpdatePreviewEvent &e) {
    if (e.GetId() == UPDATE_PREVIEW) {
        wxBitmap image = e.GetImage();
        img_bitmap->setImage(image);
    }

    if (e.GetId() == CLEAR_PREVIEW) {
        img_bitmap->setNoImage();
    }
}

// clang-format off
wxBEGIN_EVENT_TABLE(CalibrationPanel, wxPanel)
    EVT_UPDATE_PREVIEW(wxID_ANY, CalibrationPanel::OnUpdatePreview)
    EVT_BUTTON(wxID_ANY,CalibrationPanel::OnButton) 
wxEND_EVENT_TABLE()
