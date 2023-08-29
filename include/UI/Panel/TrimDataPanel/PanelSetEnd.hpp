#pragma once

#include "UI/Panel/Common/TextOutlinePanel.hpp"
#include <wx/sizer.h>
#include <wx/wx.h>

class SetEndPanel : public TextOutlinePanel {
  public:
    SetEndPanel(wxWindow *parent);

    void update(const AppState &state);

    BitmapButton *next_Button;
    BitmapButton *previous_Button;

  private:
    void setPanelState(PanelState state);

    void OnButtonClicked(wxCommandEvent &e);

    wxBoxSizer *hSizer;
    wxBoxSizer *vSizer;
    wxBoxSizer *buttonSizer;
};