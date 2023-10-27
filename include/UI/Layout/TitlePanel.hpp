#pragma once

#include "Model/SessionData.hpp"
#include "UI/Button/BitmapButton/Type3/Button_Exit.hpp"
#include "UI/Button/BitmapButton/Type3/Button_Info.hpp"
#include "UI/Button/BitmapButton/Type3/Button_Settings.hpp"
#include "UI/Button/BitmapButton/Type3/Button_SwitchMode.hpp"
#include "UI/StaticText/Titletext.hpp"
#include <wx/wx.h>

/**
 * @brief The title panel
 * @image html titlepanel.png
 * @image latex titlepanel.png
 */
class TitlePanel : public wxPanel {
  public:
    TitlePanel(wxWindow *parent, PanelID panelID);

    TitlePanel(wxWindow *parent, PanelID panelID, TitleText *titleText,
               ButtonExit *exit_Button, ButtonSettings *setting_Button,
               ButtonInfo *info_Button, ButtonSwitchMode *switchMode_Button);

    ~TitlePanel();

    TitleText *titleText;

    ButtonInfo *info_Button;
    ButtonSettings *setting_Button;
    ButtonExit *exit_Button;
    ButtonSwitchMode *switchMode_Button;

    wxBoxSizer *sizer;

  private:
    void addComponentsToSizer();
};