#pragma once

#include "UI/Button/BitmapButton/BitmapButton.hpp"
#include "UI/Button/BitmapButton/Type2/BitmapButtonT2.hpp"
#include "UI/Panel/Common/TextOutlinePanel.hpp"
#include <wx/sizer.h>
#include <wx/wx.h>

class ResultPanelMain : public TextOutlinePanel {
  public:
    ResultPanelMain(wxWindow *parent);

    void update(const AppState &state);

    BitmapButton *Process_Button;
    BitmapButton *Redundant_Button;
    BitmapButtonT2 *Preview_Button;

  private:
    void setPanelState(PanelState state);

    void OnButtonClicked(wxCommandEvent &e);

    wxBoxSizer *hSizer;
    wxBoxSizer *vSizer;
    wxBoxSizer *buttonSizer;
};
