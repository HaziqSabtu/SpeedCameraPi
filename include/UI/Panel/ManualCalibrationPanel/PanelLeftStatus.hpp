#pragma once

#include "UI/Panel/Common/TextOutlinePanel.hpp"
#include <wx/sizer.h>
#include <wx/wx.h>

class ManualCalibrationButtonLeft : public TextOutlinePanel {
  public:
    ManualCalibrationButtonLeft(wxWindow *parent);

    void update(const AppState &state);

    BitmapButton *Left_Button;
    BitmapButton *Clear_Button;

  private:
    void setPanelState(PanelState state);

    void OnButtonClicked(wxCommandEvent &e);

    wxBoxSizer *hSizer;
    wxBoxSizer *vSizer;
    wxBoxSizer *buttonSizer;
};
