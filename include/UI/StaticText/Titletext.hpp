#pragma once

#include "Model/SessionData.hpp"
#include <wx/wx.h>

class TitleText : public wxStaticText {
  public:
    TitleText(wxWindow *parent, wxWindowID id, PanelID panel_id);
    wxBoxSizer *sizer;

  private:
    wxString panelID_to_string(PanelID panel_id);
};