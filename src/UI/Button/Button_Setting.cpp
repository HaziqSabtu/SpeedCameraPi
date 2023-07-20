#include "Utils/Enum.hpp"
#include <UI/Button/Button_Setting.hpp>
#include <wx/app.h>
#include <wx/gdicmn.h>
#include <wx/stringimpl.h>

ButtonSetting::ButtonSetting(wxWindow *parent)
    : wxButton(parent, Enum::G_Setting_Button_ID, wxEmptyString,
               wxDefaultPosition, wxSize(40, 40)) {
    SetBackgroundColour(colour);

    wxIcon icon;
    icon.LoadFile(filename, wxBITMAP_TYPE_ICO);
    SetBitmapLabel(icon);
    SetBitmapPosition(wxLEFT);
}

ButtonSetting::~ButtonSetting() {}

void ButtonSetting::OnButton(wxCommandEvent &e) { e.Skip(); }

BEGIN_EVENT_TABLE(ButtonSetting, wxButton)
EVT_BUTTON(Enum::G_Exit_Button_ID, ButtonSetting::OnButton)
END_EVENT_TABLE()