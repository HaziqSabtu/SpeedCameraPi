#include "UI/Button/BitmapButton/Button_Cancel.hpp"
#include "UI/Button/BitmapButton/Button_OK.hpp"
#include "UI/Button/BitmapButton/Button_Target.hpp"
#include <UI/Panel/CalibrationPanel/PanelStatusTool.hpp>

CalibrationToolPanel::CalibrationToolPanel(wxWindow *parent)
    : TextOutlinePanel(parent, RTC::CALIB_TOOL) {

    target_button = new BitmapTarget(this, wxID_ANY);
    cancel_button = new BitmapCancel(this, wxID_ANY);
    ok_button = new BitmapOK(this, wxID_ANY);

    buttonSizer = new wxBoxSizer(wxHORIZONTAL);
    buttonSizer->Add(target_button, 1, wxEXPAND);
    buttonSizer->Add(cancel_button, 1, wxEXPAND);
    buttonSizer->Add(ok_button, 1, wxEXPAND);

    vSizer = new wxBoxSizer(wxVERTICAL);
    vSizer->Add(topPadding, 0, wxEXPAND);
    vSizer->Add(buttonSizer, 0, wxEXPAND | wxALL, 10);
    vSizer->Add(bottomPadding, 0, wxEXPAND);

    hSizer = new wxBoxSizer(wxHORIZONTAL);
    hSizer->Add(leftPadding, 0, wxEXPAND);
    hSizer->Add(vSizer, 1, wxEXPAND);
    hSizer->Add(rightPadding, 0, wxEXPAND);

    SetSizer(hSizer);
    Fit();
}