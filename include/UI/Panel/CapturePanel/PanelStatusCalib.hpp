#pragma once

#include "Model/AppState.hpp"
#include "UI/Button/BitmapButton/BitmapButton.hpp"
#include "UI/Panel/Common/TextOutlinePanel.hpp"
#include <wx/sizer.h>
#include <wx/wx.h>

class CalibrationStatusPanel : public TextOutlinePanel {
  public:
    CalibrationStatusPanel(wxWindow *parent);

    BitmapButton *calibrate_Button;
    BitmapButton *reset_Button;

    void setPanelState(PanelState state);

  private:
    void OnButtonClicked(wxCommandEvent &e);

    wxBoxSizer *hSizer;
    wxBoxSizer *vSizer;
};
