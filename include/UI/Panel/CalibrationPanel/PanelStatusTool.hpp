#pragma once

#include "UI/Button/BitmapButton/BitmapButton.hpp"
#include <UI/Panel/Common/TextOutlinePanel.hpp>

#include <wx/wx.h>

class CalibrationToolPanel : public TextOutlinePanel {

  public:
    CalibrationToolPanel(wxWindow *parent);

    void update(const AppState &state);

    BitmapButton *target_button;
    BitmapButton *cancel_button;
    BitmapButton *ok_button;

  private:
    wxBoxSizer *buttonSizer;
    wxBoxSizer *vSizer;
    wxBoxSizer *hSizer;
};