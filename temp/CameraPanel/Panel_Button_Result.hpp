#ifndef PANEL_BUTTON_RESULT_HPP
#define PANEL_BUTTON_RESULT_HPP

#include <UI/Button/Button_BBox.hpp>
#include <UI/Button/Button_BotL.hpp>
#include <UI/Button/Button_OFPnt.hpp>
#include <UI/Button/Button_SelL.hpp>
#include <Utils/Enum.hpp>
#include <wx/wx.h>

class PanelButtonResult : public wxPanel {
  public:
    PanelButtonResult(wxWindow *parent, wxWindowID id);
    void DisableAllButtons();
    void EnableAllButtons();

    bool GetBBoxState() { return BBox_Button->GetState(); }
    bool GetBotLState() { return BotL_Button->GetState(); }
    bool GetOFPntState() { return OFPnt_Button->GetState(); }
    bool GetSelLState() { return SelL_Button->GetState(); }

  private:
    wxBoxSizer *button_sizer;

    ButtonBBox *BBox_Button;
    ButtonBotL *BotL_Button;
    ButtonOFPnt *OFPnt_Button;
    ButtonSelL *SelL_Button;
    wxButton *Reset_Button;
    wxButton *Replay_Button;
    wxButton *Reselect_Button;
    wxStaticText *Spacer;

    bool isInit;

    void OnButton(wxCommandEvent &e);
    void OnShow(wxShowEvent &e);
    DECLARE_EVENT_TABLE();
};
#endif
