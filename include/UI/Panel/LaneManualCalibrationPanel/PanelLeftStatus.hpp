#pragma once

#include "UI/Panel/Common/TextOutlinePanel.hpp"
#include <wx/sizer.h>
#include <wx/wx.h>

class LaneManualCalibrationButtonLeft : public TextOutlinePanel {
  public:
    LaneManualCalibrationButtonLeft(wxWindow *parent);

    void update(const AppState &state);

    BitmapButton *Left_Button;
    BitmapButton *Clear_Button;

  private:
    void setPanelState(PanelState state);

    void OnButtonClicked(wxCommandEvent &e);

    wxBoxSizer *buttonSizer;
};
