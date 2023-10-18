#pragma once

#include "wx/wx.h"
#include <Model/Enum.hpp>

struct BitmapDataT3 {
    wxSize size;
    wxString onName;

    wxColour bitmapActiveColour;
    wxColour backgroundActiveColour;

    wxColour bitmapDisabledColour;
    wxColour backgroundDisabledColour;
};

class BitmapButtonT3 : public wxButton {
  public:
    BitmapButtonT3(wxWindow *parent, wxWindowID id, const BitmapDataT3 &data);

    void setState(ButtonState state);
    ButtonState getState();

    void setDisabled();
    void setEnabled();

  protected:
    wxBitmap onBitmap;
    wxBitmap offBitmap;

    wxColour backgroundActiveColour;
    wxColour backgroundDisabledColour;

    ButtonState state = ButtonState::NORMAL;
};