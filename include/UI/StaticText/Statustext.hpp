#pragma once

#include "UI/Theme/Theme.hpp"
#include <wx/sizer.h>
#include <wx/wx.h>

class StatusText : public wxStaticText {
  public:
    StatusText(wxWindow *parent, wxWindowID id, wxString text);
    ~StatusText();

    void SetText(wxString text);

  private:
    wxBoxSizer *text_sizer;

    wxColour backgroundColour = Theme::StatusBackground;
    wxColour textColour = Theme::StatusText;
};