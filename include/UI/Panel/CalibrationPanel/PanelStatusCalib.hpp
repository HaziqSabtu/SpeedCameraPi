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

    BitmapButtonT2 *calibrate_Button;
    BitmapButtonT2 *cCapture_Button;
    BitmapButton *reset_Button;

    void update(const AppState &state);

  private:
    void setPanelState(PanelState state);

    void OnButtonClicked(wxCommandEvent &e);

    wxBoxSizer *hSizer;
    wxBoxSizer *vSizer;
    wxBoxSizer *buttonSizer;
};
