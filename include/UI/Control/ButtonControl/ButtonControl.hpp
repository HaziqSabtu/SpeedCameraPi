#pragma once

#include "UI/Button/TextButton/Type2/TextButtonT2.hpp"
#include <wx/wx.h>

class ButtonControl : public wxPanel {
  public:
    ButtonControl(wxWindow *parent, wxWindowID id);

    void setValue(bool value);
    bool getValue();

  private:
    bool value = false;

    wxBoxSizer *mainSizer;

    TextButtonT2 *button;

    wxStaticText *spacer1;
    wxStaticText *spacer2;

    void update();
    void onToggle(wxCommandEvent &e);
};