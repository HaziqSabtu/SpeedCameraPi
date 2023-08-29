
#include "UI/Panel/CalibrationPanel/PanelStatusOther.hpp"
#include "UI/Panel/CalibrationPanel/PanelStatusTool.hpp"
#include "UI/Panel/Common/Spacer.hpp"
#include "Utils/Enum.hpp"
#include <UI/Panel/CalibrationPanel/Panel_Button.hpp>
#include <wx/gtk/stattext.h>
#include <wx/stringimpl.h>

CalibrationPanelButton::CalibrationPanelButton(wxWindow *parent, wxWindowID id)
    : BaseButtonPanel(parent, id) {

    cPanel = new CalibrationMainStatusPanel(this);
    ctPanel = new CalibrationToolPanel(this);
    cpPanel = new CalibrationPreviewPanel(this);
    coPanel = new CalibrationOtherPanel(this);
    okCancelPanel = new OKCancelPanel(this);

    wxStaticText *spacer = new Spacer(this);

    main_sizer = new wxBoxSizer(wxVERTICAL);
    main_sizer->Add(cPanel, 0, wxEXPAND | wxBOTTOM, 10);
    main_sizer->Add(ctPanel, 0, wxEXPAND | wxBOTTOM, 10);
    main_sizer->Add(cpPanel, 0, wxEXPAND | wxBOTTOM, 10);
    main_sizer->Add(coPanel, 0, wxEXPAND | wxBOTTOM, 10);
    main_sizer->Add(spacer, 1, wxEXPAND | wxBOTTOM, 10);
    main_sizer->Add(okCancelPanel, 0, wxEXPAND | wxBOTTOM, 0);

    this->SetSizer(main_sizer);
}

void CalibrationPanelButton::update(const AppState &state) {
    cPanel->update(state);
    ctPanel->update(state);
    cpPanel->update(state);
    coPanel->update(state);

    auto okState = state.calibrationPanel.okButtonState;
    auto cancelState = state.calibrationPanel.cancelButtonState;
    okCancelPanel->update(okState, cancelState);
}

// clang-format off
BEGIN_EVENT_TABLE(CalibrationPanelButton, BaseButtonPanel)
END_EVENT_TABLE()

