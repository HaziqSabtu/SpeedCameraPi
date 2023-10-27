#include "UI/Panel/Common/Spacer.hpp"
#include "UI/Panel/LaneCalibrationPanel/PanelStatusOther.hpp"
#include "UI/Panel/LaneCalibrationPanel/PanelStatusTool.hpp"
#include "Utils/Enum.hpp"
#include <UI/Panel/LaneCalibrationPanel/Panel_Button.hpp>
#include <wx/gtk/stattext.h>
#include <wx/stringimpl.h>

LaneCalibrationPanelButton::LaneCalibrationPanelButton(wxWindow *parent,
                                                       wxWindowID id)
    : BaseButtonPanel(parent, id) {

    MainPanel = new LaneCalibrationButtonMain(this);
    ToolPanel = new LaneCalibrationButtonTool(this);
    OtherPanel = new LaneCalibrationButtonOther(this);
    OkCancelPanel = new OKCancelPanel(this);

    wxStaticText *spacer = new Spacer(this);

    main_sizer = new wxBoxSizer(wxVERTICAL);
    main_sizer->Add(MainPanel, 0, wxEXPAND | wxBOTTOM, 10);
    main_sizer->Add(ToolPanel, 0, wxEXPAND | wxBOTTOM, 10);
    main_sizer->Add(OtherPanel, 0, wxEXPAND | wxBOTTOM, 10);
    main_sizer->Add(spacer, 1, wxEXPAND | wxBOTTOM, 10);
    main_sizer->Add(OkCancelPanel, 0, wxEXPAND | wxBOTTOM, 0);

    this->SetSizer(main_sizer);
}

void LaneCalibrationPanelButton::update(const AppState &state) {
    MainPanel->update(state);
    ToolPanel->update(state);
    OtherPanel->update(state);

    auto okState = state.laneCalibrationPanel.okButtonState;
    auto cancelState = state.laneCalibrationPanel.cancelButtonState;
    OkCancelPanel->update(okState, cancelState);
}

// clang-format off
BEGIN_EVENT_TABLE(LaneCalibrationPanelButton, BaseButtonPanel)
END_EVENT_TABLE()

