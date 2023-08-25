#pragma once

#include "UI/Panel/Common/OKCancelPanel.hpp"
#include "UI/Panel/TrimDataPanel/PanelSetEnd.hpp"
#include "UI/Panel/TrimDataPanel/PanelSetStart.hpp"
#include "UI/Panel/TrimDataPanel/PanelStatusTrim.hpp"
#include <Utils/Enum.hpp>

#include <wx/gtk/button.h>
#include <wx/sizer.h>
#include <wx/wx.h>

class TrimDataPanelButton : public wxPanel {
  public:
    TrimDataPanelButton(wxWindow *parent, wxWindowID id);

    TrimDataMainPanel *main_status_panel;

    SetStartPanel *set_start_panel;
    SetEndPanel *set_end_panel;

    OKCancelPanel *ok_cancel_panel;

  private:
    wxStaticText *Spacer;

    wxBoxSizer *lrSizer;
    wxBoxSizer *button_sizer;

    DECLARE_EVENT_TABLE();
};
