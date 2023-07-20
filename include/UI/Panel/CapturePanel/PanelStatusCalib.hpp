#pragma once

#include "UI/Panel/Common/TextOutlinePanel.hpp"
#include <wx/sizer.h>
#include <wx/wx.h>

class CalibrationStatusPanel : public TextOutlinePanel {
  public:
    CalibrationStatusPanel(wxWindow *parent);

  private:
    void OnButtonClicked(wxCommandEvent &e);

    wxButton *calibrate_Button;
    wxButton *reset_Button;

    wxBoxSizer *hSizer;
    wxBoxSizer *vSizer;
};
