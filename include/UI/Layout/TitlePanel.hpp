#pragma once

#include "Model/SessionData.hpp"
#include "UI/Button/Button_Exit.hpp"
#include "UI/StaticText/Titletext.hpp"
#include <wx/wx.h>

class TitlePanel : public wxPanel {
  public:
    TitlePanel(wxWindow *parent, PanelID panelID);

    TitlePanel(wxWindow *parent, PanelID panelID, TitleText *titleText,
               ButtonExit *exit_Button);

    ~TitlePanel();

    TitleText *titleText;
    ButtonExit *exit_Button;

    wxBoxSizer *sizer;
};