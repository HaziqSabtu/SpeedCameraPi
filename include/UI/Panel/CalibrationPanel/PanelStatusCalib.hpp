#pragma once

#include "Model/AppState.hpp"
#include "UI/Button/BitmapButton/BitmapButton.hpp"
#include "UI/Button/BitmapButton/Type2/BitmapButtonT2.hpp"
#include "UI/Panel/Common/TextOutlinePanel.hpp"
#include <wx/sizer.h>
#include <wx/wx.h>

class CalibrationMainStatusPanel : public TextOutlinePanel {
  public:
    CalibrationMainStatusPanel(wxWindow *parent);

    BitmapButton *calibrate_Button;
    BitmapButtonT2 *camera_Button;
    BitmapButton *reset_Button;

    void update(const AppState &state);

  private:
    void OnButtonClicked(wxCommandEvent &e);

    wxBoxSizer *hSizer;
    wxBoxSizer *vSizer;
    wxBoxSizer *buttonSizer;
};
