#pragma once

#include "wx/wx.h"

struct TextButtonData {
    wxString text;

    wxColour bgColor;
    wxColour fgColor;

    wxSize size;
};

class TextButton : public wxPanel {
  public:
    TextButton(wxWindow *parent, wxWindowID id, const TextButtonData &data);

    void update(bool state);

    wxButton *button;

  protected:
  private:
    wxBoxSizer *sizer;

    void setNormal();
    void setDisabled();
};