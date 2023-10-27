#pragma once

#include <Model/AppState.hpp>
#include <UI/Data/Theme.hpp>
#include <wx/wx.h>

namespace T = Theme;

struct TextButtonData {
    wxString text;

    wxColour normalBgColor = T::Primary60;
    wxColour normalFgColor = T::Secondary30;

    wxColour disabledBgColor = T::GrayDisabled;
    wxColour disabledFgColor = T::Primary60;

    wxSize size = wxSize(100, 58);
};

class TextButton : public wxPanel {
  public:
    TextButton(wxWindow *parent, wxWindowID id, const TextButtonData &data);

    void update(const ButtonState &buttonState);

    wxButton *button;

  private:
  protected:
    wxBoxSizer *sizer;

    wxColour normalBgColor;
    wxColour normalFgColor;

    wxColour disabledBgColor;
    wxColour disabledFgColor;

    virtual void setDisabled();
    virtual void setNormal();
};