#pragma once

#include "UI/Button/BitmapButton/BitmapButton.hpp"
#include "UI/Button/BitmapButton/Type2/BitmapButtonT2.hpp"
#include "UI/Panel/Common/TextOutlinePanel.hpp"
#include <wx/sizer.h>
#include <wx/wx.h>

class ResultPanelPreview : public TextOutlinePanel {
  public:
    ResultPanelPreview(wxWindow *parent);

    void update(const AppState &state);

    BitmapButtonT2 *Box_Button;
    BitmapButtonT2 *Intersection_Button;
    BitmapButtonT2 *Lanes_Button;
    BitmapButton *Replay_Button;

  private:
    void setPanelState(PanelState state);

    void OnButtonClicked(wxCommandEvent &e);

    wxBoxSizer *hSizer;
    wxBoxSizer *vSizer;
    wxBoxSizer *buttonSizer;
};
