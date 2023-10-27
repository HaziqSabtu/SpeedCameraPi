#pragma once

#include "UI/Button/BitmapButton/BitmapButton.hpp"
#include "UI/Button/BitmapButton/Type2/BitmapButtonT2.hpp"
#include "UI/Panel/Common/TextOutlinePanel.hpp"
#include <wx/sizer.h>
#include <wx/wx.h>

class TrimButtonMain : public TextOutlinePanel {
  public:
    TrimButtonMain(wxWindow *parent);

    void update(const AppState &state);

    BitmapButtonT2 *Start_Button;
    BitmapButton *Preview_Button;
    BitmapButton *PreviewInThread_Button;

  private:
    void OnButtonClicked(wxCommandEvent &e);

    wxBoxSizer *buttonSizer;
};
