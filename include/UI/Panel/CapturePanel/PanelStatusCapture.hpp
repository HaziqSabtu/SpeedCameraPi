#pragma once

#include "Model/AppState.hpp"
#include "UI/Button/BitmapButton/BitmapButton.hpp"
#include "UI/Button/BitmapButton/Type2/BitmapButtonT2.hpp"
#include "UI/Button/Button_wState.hpp"
#include "UI/Panel/Common/TextOutlinePanel.hpp"
#include <wx/sizer.h>
#include <wx/wx.h>

class CaptureStatusPanel : public TextOutlinePanel {
  public:
    CaptureStatusPanel(wxWindow *parent);

    BitmapButton *Capture_Button;
    BitmapButton *Load_Button;
    BitmapButton *reset_Button;
    BitmapButton *replay_Button;
    BitmapButtonT2 *camera_Button;

    void setPanelState(PanelState state);
    void update(const AppState &state);

  private:
    void OnButtonClicked(wxCommandEvent &e);

    wxBoxSizer *hSizer;
    wxBoxSizer *vSizer;

    wxBoxSizer *leftSizer;
    wxBoxSizer *rightSizer;

    wxBoxSizer *buttonSizer;
};
