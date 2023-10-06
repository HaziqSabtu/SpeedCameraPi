#pragma once

#include "UI/Panel/Common/TextOutlinePanel.hpp"
#include <wx/sizer.h>
#include <wx/wx.h>

class TrimButtonSetEnd : public TextOutlinePanel {
  public:
    TrimButtonSetEnd(wxWindow *parent);

    void update(const AppState &state);

    BitmapButton *Next_Button;
    BitmapButton *Previous_Button;

  private:
    void setPanelState(PanelState state);

    void OnButtonClicked(wxCommandEvent &e);

    wxBoxSizer *buttonSizer;
};
