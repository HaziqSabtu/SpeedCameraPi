#pragma once

#include "UI/Button/BitmapButton/BitmapButton.hpp"
#include <UI/Panel/Common/TextOutlinePanel.hpp>

#include <wx/wx.h>

class CalibrationButtonOther : public TextOutlinePanel {

  public:
    CalibrationButtonOther(wxWindow *parent);

    void update(const AppState &state);

    BitmapButton *ColorCalibration_Button;
    // BitmapButton *ManualCalibration_Button;

  private:
    void setPanelState(PanelState state);

    wxBoxSizer *buttonSizer;
    wxBoxSizer *vSizer;
    wxBoxSizer *hSizer;
};