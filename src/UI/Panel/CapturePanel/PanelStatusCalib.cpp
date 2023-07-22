#include "UI/Button/Button_Default.hpp"
#include "UI/Panel/Common/TextOutlinePanel.hpp"
#include "UI/StaticText/RichText.hpp"
#include "Utils/Enum.hpp"
#include <UI/Panel/CapturePanel/PanelStatusCalib.hpp>

CalibrationStatusPanel::CalibrationStatusPanel(wxWindow *parent)
    : TextOutlinePanel(parent, RTC::CALIB_OK) {

    calibrate_Button =
        new DefaultButton(this, Enum::CP_CALIBRATE_Button_ID, "Calibrate");
    reset_Button = new DefaultButton(this, wxID_ANY, "Reset Calibration");

    vSizer = new wxBoxSizer(wxVERTICAL);
    vSizer->Add(topPadding, 0, wxEXPAND);
    vSizer->Add(calibrate_Button, 0, wxEXPAND | wxTOP | wxRIGHT | wxLEFT, 10);
    vSizer->Add(reset_Button, 0, wxEXPAND | wxALL, 10);
    vSizer->Add(bottomPadding, 0, wxEXPAND);

    hSizer = new wxBoxSizer(wxHORIZONTAL);
    hSizer->Add(leftPadding, 0, wxEXPAND);
    hSizer->Add(vSizer, 1, wxEXPAND);
    hSizer->Add(rightPadding, 0, wxEXPAND);

    SetSizer(hSizer);
    Fit();

    reset_Button->Bind(wxEVT_BUTTON, &CalibrationStatusPanel::OnButtonClicked,
                       this);
}

void CalibrationStatusPanel::OnButtonClicked(wxCommandEvent &e) { e.Skip(); }
