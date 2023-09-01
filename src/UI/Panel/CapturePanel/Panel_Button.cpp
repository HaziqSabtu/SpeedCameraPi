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

    Measure_Button = new MeasureTextButton(this, Enum::CP_Measure_Button_ID);

    spacer = new Spacer(this);

    MainPanel = new CaptureButtonMain(this);
    CalibrationPanel = new CaptureButtonCalibration(this);
    RoiPanel = new CaptureButtonROI(this);

    left_sizer = new wxBoxSizer(wxVERTICAL);
    left_sizer->Add(CalibrationPanel, 0, wxEXPAND | wxBOTTOM, 0);

    right_sizer = new wxBoxSizer(wxVERTICAL);
    right_sizer->Add(RoiPanel, 0, wxEXPAND | wxBOTTOM, 0);

    lrSizer = new wxBoxSizer(wxHORIZONTAL);
    lrSizer->Add(left_sizer, 1, wxALL, 0);
    lrSizer->Add(spacer, 0, wxALL, 0);
    lrSizer->Add(right_sizer, 1, wxALL, 0);

    ToolsPanel = new CaptureButtonTools(this);

    main_sizer = new wxBoxSizer(wxVERTICAL);
    main_sizer->Add(MainPanel, 0, wxEXPAND | wxBOTTOM, 10);
    main_sizer->Add(lrSizer, 0, wxEXPAND | wxBOTTOM, 10);
    main_sizer->Add(ToolsPanel, 0, wxEXPAND | wxBOTTOM, 10);
    main_sizer->Add(Measure_Button, 1, wxEXPAND | wxBOTTOM, 0);

    SetSizer(main_sizer);
}

void CaptureButtonPanel::update(const AppState &state) {
    MainPanel->update(state);
    CalibrationPanel->update(state);
    RoiPanel->update(state);
    ToolsPanel->update(state);

    auto ms = state.cameraPanel.measureButtonState;
    Measure_Button->update(ms);
}

// clang-format off
BEGIN_EVENT_TABLE(CaptureButtonPanel, BaseButtonPanel)
END_EVENT_TABLE()

