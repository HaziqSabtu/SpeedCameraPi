#pragma once

#include "UI/Button/BitmapButton/BitmapButton.hpp"
#include "UI/Button/BitmapButton/Type2/BitmapButtonT2.hpp"
#include "UI/Panel/Common/TextOutlinePanel.hpp"
#include <wx/sizer.h>
#include <wx/wx.h>

class ManualCalibrationMainStatusPanel : public TextOutlinePanel {
  public:
    ManualCalibrationMainStatusPanel(wxWindow *parent);

    BitmapButton *calibrate_Button;
    BitmapButtonT2 *camera_Button;
    BitmapButton *preview_Button;
    BitmapButton *reset_Button;

  private:
    void OnButtonClicked(wxCommandEvent &e);

    wxBoxSizer *hSizer;
    wxBoxSizer *vSizer;
    wxBoxSizer *buttonSizer;
};
