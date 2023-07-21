#include "Utils/Enum.hpp"
#include <UI/Button/Button_Settings.hpp>
#include <wx/app.h>
#include <wx/gdicmn.h>
#include <wx/stringimpl.h>

ButtonSettings::ButtonSettings(wxWindow *parent)
    : wxButton(parent, Enum::G_Setting_Button_ID, wxEmptyString,
               wxDefaultPosition, wxSize(40, 40)) {
    SetBackgroundColour(colour);

    wxIcon icon;
    icon.LoadFile(filename, wxBITMAP_TYPE_ICO);
    SetBitmapLabel(icon);
    SetBitmapPosition(wxLEFT);
}

ButtonSettings::~ButtonSettings() {}

void ButtonSettings::OnButton(wxCommandEvent &e) { e.Skip(); }

BEGIN_EVENT_TABLE(ButtonSettings, wxButton)
EVT_BUTTON(Enum::G_Exit_Button_ID, ButtonSettings::OnButton)
END_EVENT_TABLE()