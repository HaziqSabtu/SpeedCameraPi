#pragma once

#include "UI/Button/BitmapButton/BitmapButton.hpp"
#include "UI/Panel/Common/TextOutlinePanel.hpp"
#include <wx/sizer.h>
#include <wx/wx.h>

class CaptureToolsPanel : public TextOutlinePanel {
  public:
    CaptureToolsPanel(wxWindow *parent);

    BitmapButton *save_Button;
    BitmapButton *trim_Button;
    BitmapButton *reset_Button;

    void update(const AppState &state);

  private:
    void OnButtonClicked(wxCommandEvent &e);

    wxBoxSizer *hSizer;
    wxBoxSizer *vSizer;
};
