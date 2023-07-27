#pragma once

#include "UI/Button/BitmapButton/BitmapButton.hpp"
#include "UI/Panel/Common/TextOutlinePanel.hpp"
#include <wx/sizer.h>
#include <wx/wx.h>

class ROIStatusPanel : public TextOutlinePanel {
  public:
    ROIStatusPanel(wxWindow *parent);

    BitmapButton *roi_Button;
    BitmapButton *reset_Button;

    void setPanelState(PanelState state);
    void update(const AppState &state);

  private:
    void OnButtonClicked(wxCommandEvent &e);

    wxBoxSizer *hSizer;
    wxBoxSizer *vSizer;
};
