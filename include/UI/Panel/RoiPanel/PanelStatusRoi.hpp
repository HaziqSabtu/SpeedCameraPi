#pragma once

#include "UI/Button/BitmapButton/BitmapButton.hpp"
#include "UI/Button/BitmapButton/Type2/BitmapButtonT2.hpp"
#include "UI/Panel/Common/TextOutlinePanel.hpp"
#include <wx/sizer.h>
#include <wx/wx.h>

class RoiMainStatusPanel : public TextOutlinePanel {
  public:
    RoiMainStatusPanel(wxWindow *parent);

    void update(const AppState &state);

    BitmapButton *calibrate_Button;
    BitmapButton *stop_Button;
    BitmapButtonT2 *camera_Button;
    BitmapButton *reset_Button;

  private:
    void setPanelState(PanelState state);

    void OnButtonClicked(wxCommandEvent &e);

    wxBoxSizer *hSizer;
    wxBoxSizer *vSizer;
    wxBoxSizer *buttonSizer;
};
