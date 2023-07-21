#include "UI/Button/Button_Capture.hpp"
#include "UI/Button/Button_Load.hpp"
#include "UI/Button/Button_ToggleCamera.hpp"
#include "UI/Panel/Common/TextOutlinePanel.hpp"
#include "Utils/Enum.hpp"
#include <UI/Panel/CapturePanel/PanelStatusDebug.hpp>

DebugStatusPanel::DebugStatusPanel(wxWindow *parent)
    : TextOutlinePanel(parent, "#Debug") {
    ToggleCamera_Button =
        new ButtonToggleCam(this, Enum::CP_ToggleCamera_Button_ID);

    hSizer = new wxBoxSizer(wxHORIZONTAL);
    hSizer->Add(leftPadding, 0, wxEXPAND);
    hSizer->Add(ToggleCamera_Button, 1, wxEXPAND);
    hSizer->Add(rightPadding, 0, wxEXPAND);

    vSizer = new wxBoxSizer(wxVERTICAL);
    vSizer->Add(topPadding, 0, wxEXPAND);
    vSizer->Add(hSizer, 0, wxEXPAND | wxALL, 10);
    vSizer->Add(bottomPadding, 0, wxEXPAND);

    SetSizer(vSizer);
    Fit();
}

void DebugStatusPanel::OnButtonClicked(wxCommandEvent &e) { e.Skip(); }
