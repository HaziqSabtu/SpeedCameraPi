#pragma once

#include "Model/AppState.hpp"
#include "UI/Button/TextButton/TextButton.hpp"
#include "wx/wx.h"

/**
 * @class OKCancelPanel
 * @brief Panel with OK and Cancel buttons
 * @image html okcancelpanel.png
 * @image latex okcancelpanel.png
 */
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

/**
 * @class OKCancelResetPanel
 * @brief Panel with OK, Cancel and Reset buttons
 * @image html okcancelresetpanel.png
 * @image latex okcancelresetpanel.png
 */
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