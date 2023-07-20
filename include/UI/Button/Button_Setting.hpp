#pragma once

#include <wx/wx.h>

class ButtonSetting : public wxButton {
  public:
    ButtonSetting(wxWindow *parent);
    ~ButtonSetting();

  private:
    const wxSize size = wxSize(40, 40);
    const wxColour colour = wxColour(231, 177, 10);
    const wxString filename = wxT("settings_24.ico");

    void OnButton(wxCommandEvent &e);
    DECLARE_EVENT_TABLE()
};