#pragma once

#include "Model/AppState.hpp"
#include "UI/Button/TextButton/TextButton.hpp"
#include "wx/wx.h"

class OKCancelPanel : public wxPanel {
  public:
    OKCancelPanel(wxWindow *parent);
    ~OKCancelPanel();

    void update(ButtonState okButtonState, ButtonState cancelButtonState);

    TextButton *OKButton;
    TextButton *CancelButton;

  private:
    wxBoxSizer *main_sizer;
};