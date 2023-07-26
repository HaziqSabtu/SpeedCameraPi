#pragma once

#include "UI/Button/TextButton/TextButton.hpp"
#include "wx/wx.h"

class OKCancelPanel : public wxPanel {
  public:
    OKCancelPanel(wxWindow *parent);
    ~OKCancelPanel();

    TextButton *OKButton;
    TextButton *CancelButton;

  private:
    wxBoxSizer *main_sizer;
};