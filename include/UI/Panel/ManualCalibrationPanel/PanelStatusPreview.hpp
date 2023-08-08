#pragma once

#include "UI/Button/BitmapButton/BitmapButton.hpp"
#include "UI/Button/BitmapButton/Type2/BitmapButtonT2.hpp"
#include <UI/Panel/Common/TextOutlinePanel.hpp>

#include <wx/wx.h>

class ManualCalibrationPreviewPanel : public TextOutlinePanel {

  public:
    ManualCalibrationPreviewPanel(wxWindow *parent);

    void update(const AppState &state);

    BitmapButtonT2 *pCamera_button;
    BitmapButtonT2 *pCapture_button;

  private:
    void setPanelState(PanelState state);

    wxBoxSizer *buttonSizer;
    wxBoxSizer *vSizer;
    wxBoxSizer *hSizer;
};