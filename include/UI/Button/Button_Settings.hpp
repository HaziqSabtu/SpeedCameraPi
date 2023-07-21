#pragma once

#include "UI/Theme/Theme.hpp"
#include <wx/wx.h>

class ButtonSettings : public wxButton {
  public:
    ButtonSettings(wxWindow *parent);
    ~ButtonSettings();

  private:
    const wxSize size = wxSize(40, 40);
    const wxColour colour = Theme::SettingsColor;
    const wxString filename = Theme::SettingsFilename;

    void OnButton(wxCommandEvent &e);
    DECLARE_EVENT_TABLE()
};