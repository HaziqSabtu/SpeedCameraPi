#pragma once

#include "UI/Theme/Theme.hpp"
#include <wx/wx.h>

class ButtonExit : public wxButton {
  public:
    ButtonExit(wxWindow *parent);
    ~ButtonExit();

  private:
    const wxSize size = wxSize(40, 40);
    const wxColour colour = Theme::ExitColor;
    const wxString filename = Theme::ExitFilename;

    void OnButton(wxCommandEvent &e);
    DECLARE_EVENT_TABLE()
};