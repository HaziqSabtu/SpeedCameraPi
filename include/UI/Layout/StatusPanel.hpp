#pragma once

#include "UI/Data/StatusData.hpp"
#include "UI/Data/Theme.hpp"
#include "UI/StaticText/Statustext.hpp"
#include <wx/gtk/stattext.h>
#include <wx/string.h>
#include <wx/wx.h>

namespace SC = StatusCollection;

class StatusPanel : public wxPanel {
  public:
    StatusPanel(wxWindow *parent, wxString stat = SC::STATUS_IDLE);
    ~StatusPanel();

    void SetText(wxString text);

  private:
    StatusText *statusText;

    wxStaticText *emptySpacerLeft;
    wxStaticText *emptySpacerRight;

    wxBoxSizer *hSizer;
    wxBoxSizer *vSizer;
};