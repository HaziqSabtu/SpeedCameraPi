#pragma once

#include "UI/Panel/Common/TextOutlinePanel.hpp"
#include <wx/sizer.h>
#include <wx/wx.h>

class BlueStatusPanel : public TextOutlinePanel {
  public:
    BlueStatusPanel(wxWindow *parent);

    void update(const AppState &state);

    BitmapButton *color_Button;
    BitmapButton *clear_Button;

  private:
    void setPanelState(PanelState state);

    void OnButtonClicked(wxCommandEvent &e);

    wxBoxSizer *hSizer;
    wxBoxSizer *vSizer;
    wxBoxSizer *buttonSizer;
};
