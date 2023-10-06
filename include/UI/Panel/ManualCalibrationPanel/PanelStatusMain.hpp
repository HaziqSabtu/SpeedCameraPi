#pragma once

#include "UI/Button/BitmapButton/BitmapButton.hpp"
#include "UI/Button/BitmapButton/Type2/BitmapButtonT2.hpp"
#include "UI/Panel/Common/TextOutlinePanel.hpp"
#include <wx/sizer.h>
#include <wx/wx.h>

class ManualCalibrationButtonMain : public TextOutlinePanel {
  public:
    ManualCalibrationButtonMain(wxWindow *parent);

    void update(const AppState &state);

    BitmapButtonT2 *CalibrateCamera_Button;
    BitmapButtonT2 *CalibrateCapture_Button;
    BitmapButton *Reset_Button;

  private:
    void setPanelState(PanelState state);

    void OnButtonClicked(wxCommandEvent &e);

    wxBoxSizer *buttonSizer;
};
