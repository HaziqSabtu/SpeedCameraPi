#pragma once

#include <wx/wx.h>

class SettingsFrame : public wxFrame {
  public:
    SettingsFrame();

  private:
    void OnButton(wxCommandEvent &e);

    DECLARE_EVENT_TABLE()
};