#pragma once

#include "UI/Button/BitmapButton/BitmapButton.hpp"
#include <UI/Panel/Common/TextOutlinePanel.hpp>

#include <wx/wx.h>

class ColorCalibrationOtherPanel : public TextOutlinePanel {

  public:
    ColorCalibrationOtherPanel(wxWindow *parent);

    void update(const AppState &state);

    BitmapButton *save_button;
    BitmapButton *restore_button;

  private:
    wxBoxSizer *buttonSizer;
    wxBoxSizer *vSizer;
    wxBoxSizer *hSizer;
};