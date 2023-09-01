#pragma once

#include "UI/Button/BitmapButton/BitmapButton.hpp"
#include <UI/Panel/Common/TextOutlinePanel.hpp>

#include <wx/wx.h>

class CalibrationButtonTool : public TextOutlinePanel {

  public:
    CalibrationButtonTool(wxWindow *parent);

    void update(const AppState &state);

    BitmapButton *SetPoint_Button;
    BitmapButton *Cancel_Button;

  private:
    void setPanelState(PanelState state);

    wxBoxSizer *buttonSizer;
    wxBoxSizer *vSizer;
    wxBoxSizer *hSizer;
};