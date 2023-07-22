#pragma once

#include "UI/Panel/Common/TextOutlinePanel.hpp"
#include <wx/sizer.h>
#include <wx/wx.h>

class CalibrationMainStatusPanel : public TextOutlinePanel {
  public:
    CalibrationMainStatusPanel(wxWindow *parent);

    wxButton *calibrate_Button;
    wxButton *reset_Button;

  private:
    void OnButtonClicked(wxCommandEvent &e);

    wxBoxSizer *hSizer;
    wxBoxSizer *vSizer;
};
