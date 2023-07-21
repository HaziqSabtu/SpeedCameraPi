#pragma once

#include "UI/Button/Button_wState.hpp"
#include "UI/Panel/Common/TextOutlinePanel.hpp"
#include <wx/sizer.h>
#include <wx/wx.h>

class CaptureStatusPanel : public TextOutlinePanel {
  public:
    CaptureStatusPanel(wxWindow *parent);

    ButtonWState *Capture_Button;
    ButtonWState *Load_Button;
    wxButton *reset_Button;

  private:
    void OnButtonClicked(wxCommandEvent &e);

    wxBoxSizer *hSizer;
    wxBoxSizer *vSizer;
};
