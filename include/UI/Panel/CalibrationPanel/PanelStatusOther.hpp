#pragma once

#include "UI/Button/BitmapButton/BitmapButton.hpp"
#include <UI/Panel/Common/TextOutlinePanel.hpp>

#include <wx/wx.h>

class CalibrationOtherPanel : public TextOutlinePanel {

  public:
    CalibrationOtherPanel(wxWindow *parent);

    BitmapButton *recalibrate_button;
    BitmapButton *manual_button;

  private:
    wxBoxSizer *buttonSizer;
    wxBoxSizer *vSizer;
    wxBoxSizer *hSizer;
};