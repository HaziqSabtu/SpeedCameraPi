#pragma once

#include "UI/Theme/Theme.hpp"
#include <wx/wx.h>

class DefaultButton : public wxButton {
  public:
    // same constructor as wxButton
    DefaultButton(wxWindow *parent, wxWindowID id, const wxString &label,
                  const wxPoint &pos = wxDefaultPosition,
                  const wxSize &size = wxDefaultSize, long style = 0,
                  const wxValidator &validator = wxDefaultValidator,
                  const wxString &name = wxButtonNameStr);
    DefaultButton(wxWindow *parent, wxWindowID id, const wxString &label,
                  const wxColour &background, const wxColour &foreground,
                  const wxPoint &pos = wxDefaultPosition,
                  const wxSize &size = wxDefaultSize, long style = 0,
                  const wxValidator &validator = wxDefaultValidator,
                  const wxString &name = wxButtonNameStr);

    ~DefaultButton();

  private:
    wxColour background = Theme::ButtonBackground;
    wxColour foreground = Theme::ButtonText;
};