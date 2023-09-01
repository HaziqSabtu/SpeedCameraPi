#pragma once

#include "UI/Button/BitmapButton/BitmapButton.hpp"
#include <UI/Panel/Common/TextOutlinePanel.hpp>

#include <wx/wx.h>

class ColorCalibrationButtonOther : public TextOutlinePanel {

  public:
    ColorCalibrationButtonOther(wxWindow *parent);

    void update(const AppState &state);

    BitmapButton *Save_button;
    BitmapButton *Restore_button;

  private:
    wxBoxSizer *vSizer;
    wxBoxSizer *hSizer;
    wxBoxSizer *buttonSizer;
};