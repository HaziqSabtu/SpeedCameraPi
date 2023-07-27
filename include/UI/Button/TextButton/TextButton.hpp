#pragma once

#include "Model/AppState.hpp"
#include "wx/wx.h"

struct TextButtonData {
    wxString text;

    wxColour normalBgColor;
    wxColour normalFgColor;

    wxColour disabledBgColor;
    wxColour disabledFgColor;

    wxSize size;
};

class TextButton : public wxPanel {
  public:
    TextButton(wxWindow *parent, wxWindowID id, const TextButtonData &data);

    void update(const ButtonState &buttonState);

    wxButton *button;

  protected:
  private:
    wxBoxSizer *sizer;

    wxColour normalBgColor;
    wxColour normalFgColor;

    wxColour disabledBgColor;
    wxColour disabledFgColor;

    void setDisabled();
    void setNormal();
};