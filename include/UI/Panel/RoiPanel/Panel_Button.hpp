#pragma once

#include <Utils/Enum.hpp>

#include <wx/gtk/button.h>
#include <wx/wx.h>

class RoiButtonPanel : public wxPanel {
  public:
    RoiButtonPanel(wxWindow *parent, wxWindowID id);
    void DisableAllButtons();
    void EnableAllButtons();

    wxButton *switchButton;

  private:
    wxPanel *button_panel;
    wxBoxSizer *button_sizer;

    wxStaticText *Spacer;

    DECLARE_EVENT_TABLE();
};
