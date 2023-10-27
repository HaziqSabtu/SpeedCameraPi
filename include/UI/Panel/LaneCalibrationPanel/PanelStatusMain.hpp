#pragma once

#include "Model/AppState.hpp"
#include "UI/Button/BitmapButton/BitmapButton.hpp"
#include "UI/Button/BitmapButton/Type2/BitmapButtonT2.hpp"
#include "UI/Panel/Common/TextOutlinePanel.hpp"
#include <wx/sizer.h>
#include <wx/wx.h>

class LaneCalibrationButtonMain : public TextOutlinePanel {
  public:
    LaneCalibrationButtonMain(wxWindow *parent);

    BitmapButtonT2 *Calibrate_Button;
    BitmapButtonT2 *Preview_Button;
    BitmapButton *ManualCalibration_Button;

    BitmapButton *Reset_Button;

    void update(const AppState &state);

  private:
    void setPanelState(PanelState state);

    void OnButtonClicked(wxCommandEvent &e);

    wxBoxSizer *buttonSizer;
};
