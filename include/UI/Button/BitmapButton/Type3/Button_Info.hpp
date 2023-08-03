#pragma once

#include "UI/Theme/Theme.hpp"
#include <wx/wx.h>

class ButtonInfo : public wxButton {
  public:
    ButtonInfo(wxWindow *parent);
    ~ButtonInfo();

  private:
    const wxSize size = wxSize(40, 40);
    const wxColour colour = Theme::InfoColor;
    const wxString filename = Theme::InfoFilename;

    void OnButton(wxCommandEvent &e);
    DECLARE_EVENT_TABLE()
};