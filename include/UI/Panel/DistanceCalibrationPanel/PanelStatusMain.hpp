#pragma once

#include "UI/Button/BitmapButton/BitmapButton.hpp"
#include "UI/Button/BitmapButton/Type2/BitmapButtonT2.hpp"
#include "UI/Panel/Common/TextOutlinePanel.hpp"
#include <wx/sizer.h>
#include <wx/wx.h>

class DistanceCalibrationButtonMain : public TextOutlinePanel {
  public:
    DistanceCalibrationButtonMain(wxWindow *parent);

    void update(const AppState &state);

    BitmapButtonT2 *Calibrate_Button;
    BitmapButtonT2 *Preview_Button;

    BitmapButton *Reset_Button;

  private:
    void setPanelState(PanelState state);

    void OnButtonClicked(wxCommandEvent &e);

    wxBoxSizer *buttonSizer;
};
