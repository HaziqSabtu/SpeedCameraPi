#pragma once

#include "UI/Panel/Common/TextOutlinePanel.hpp"
#include <wx/sizer.h>
#include <wx/wx.h>

class TrimButtonSetStart : public TextOutlinePanel {
  public:
    TrimButtonSetStart(wxWindow *parent);

    void update(const AppState &state);

    BitmapButton *Next_Button;
    BitmapButton *Previous_Button;

  private:
    void setPanelState(PanelState state);

    void OnButtonClicked(wxCommandEvent &e);

    wxBoxSizer *hSizer;
    wxBoxSizer *vSizer;
    wxBoxSizer *buttonSizer;
};
