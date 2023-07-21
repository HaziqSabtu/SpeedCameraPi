#include "UI/Button/Button_Capture.hpp"
#include "UI/Button/Button_Load.hpp"
#include "UI/Panel/Common/TextOutlinePanel.hpp"
#include "Utils/Enum.hpp"
#include <UI/Panel/CapturePanel/PanelStatusCapture.hpp>
#include <wx/sizer.h>

CaptureStatusPanel::CaptureStatusPanel(wxWindow *parent)
    : TextOutlinePanel(parent, "Capture") {

    Capture_Button = new ButtonCapture(this, Enum::CP_Capture_Button_ID);
    Load_Button = new ButtonLoad(this, Enum::CP_Load_Button_ID);

    reset_Button = new wxButton(this, wxID_ANY, "Reset Capture");

    wxBoxSizer *clSizer = new wxBoxSizer(wxHORIZONTAL);
    clSizer->Add(Capture_Button, 1, wxEXPAND | wxRIGHT, 10);
    clSizer->Add(Load_Button, 1, wxEXPAND | wxRIGHT, 0);

    vSizer = new wxBoxSizer(wxVERTICAL);
    vSizer->Add(topPadding, 0, wxEXPAND);
    vSizer->Add(clSizer, 0, wxEXPAND | wxTOP | wxRIGHT | wxLEFT, 10);
    vSizer->Add(reset_Button, 0, wxEXPAND | wxALL, 10);
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
