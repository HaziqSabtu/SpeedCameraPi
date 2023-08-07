#include "UI/Panel/CapturePanel/PanelStatusDebug.hpp"
#include "UI/Panel/Common/DividerPanel.hpp"
#include "UI/Panel/Common/TextOutlinePanel.hpp"
#include "UI/Theme/Theme.hpp"
#include <UI/Panel/CapturePanel/Panel_Button.hpp>
#include <wx/gdicmn.h>
#include <wx/layout.h>

CaptureButtonPanel::CaptureButtonPanel(wxWindow *parent, wxWindowID id)
    : wxPanel(parent, id, wxDefaultPosition, wxSize(400, 400)) {

    switch_Button = new MeasureTextButton(this, Enum::CP_SWITCH_Button_ID);

    Spacer =
        new wxStaticText(this, wxID_ANY, "", wxDefaultPosition, wxSize(10, 10));

    cPanel = new CaptureStatusPanel(this);
    csPanel = new CalibrationStatusPanel(this);
    rPanel = new ROIStatusPanel(this);

    left_sizer = new wxBoxSizer(wxVERTICAL);
    left_sizer->Add(csPanel, 0, wxEXPAND | wxBOTTOM, 0);

    right_sizer = new wxBoxSizer(wxVERTICAL);
    right_sizer->Add(rPanel, 0, wxEXPAND | wxBOTTOM, 0);

    lrSizer = new wxBoxSizer(wxHORIZONTAL);
    lrSizer->Add(left_sizer, 1, wxALL, 0);
    lrSizer->Add(Spacer, 0, wxALL, 0);
    lrSizer->Add(right_sizer, 1, wxALL, 0);

    main_sizer = new wxBoxSizer(wxVERTICAL);
    main_sizer->Add(cPanel, 0, wxEXPAND | wxBOTTOM, 10);
    main_sizer->Add(lrSizer, 0, wxEXPAND | wxBOTTOM, 10);
    main_sizer->Add(switch_Button, 1, wxEXPAND | wxBOTTOM, 10);

    SetSizer(main_sizer);
}

// clang-format off
BEGIN_EVENT_TABLE(CaptureButtonPanel, wxPanel)
END_EVENT_TABLE()

