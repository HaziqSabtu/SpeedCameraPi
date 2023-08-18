#pragma once

#include "UI/Layout/TitlePanel.hpp"
#include "UI/Panel/Common/OKCancelPanel.hpp"
#include "UI/Panel/SettingsPanel/SettingsPanel.hpp"

#include <wx/wx.h>

class SettingsFrame : public wxFrame {
  public:
    SettingsFrame();

    TitlePanel *title_panel;

    SettingsScrollPanel *scrolled_panel;

    OKCancelResetPanel *ok_cancel_panel;

  private:
    void OnButton(wxCommandEvent &e);

    void OkButtonHandler();
    void CancelButtonHandler();
    void ResetButtonHandler();

    const PanelID panel_id = PanelID::PANEL_SETTINGS;

    DECLARE_EVENT_TABLE()
};