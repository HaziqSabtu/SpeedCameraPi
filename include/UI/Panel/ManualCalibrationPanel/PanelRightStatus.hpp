#pragma once

#include "UI/Button/BitmapButton/BitmapButton.hpp"
#include "UI/Panel/Common/TextOutlinePanel.hpp"
#include <wx/sizer.h>
#include <wx/wx.h>

class RightStatusPanel : public TextOutlinePanel {
  public:
    RightStatusPanel(wxWindow *parent);

    void update(const AppState &state);

    BitmapButton *right_Button;
    BitmapButton *clear_Button;

  private:
    void setPanelState(PanelState state);

    void OnButtonClicked(wxCommandEvent &e);

    wxBoxSizer *hSizer;
    wxBoxSizer *vSizer;
    wxBoxSizer *buttonSizer;
};
