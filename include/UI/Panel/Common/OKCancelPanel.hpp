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

  protected:
    wxBoxSizer *main_sizer;
};

class OKCancelResetPanel : public OKCancelPanel {
  public:
    OKCancelResetPanel(wxWindow *parent);
    ~OKCancelResetPanel();

    void update(ButtonState okButtonState, ButtonState cancelButtonState,
                ButtonState resetButtonState);

    TextButton *ResetButton;

  protected:
    wxBoxSizer *main_sizer;
};