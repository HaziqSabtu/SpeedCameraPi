#include "UI/Button/Button_Default.hpp"
#include "UI/Panel/Common/TextOutlinePanel.hpp"
#include "UI/StaticText/RichText.hpp"
#include "Utils/Enum.hpp"
#include <UI/Panel/ManualCalibrationPanel/PanelRightStatus.hpp>

RightStatusPanel::RightStatusPanel(wxWindow *parent)
    : TextOutlinePanel(parent, RTC::RIGHT_NONE) {

    accept_Button =
        new DefaultButton(this, Enum::CP_CALIBRATE_Button_ID, "Accept");
    clear_Button = new DefaultButton(this, wxID_ANY, "Clear");

    vSizer = new wxBoxSizer(wxVERTICAL);
    vSizer->Add(topPadding, 0, wxEXPAND);
    vSizer->Add(accept_Button, 0, wxEXPAND | wxTOP | wxRIGHT | wxLEFT, 10);
    vSizer->Add(clear_Button, 0, wxEXPAND | wxALL, 10);
    vSizer->Add(bottomPadding, 0, wxEXPAND);

    hSizer = new wxBoxSizer(wxHORIZONTAL);
    hSizer->Add(leftPadding, 0, wxEXPAND);
    hSizer->Add(vSizer, 1, wxEXPAND);
    hSizer->Add(rightPadding, 0, wxEXPAND);

    SetSizer(hSizer);
    Fit();
}

void RightStatusPanel::OnButtonClicked(wxCommandEvent &e) { e.Skip(); }
