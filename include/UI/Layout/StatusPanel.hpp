#pragma once

#include "UI/StaticText/Statustext.hpp"
#include <wx/string.h>
#include <wx/wx.h>

class StatusPanel : public wxPanel {
  public:
    StatusPanel(wxWindow *parent, wxString stat);
    ~StatusPanel();

    StatusText *statusText;
    wxBoxSizer *hSizer;
    wxBoxSizer *vSizer;
};