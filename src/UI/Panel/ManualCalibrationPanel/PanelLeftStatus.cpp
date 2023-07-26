#include "UI/Button/BitmapButton/Button_Left.hpp"
#include "UI/Button/BitmapButton/Button_Remove.hpp"
#include "UI/Button/Button_Default.hpp"
#include "UI/Panel/Common/TextOutlinePanel.hpp"
#include "UI/StaticText/RichText.hpp"
#include "Utils/Enum.hpp"
#include <UI/Panel/ManualCalibrationPanel/PanelLeftStatus.hpp>

LeftStatusPanel::LeftStatusPanel(wxWindow *parent)
    : TextOutlinePanel(parent, RTC::LEFT_NONE) {

    left_Button = new BitmapL(this, wxID_ANY);
    clear_Button = new BitmapRemove(this, wxID_ANY);

    buttonSizer = new wxBoxSizer(wxHORIZONTAL);
    buttonSizer->Add(left_Button, 1, wxEXPAND);
    buttonSizer->Add(clear_Button, 1, wxEXPAND);

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

void LeftStatusPanel::OnButtonClicked(wxCommandEvent &e) { e.Skip(); }
