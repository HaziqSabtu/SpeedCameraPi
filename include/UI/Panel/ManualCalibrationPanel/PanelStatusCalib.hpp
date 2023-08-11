#pragma once

#include "UI/Button/BitmapButton/BitmapButton.hpp"
#include "UI/Button/BitmapButton/Type2/BitmapButtonT2.hpp"
#include "UI/Panel/Common/TextOutlinePanel.hpp"
#include <wx/sizer.h>
#include <wx/wx.h>

class ManualCalibrationMainStatusPanel : public TextOutlinePanel {
  public:
    ManualCalibrationMainStatusPanel(wxWindow *parent);

    void update(const AppState &state);

    BitmapButtonT2 *calibrate_Button;
    BitmapButtonT2 *cCapture_Button;
    // BitmapButton *stop_Button;
    // BitmapButtonT2 *camera_Button;
    BitmapButton *reset_Button;

  private:
    void setPanelState(PanelState state);

    void OnButtonClicked(wxCommandEvent &e);

    wxBoxSizer *hSizer;
    wxBoxSizer *vSizer;
    wxBoxSizer *buttonSizer;
};
