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

    title_panel = new TitlePanel(this, panel_id);

    status_panel = new StatusPanel(this, wxT(" Status"));

    main_sizer = new wxBoxSizer(wxVERTICAL);
    main_sizer->Add(title_panel, 0, wxEXPAND | wxTOP | wxLEFT | wxRIGHT, 10);
    main_sizer->Add(img_bitmap, 1, wxEXPAND | wxTOP | wxLEFT | wxRIGHT, 10);
    main_sizer->Add(status_panel, 0, wxEXPAND | wxTOP | wxLEFT | wxRIGHT, 10);
    main_sizer->Add(button_panel, 0, wxEXPAND | wxALL, 10);

    SetSizer(main_sizer);
    Fit();

    Hide();
}

CalibrationPanel::~CalibrationPanel() {}

void CalibrationPanel::OnButton(wxCommandEvent &e) {
    if (e.GetId() == Enum::CL_Back_Button_ID) {
        model->e_ChangePanel(button_panel->cancel_Button);
    }

    if (e.GetId() == Enum::CL_ToggleCamera_Button_ID) {
        ButtonWState *button = button_panel->camera_Button;
        model->e_ToggleCamera(button, button->GetState());
    }

    if (e.GetId() == Enum::CL_Start_Button_ID) {
        model->e_StartCalibration(button_panel->start_Button);
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
