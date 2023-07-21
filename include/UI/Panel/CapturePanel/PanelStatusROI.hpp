#pragma once

#include "UI/Panel/Common/TextOutlinePanel.hpp"
#include <wx/sizer.h>
#include <wx/wx.h>

class ROIStatusPanel : public TextOutlinePanel {
  public:
    ROIStatusPanel(wxWindow *parent);

    wxButton *roi_Button;
    wxButton *reset_Button;

  private:
    void OnButtonClicked(wxCommandEvent &e);

    wxBoxSizer *hSizer;
    wxBoxSizer *vSizer;
};
