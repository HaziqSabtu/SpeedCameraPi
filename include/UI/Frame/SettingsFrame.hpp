#pragma once

#include "UI/Layout/TitlePanel.hpp"
#include <wx/wx.h>

class SettingsFrame : public wxFrame {
  public:
    SettingsFrame();

    TitlePanel *title_panel;

  private:
    void OnButton(wxCommandEvent &e);

    const PanelID panel_id = PanelID::PANEL_SETTINGS;

    DECLARE_EVENT_TABLE()
};