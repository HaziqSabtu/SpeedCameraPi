#pragma once

#include "UI/Button/BitmapButton/BitmapButton.hpp"
#include <UI/Panel/Common/TextOutlinePanel.hpp>

#include <wx/wx.h>

class LaneCalibrationButtonOther : public TextOutlinePanel {

  public:
    LaneCalibrationButtonOther(wxWindow *parent);

    void update(const AppState &state);

    BitmapButton *ColorCalibration_Button;

  private:
    void setPanelState(PanelState state);

    wxBoxSizer *buttonSizer;
    wxBoxSizer *vSizer;
    wxBoxSizer *hSizer;
};