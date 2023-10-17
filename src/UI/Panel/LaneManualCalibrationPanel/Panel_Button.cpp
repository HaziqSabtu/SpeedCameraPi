
#include "UI/Panel/Common/BasePanel.hpp"
#include "UI/Panel/Common/Spacer.hpp"
#include "Utils/Enum.hpp"
#include <UI/Panel/LaneManualCalibrationPanel/Panel_Button.hpp>
#include <wx/stringimpl.h>

LaneManualCalibrationPanelButton::LaneManualCalibrationPanelButton(
    wxWindow *parent, wxWindowID id)
    : BaseButtonPanel(parent, id) {

    spacer = new Spacer(this);

    MainPanel = new LaneManualCalibrationButtonMain(this);

    LeftPanel = new LaneManualCalibrationButtonLeft(this);
    RightPanel = new LaneManualCalibrationButtonRight(this);

    lrSizer = new wxBoxSizer(wxHORIZONTAL);
    lrSizer->Add(LeftPanel, 1, wxEXPAND | wxBOTTOM | wxRIGHT, 10);
    lrSizer->Add(RightPanel, 1, wxEXPAND | wxBOTTOM, 10);

    OkCancelPanel = new OKCancelPanel(this);

    button_sizer = new wxBoxSizer(wxVERTICAL);
    button_sizer->Add(MainPanel, 0, wxEXPAND | wxBOTTOM, 10);
    button_sizer->Add(lrSizer, 0, wxEXPAND | wxBOTTOM, 10);
    button_sizer->Add(spacer, 1, wxEXPAND);
    button_sizer->Add(OkCancelPanel, 0, wxEXPAND | wxBOTTOM, 0);

    this->SetSizer(button_sizer);
}

void LaneManualCalibrationPanelButton::update(const AppState &state) {
    MainPanel->update(state);
    LeftPanel->update(state);
    RightPanel->update(state);

    auto okState = state.laneManualCalibrationPanel.okButtonState;
    auto cancelState = state.laneManualCalibrationPanel.cancelButtonState;
    OkCancelPanel->update(okState, cancelState);
}

// clang-format off
BEGIN_EVENT_TABLE(LaneManualCalibrationPanelButton, BaseButtonPanel)
END_EVENT_TABLE()

