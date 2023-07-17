#include "Utils/Enum.hpp"
#include <UI/Button/Button_Exit.hpp>
#include <wx/app.h>
#include <wx/gdicmn.h>
#include <wx/stringimpl.h>

ButtonExit::ButtonExit(wxWindow *parent)
    : wxButton(parent, Enum::G_Exit_Button_ID, wxEmptyString, wxDefaultPosition,
               wxSize(40, 40)) {
    SetBackgroundColour(colour);

    wxIcon icon;
    icon.LoadFile("exit.ico", wxBITMAP_TYPE_ICO);
    SetBitmapLabel(icon);
    SetBitmapPosition(wxLEFT);
}

ButtonExit::~ButtonExit() {}

void ButtonExit::OnButton(wxCommandEvent &e) { e.Skip(); }

BEGIN_EVENT_TABLE(ButtonExit, wxButton)
EVT_BUTTON(Enum::G_Exit_Button_ID, ButtonExit::OnButton)
END_EVENT_TABLE()