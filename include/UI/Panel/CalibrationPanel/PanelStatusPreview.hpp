#pragma once

#include "UI/Button/BitmapButton/BitmapButton.hpp"
#include "UI/Button/BitmapButton/Type2/BitmapButtonT2.hpp"
#include <UI/Panel/Common/TextOutlinePanel.hpp>

#include <wx/wx.h>

class CalibrationButtonPreview : public TextOutlinePanel {

  public:
    CalibrationButtonPreview(wxWindow *parent);

    void update(const AppState &state);

    BitmapButtonT2 *PreviewCamera_Button;
    BitmapButtonT2 *PreviewCapture_Button;

  private:
    void setPanelState(PanelState state);

    wxBoxSizer *buttonSizer;
    wxBoxSizer *vSizer;
    wxBoxSizer *hSizer;
};