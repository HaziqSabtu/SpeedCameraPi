#include <UI/StaticText/Titletext.hpp>

TitleText::TitleText(wxWindow *parent, wxWindowID id, PanelID panel_id)
    : wxStaticText(parent, id, panelID_to_string(panel_id)) {

    sizer = new wxBoxSizer(wxVERTICAL);
    sizer->AddStretchSpacer();
    sizer->Add(this, 0, wxEXPAND);
    sizer->AddStretchSpacer();
}

wxString TitleText::panelID_to_string(PanelID panel_id) {

    if (panel_id == PanelID::PANEL_CAPTURE) {
        return "Capture Panel";
    }

    if (panel_id == PanelID::PANEL_CALIBRATION) {
        return "Calibration Panel";
    }

    return "Unknown Panel";
}