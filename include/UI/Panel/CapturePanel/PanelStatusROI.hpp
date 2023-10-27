#pragma once

#include "UI/Button/BitmapButton/BitmapButton.hpp"
#include "UI/Panel/Common/TextOutlinePanel.hpp"
#include <Model/AppState.hpp>
#include <wx/sizer.h>
#include <wx/wx.h>

class CaptureButtonROI : public TextOutlinePanel {
  public:
    CaptureButtonROI(wxWindow *parent);

    BitmapButton *Roi_Button;
    BitmapButton *Reset_Button;

    void setPanelState(PanelState state);
    void update(const AppState &state);

  private:
    void OnButtonClicked(wxCommandEvent &e);

    wxBoxSizer *buttonSizer;
};
