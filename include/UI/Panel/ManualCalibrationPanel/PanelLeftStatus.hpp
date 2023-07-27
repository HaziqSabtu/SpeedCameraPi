#pragma once

#include "UI/Panel/Common/TextOutlinePanel.hpp"
#include <wx/sizer.h>
#include <wx/wx.h>

class LeftStatusPanel : public TextOutlinePanel {
  public:
    LeftStatusPanel(wxWindow *parent);

    void update(const AppState &state);

    BitmapButton *left_Button;
    BitmapButton *clear_Button;

  private:
    void OnButtonClicked(wxCommandEvent &e);

    wxBoxSizer *hSizer;
    wxBoxSizer *vSizer;
    wxBoxSizer *buttonSizer;
};
