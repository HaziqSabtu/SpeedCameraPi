#include "Utils/Enum.hpp"
#include <UI/Button/BitmapButton/Type3/Button_Info.hpp>
#include <wx/app.h>
#include <wx/gdicmn.h>
#include <wx/stringimpl.h>

ButtonInfo::ButtonInfo(wxWindow *parent)
    : wxButton(parent, Enum::G_Info_Button_ID, wxEmptyString, wxDefaultPosition,
               wxSize(40, 40)) {
    SetBackgroundColour(colour);

    wxIcon icon;
    icon.LoadFile(filename, wxBITMAP_TYPE_ICO);
    SetBitmapLabel(icon);
    SetBitmapPosition(wxLEFT);
}

ButtonInfo::~ButtonInfo() {}

void ButtonInfo::OnButton(wxCommandEvent &e) { e.Skip(); }

BEGIN_EVENT_TABLE(ButtonInfo, wxButton)
EVT_BUTTON(Enum::G_Exit_Button_ID, ButtonInfo::OnButton)
END_EVENT_TABLE()