#pragma once

#include "UI/Panel/Common/TextOutlinePanel.hpp"
#include <wx/sizer.h>
#include <wx/wx.h>

class RightStatusPanel : public TextOutlinePanel {
  public:
    RightStatusPanel(wxWindow *parent);

    wxButton *accept_Button;
    wxButton *clear_Button;

  private:
    void OnButtonClicked(wxCommandEvent &e);

    wxBoxSizer *hSizer;
    wxBoxSizer *vSizer;
};
