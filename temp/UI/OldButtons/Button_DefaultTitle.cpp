#include "UI/Data/Theme.hpp"
#include <UI/Button/Button_DefaultTitle.hpp>
#include <wx/gdicmn.h>

DefaultTitleButton::DefaultTitleButton(wxWindow *parent, wxWindowID id,
                                       const wxString &filename,
                                       const wxColour &color)
    : wxButton(parent, id, wxEmptyString, wxDefaultPosition, wxSize(40, 40)) {
    SetBackgroundColour(Theme::ButtonBackground);

    wxIcon icon;
    icon.LoadFile(filename, wxBITMAP_TYPE_ICO);
    SetBitmapLabel(icon);
    SetBitmapPosition(wxLEFT);
}

DefaultTitleButton::~DefaultTitleButton() {}