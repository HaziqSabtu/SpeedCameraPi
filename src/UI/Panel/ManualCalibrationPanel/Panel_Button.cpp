
#include "UI/Panel/Common/BasePanel.hpp"
#include "UI/Panel/Common/Spacer.hpp"
#include "Utils/Enum.hpp"
#include <UI/Panel/ManualCalibrationPanel/Panel_Button.hpp>
#include <wx/stringimpl.h>

ManualCalibrationPanelButton::ManualCalibrationPanelButton(wxWindow *parent,
                                                           wxWindowID id)
    : BaseButtonPanel(parent, id) {

    spacer = new Spacer(this);

    main_status_panel = new ManualCalibrationMainStatusPanel(this);

    left_status_panel = new LeftStatusPanel(this);
    right_status_panel = new RightStatusPanel(this);

    lrSizer = new wxBoxSizer(wxHORIZONTAL);
    lrSizer->Add(left_status_panel, 1, wxEXPAND | wxBOTTOM | wxRIGHT, 10);
    lrSizer->Add(right_status_panel, 1, wxEXPAND | wxBOTTOM, 10);

    preview_panel = new ManualCalibrationPreviewPanel(this);

    ok_cancel_panel = new OKCancelPanel(this);

    button_sizer = new wxBoxSizer(wxVERTICAL);
    button_sizer->Add(main_status_panel, 0, wxEXPAND | wxBOTTOM, 10);
    button_sizer->Add(lrSizer, 0, wxEXPAND | wxBOTTOM, 10);
    button_sizer->Add(preview_panel, 0, wxEXPAND | wxBOTTOM, 10);
    button_sizer->Add(spacer, 1, wxEXPAND);
    button_sizer->Add(ok_cancel_panel, 0, wxEXPAND | wxBOTTOM, 0);

    this->SetSizer(button_sizer);
}

void ManualCalibrationPanelButton::update(const AppState &state) {
    main_status_panel->update(state);
    left_status_panel->update(state);
    right_status_panel->update(state);
    preview_panel->update(state);

    auto okState = state.manualCalibrationPanel.okButtonState;
    auto cancelState = state.manualCalibrationPanel.cancelButtonState;
    ok_cancel_panel->update(okState, cancelState);
}

// clang-format off
BEGIN_EVENT_TABLE(ManualCalibrationPanelButton, BaseButtonPanel)
END_EVENT_TABLE()

