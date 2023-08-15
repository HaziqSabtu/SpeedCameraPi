#pragma once

#include "UI/Button/BitmapButton/BitmapButton.hpp"
#include "UI/Button/BitmapButton/Type2/BitmapButtonT2.hpp"
#include "UI/Panel/Common/TextOutlinePanel.hpp"
#include <wx/sizer.h>
#include <wx/wx.h>

class ResultPreviewStatusPanel : public TextOutlinePanel {
  public:
    ResultPreviewStatusPanel(wxWindow *parent);

    void update(const AppState &state);

    BitmapButtonT2 *box_Button;
    BitmapButtonT2 *intersection_Button;
    BitmapButtonT2 *lanes_Button;
    BitmapButton *replay_Button;

  private:
    void setPanelState(PanelState state);

    void OnButtonClicked(wxCommandEvent &e);

    wxBoxSizer *hSizer;
    wxBoxSizer *vSizer;
    wxBoxSizer *buttonSizer;
};
