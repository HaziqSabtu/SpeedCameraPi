#include "UI/Button/Button_Capture.hpp"
#include "UI/Button/Button_Default.hpp"
#include "UI/Button/Button_Load.hpp"
#include "UI/Panel/Common/TextOutlinePanel.hpp"
#include "UI/StaticText/RichText.hpp"
#include "Utils/Enum.hpp"
#include <UI/Panel/CapturePanel/PanelStatusCapture.hpp>
#include <wx/gtk/stattext.h>
#include <wx/sizer.h>

CaptureStatusPanel::CaptureStatusPanel(wxWindow *parent)
    : TextOutlinePanel(parent, RTC::CAPTURE_NONE) {

    Capture_Button = new ButtonCapture(this, Enum::CP_Capture_Button_ID);
    Load_Button = new ButtonLoad(this, Enum::CP_Load_Button_ID);

    reset_Button = new DefaultButton(this, wxID_ANY, "Reset Capture");
    replay_Button = new DefaultButton(this, wxID_ANY, "Replay Capture");

    wxStaticText *middleSpacer =
        new wxStaticText(this, wxID_ANY, "", wxDefaultPosition, wxSize(10, 10));

    leftSizer = new wxBoxSizer(wxVERTICAL);
    leftSizer->Add(Capture_Button, 0, wxEXPAND | wxBOTTOM, 10);
    leftSizer->Add(replay_Button, 0, wxEXPAND | wxBOTTOM, 0);

    rightSizer = new wxBoxSizer(wxVERTICAL);
    rightSizer->Add(Load_Button, 0, wxEXPAND | wxBOTTOM, 10);
    rightSizer->Add(reset_Button, 0, wxEXPAND | wxBOTTOM, 0);

    buttonSizer = new wxBoxSizer(wxHORIZONTAL);
    buttonSizer->Add(leftSizer, 1, wxEXPAND);
    buttonSizer->Add(middleSpacer, 0, wxEXPAND);
    buttonSizer->Add(rightSizer, 1, wxEXPAND);

    vSizer = new wxBoxSizer(wxVERTICAL);
    vSizer->Add(topPadding, 0, wxEXPAND);
    // vSizer->Add(clSizer, 0, wxEXPAND | wxTOP | wxRIGHT | wxLEFT, 10);
    vSizer->Add(buttonSizer, 0, wxEXPAND | wxALL, 10);
    vSizer->Add(bottomPadding, 0, wxEXPAND);

    hSizer = new wxBoxSizer(wxHORIZONTAL);
    hSizer->Add(leftPadding, 0, wxEXPAND);
    hSizer->Add(vSizer, 1, wxEXPAND);
    hSizer->Add(rightPadding, 0, wxEXPAND);

    SetSizer(hSizer);
    Fit();

    reset_Button->Bind(wxEVT_BUTTON, &CaptureStatusPanel::OnButtonClicked,
                       this);
}

void CaptureStatusPanel::OnButtonClicked(wxCommandEvent &e) { e.Skip(); }
