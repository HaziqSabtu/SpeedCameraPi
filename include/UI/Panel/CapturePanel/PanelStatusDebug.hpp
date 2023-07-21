#pragma once

#include "UI/Button/Button_wState.hpp"
#include "UI/Panel/Common/TextOutlinePanel.hpp"
#include <wx/sizer.h>
#include <wx/wx.h>

class DebugStatusPanel : public TextOutlinePanel {
  public:
    DebugStatusPanel(wxWindow *parent);

    ButtonWState *ToggleCamera_Button;

  private:
    void OnButtonClicked(wxCommandEvent &e);

    wxBoxSizer *hSizer;
    wxBoxSizer *vSizer;
};
