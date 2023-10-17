#pragma once

#include "UI/Button/BitmapButton/BitmapButton.hpp"
#include "UI/Panel/Common/TextOutlinePanel.hpp"
#include <wx/sizer.h>
#include <wx/wx.h>

class LaneManualCalibrationButtonRight : public TextOutlinePanel {
  public:
    LaneManualCalibrationButtonRight(wxWindow *parent);

    void update(const AppState &state);

    BitmapButton *Right_Button;
    BitmapButton *Clear_Button;

  private:
    void setPanelState(PanelState state);

    void OnButtonClicked(wxCommandEvent &e);

    wxBoxSizer *buttonSizer;
};
