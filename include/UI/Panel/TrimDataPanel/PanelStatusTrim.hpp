#pragma once

#include "UI/Button/BitmapButton/BitmapButton.hpp"
#include "UI/Button/BitmapButton/Type2/BitmapButtonT2.hpp"
#include "UI/Panel/Common/TextOutlinePanel.hpp"
#include <wx/sizer.h>
#include <wx/wx.h>

class TrimDataMainPanel : public TextOutlinePanel {
  public:
    TrimDataMainPanel(wxWindow *parent);

    void update(const AppState &state);

    BitmapButtonT2 *start_Button;
    BitmapButton *reset_Button;
    BitmapButton *preview_Button;
    BitmapButton *preview2_Button;

  private:
    void OnButtonClicked(wxCommandEvent &e);

    wxBoxSizer *hSizer;
    wxBoxSizer *vSizer;
    wxBoxSizer *buttonSizer;
};
