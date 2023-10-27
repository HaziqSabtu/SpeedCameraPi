#pragma once

#include "Model/AppState.hpp"
#include "wx/wx.h"
#include <UI/Data/Theme.hpp>
#include <wx/string.h>

namespace T = Theme;

struct TextButtonDataT2 {
    wxString onText;
    wxString offText;

    wxColour onBgColor = T::Accent10;
    wxColour onFgColor = T::Primary60;

    wxColour offBgColor = T::GrayDisabled;
    wxColour offFgColor = T::Primary60;

    wxSize size = wxSize(100, 40);
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