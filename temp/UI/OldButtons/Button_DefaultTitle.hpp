#pragma once

#include "UI/Data/Theme.hpp"
#include <wx/wx.h>

// NOT WORKING !
class DefaultTitleButton : public wxButton {
  public:
    // same constructor as wxButton
    DefaultTitleButton(wxWindow *parent, wxWindowID id,
                       const wxString &filename, const wxColour &color);

    ~DefaultTitleButton();

  private:
    const wxColour background;
    const wxSize buttonSize = wxSize(40, 40);
};