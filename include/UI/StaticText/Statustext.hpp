#pragma once

#include "UI/Data/Theme.hpp"
#include "UI/Panel/Common/Spacer.hpp"
#include <wx/sizer.h>
#include <wx/wx.h>

class StatusText : public wxStaticText {
  public:
    StatusText(wxWindow *parent, wxWindowID id, wxString text,
               const wxPoint &pos = wxDefaultPosition,
               const wxSize &size = wxDefaultSize, long style = wxALIGN_LEFT);
    ~StatusText();

    void SetText(wxString text);

  private:
    wxBoxSizer *text_sizer;

    wxColour backgroundColour = Theme::StatusBackground;
    wxColour textColour = Theme::StatusText;
};