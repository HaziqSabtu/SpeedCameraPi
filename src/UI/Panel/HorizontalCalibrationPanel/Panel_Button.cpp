
#include "UI/Panel/Common/BasePanel.hpp"
#include "UI/Panel/Common/Spacer.hpp"
#include "Utils/Enum.hpp"
#include <UI/Panel/HorizontalCalibrationPanel/Panel_Button.hpp>
#include <wx/stringimpl.h>

HorizontalCalibrationPanelButton::HorizontalCalibrationPanelButton(
    wxWindow *parent, wxWindowID id)
    : BaseButtonPanel(parent, id) {

    spacer = new Spacer(this);

    MainPanel = new HorizontalCalibrationButtonMain(this);

    BottomPanel = new HorizontalCalibrationButtonBottom(this);
    TopPanel = new HorizontalCalibrationButtonTop(this);

    lrSizer = new wxBoxSizer(wxHORIZONTAL);
    lrSizer->Add(TopPanel, 1, wxEXPAND | wxBOTTOM, 10);
    lrSizer->AddSpacer(10);
    lrSizer->Add(BottomPanel, 1, wxEXPAND | wxBOTTOM, 10);

    OkCancelPanel = new OKCancelPanel(this);

    button_sizer = new wxBoxSizer(wxVERTICAL);
    button_sizer->Add(MainPanel, 0, wxEXPAND | wxBOTTOM, 10);
    button_sizer->Add(lrSizer, 0, wxEXPAND | wxBOTTOM, 10);
    button_sizer->Add(spacer, 1, wxEXPAND);
    button_sizer->Add(OkCancelPanel, 0, wxEXPAND | wxBOTTOM, 0);

    this->SetSizer(button_sizer);
}

void HorizontalCalibrationPanelButton::update(const AppState &state) {
    MainPanel->update(state);
    BottomPanel->update(state);
    TopPanel->update(state);

    auto okState = state.horizontalCalibrationPanel.okButtonState;
    auto cancelState = state.horizontalCalibrationPanel.cancelButtonState;
    OkCancelPanel->update(okState, cancelState);
}

// clang-format off
BEGIN_EVENT_TABLE(HorizontalCalibrationPanelButton, BaseButtonPanel)
END_EVENT_TABLE()

