#pragma once

#include "UI/StaticText/Statustext.hpp"
#include <wx/gtk/stattext.h>
#include <wx/string.h>
#include <wx/wx.h>

class StatusPanel : public wxPanel {
  public:
    StatusPanel(wxWindow *parent, wxString stat);
    ~StatusPanel();

    void SetText(wxString text);

  private:
    StatusText *statusText;

    wxStaticText *emptySpacerLeft;
    wxStaticText *emptySpacerRight;

    wxBoxSizer *hSizer;
    wxBoxSizer *vSizer;
};