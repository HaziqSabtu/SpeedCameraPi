#include <UI/StaticText/Titletext.hpp>
#include <wx/font.h>
#include <wx/gtk/font.h>

TitleText::TitleText(wxWindow *parent, wxWindowID id, PanelID panel_id)
    : wxStaticText(parent, id, panelID_to_string(panel_id)) {

    wxFontInfo fontInfo(14);
    fontInfo.Family(wxFONTFAMILY_DEFAULT).FaceName("Roboto");
    wxFont font(fontInfo);

    SetFont(font);

    SetForegroundColour(textColor);

    sizer = new wxBoxSizer(wxVERTICAL);
    sizer->AddStretchSpacer();
    sizer->Add(this, 0, wxEXPAND);
    sizer->AddStretchSpacer();
}

// TODO: Move to Data
wxString TitleText::panelID_to_string(PanelID panel_id) {

    if (panel_id == PanelID::PANEL_CAPTURE) {
        return "Capture";
    }

    if (panel_id == PanelID::PANEL_CALIBRATION) {
        return "Calibration";
    }

    if (panel_id == PanelID::PANEL_MANUAL_CALIBRATION) {
        return "Manual Calibration";
    }

    if (panel_id == PanelID::PANEL_COLOR_CALIBRATION) {
        return "Color Calibration";
    }

    if (panel_id == PanelID::PANEL_ROI) {
        return "ROI";
    }

    if (panel_id == PanelID::PANEL_RESULT) {
        return "Result";
    }

    if (panel_id == PanelID::PANEL_SETTINGS) {
        return "Settings";
    }

    if (panel_id == PanelID::PANEL_INFO) {
        return "Info";
    }

    return "Unknown Panel";
}