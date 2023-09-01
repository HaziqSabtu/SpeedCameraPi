#pragma once

#include "UI/Panel/Common/TextOutlinePanel.hpp"
#include <wx/sizer.h>
#include <wx/wx.h>

class ColorCalibrationButtonBlue : public TextOutlinePanel {
  public:
    ColorCalibrationButtonBlue(wxWindow *parent);

    void update(const AppState &state);

    BitmapButton *Color_Button;
    BitmapButton *Clear_Button;

  private:
    void setPanelState(PanelState state);

    void OnButtonClicked(wxCommandEvent &e);

    wxBoxSizer *hSizer;
    wxBoxSizer *vSizer;
    wxBoxSizer *buttonSizer;
};
