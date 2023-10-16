
#include "UI/Panel/CalibrationPanel/PanelStatusOther.hpp"
#include "UI/Panel/CalibrationPanel/PanelStatusTool.hpp"
#include "UI/Panel/Common/Spacer.hpp"
#include "Utils/Enum.hpp"
#include <UI/Panel/CalibrationPanel/Panel_Button.hpp>
#include <wx/gtk/stattext.h>
#include <wx/stringimpl.h>

CalibrationPanelButton::CalibrationPanelButton(wxWindow *parent, wxWindowID id)
    : BaseButtonPanel(parent, id) {

    MainPanel = new CalibrationButtonMain(this);
    ToolPanel = new CalibrationButtonTool(this);
    OtherPanel = new CalibrationButtonOther(this);
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

void CalibrationPanelButton::update(const AppState &state) {
    MainPanel->update(state);
    ToolPanel->update(state);
    OtherPanel->update(state);

    auto okState = state.calibrationPanel.okButtonState;
    auto cancelState = state.calibrationPanel.cancelButtonState;
    OkCancelPanel->update(okState, cancelState);
}

// clang-format off
BEGIN_EVENT_TABLE(CalibrationPanelButton, BaseButtonPanel)
END_EVENT_TABLE()

