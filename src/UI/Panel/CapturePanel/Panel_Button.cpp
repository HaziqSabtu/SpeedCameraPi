#include "UI/Panel/Common/BasePanel.hpp"
#include "UI/Panel/Common/DividerPanel.hpp"
#include "UI/Panel/Common/Spacer.hpp"
#include "UI/Panel/Common/TextOutlinePanel.hpp"
#include "UI/Theme/Theme.hpp"
#include <UI/Panel/CapturePanel/Panel_Button.hpp>
#include <wx/gdicmn.h>
#include <wx/layout.h>

CaptureButtonPanel::CaptureButtonPanel(wxWindow *parent, wxWindowID id)
    : BaseButtonPanel(parent, id) {

    switch_Button = new MeasureTextButton(this, Enum::CP_Measure_Button_ID);

    spacer = new Spacer(this);

    cPanel = new CaptureStatusPanel(this);
    csPanel = new CalibrationStatusPanel(this);
    rPanel = new ROIStatusPanel(this);

    left_sizer = new wxBoxSizer(wxVERTICAL);
    left_sizer->Add(csPanel, 0, wxEXPAND | wxBOTTOM, 0);

    right_sizer = new wxBoxSizer(wxVERTICAL);
    right_sizer->Add(rPanel, 0, wxEXPAND | wxBOTTOM, 0);

    lrSizer = new wxBoxSizer(wxHORIZONTAL);
    lrSizer->Add(left_sizer, 1, wxALL, 0);
    lrSizer->Add(spacer, 0, wxALL, 0);
    lrSizer->Add(right_sizer, 1, wxALL, 0);

    tPanel = new CaptureToolsPanel(this);

    main_sizer = new wxBoxSizer(wxVERTICAL);
    main_sizer->Add(cPanel, 0, wxEXPAND | wxBOTTOM, 10);
    main_sizer->Add(lrSizer, 0, wxEXPAND | wxBOTTOM, 10);
    main_sizer->Add(tPanel, 0, wxEXPAND | wxBOTTOM, 10);
    main_sizer->Add(switch_Button, 1, wxEXPAND | wxBOTTOM, 0);

    SetSizer(main_sizer);
}

void CaptureButtonPanel::update(const AppState &state) {
    cPanel->update(state);
    csPanel->update(state);
    rPanel->update(state);
    tPanel->update(state);

    auto ms = state.cameraPanel.measureButtonState;
    switch_Button->update(ms);
}

// clang-format off
BEGIN_EVENT_TABLE(CaptureButtonPanel, BaseButtonPanel)
END_EVENT_TABLE()

