#pragma once

#include "Model/AppState.hpp"
#include "wx/wx.h"
#include <wx/string.h>

struct TextButtonDataT2 {
    wxString onText;
    wxString offText;

    wxColour onBgColor;
    wxColour onFgColor;

    wxColour offBgColor;
    wxColour offFgColor;

    wxSize size;
};

class TextButtonT2 : public wxPanel {
  public:
    TextButtonT2(wxWindow *parent, wxWindowID id, const TextButtonDataT2 &data);

    void update(const ButtonState &buttonState);

    wxButton *button;

  protected:
  private:
    wxBoxSizer *sizer;

    wxString onText;
    wxString offText;

    wxColour onBgColor;
    wxColour onFgColor;

    wxColour offBgColor;
    wxColour offFgColor;

    void setOn();
    void setOff();
};