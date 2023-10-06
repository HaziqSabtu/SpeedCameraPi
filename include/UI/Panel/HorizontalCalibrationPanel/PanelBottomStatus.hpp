#pragma once

#include "UI/Panel/Common/TextOutlinePanel.hpp"
#include <wx/sizer.h>
#include <wx/wx.h>

class HorizontalCalibrationButtonBottom : public TextOutlinePanel {
  public:
    HorizontalCalibrationButtonBottom(wxWindow *parent);

    void update(const AppState &state);

    BitmapButton *Bottom_Button;
    BitmapButton *Clear_Button;

  private:
    void setPanelState(PanelState state);

    void OnButtonClicked(wxCommandEvent &e);

    wxBoxSizer *buttonSizer;
};
