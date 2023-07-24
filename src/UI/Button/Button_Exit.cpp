#include "UI/Theme/Theme.hpp"
#include "Utils/Enum.hpp"
#include "Utils/wxUtils.hpp"
#include <UI/Button/Button_Exit.hpp>
#include <wx/app.h>
#include <wx/gdicmn.h>
#include <wx/stringimpl.h>

ButtonExit::ButtonExit(wxWindow *parent)
    : wxButton(parent, Enum::G_Exit_Button_ID, wxEmptyString, wxDefaultPosition,
               wxSize(40, 40), wxBORDER_NONE) {
    SetBackgroundColour(colour);

    wxBitmap icon(filename, wxBITMAP_TYPE_ICO);
    // icon = Utils::recolor(icon, Theme::ExitColor);
    SetBitmapLabel(icon);
    SetBitmapPosition(wxLEFT);
}

ButtonExit::~ButtonExit() {}

void ButtonExit::OnButton(wxCommandEvent &e) { e.Skip(); }

BEGIN_EVENT_TABLE(ButtonExit, wxButton)
EVT_BUTTON(Enum::G_Exit_Button_ID, ButtonExit::OnButton)
END_EVENT_TABLE()