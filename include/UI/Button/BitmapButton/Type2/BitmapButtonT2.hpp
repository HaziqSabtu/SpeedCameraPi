#pragma once

#include "wx/wx.h"
#include <Model/Enum.hpp>
#include <wx/gtk/bitmap.h>

struct BitmapDataT2 {
    wxSize size;

    wxString onName;
    wxColour onColour;
    wxString onText;

    wxString offName;
    wxColour offColour;
    wxString offText;

    wxString disabledName;
    wxColour disabledColour;
    wxString disabledText;
};

class BitmapButtonT2 : public wxPanel {
  public:
    BitmapButtonT2(wxWindow *parent, wxWindowID id, const BitmapDataT2 &data);

    void update(ButtonState state);

    ButtonState getState();

    wxButton *button;

  protected:
  private:
    wxBoxSizer *sizer;

    wxBitmap onBitmap;
    wxBitmap offBitmap;
    wxBitmap disabledBitmap;

    wxString onText;
    wxString offText;
    wxString disabledText;

    ButtonState state;

    void setOn();
    void setOff();
    void setDisabled();
};