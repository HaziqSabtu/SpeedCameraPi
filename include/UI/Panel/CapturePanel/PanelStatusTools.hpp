#pragma once

#include "UI/Button/BitmapButton/BitmapButton.hpp"
#include "UI/Panel/Common/TextOutlinePanel.hpp"
#include <wx/sizer.h>
#include <wx/wx.h>

class CaptureButtonTools : public TextOutlinePanel {
  public:
    CaptureButtonTools(wxWindow *parent);

    BitmapButton *Save_Button;
    BitmapButton *Trim_Button;
    BitmapButton *Reset_Button;

    void update(const AppState &state);

  private:
    void OnButtonClicked(wxCommandEvent &e);

    void setPanelState(PanelState state);

    wxBoxSizer *buttonSizer;
};
