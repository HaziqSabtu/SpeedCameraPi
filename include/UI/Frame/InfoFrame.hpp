#pragma once

#include "UI/Layout/TitlePanel.hpp"
#include "UI/Panel/Common/Spacer.hpp"
#include "UI/Panel/InfoPanel/InfoPanel.hpp"

#include <wx/wx.h>

class InfoFrame : public wxFrame {
  public:
    InfoFrame();

    TitlePanel *title_panel;

    InfoPanel *info_panel;

    TextButton *back_button;

  private:
    void OnButton(wxCommandEvent &e);

    const PanelID panel_id = PanelID::PANEL_INFO;

    DECLARE_EVENT_TABLE()
};