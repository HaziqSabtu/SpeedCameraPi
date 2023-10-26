#pragma once

#include "wx/wx.h"
#include <Model/Enum.hpp>

/**
 * @brief BitmapButton Data for Type 3
 *
 */
struct BitmapDataT3 {

    // Size of the bitmap
    wxSize size;
    // Filename of the bitmap
    wxString onName;

    // Colours of the bitmap on ACTIVE / NORMAL state
    wxColour bitmapActiveColour;
    // Colours of the background on ACTIVE / NORMAL state
    wxColour backgroundActiveColour;

    // Colours of the bitmap on DISABLED state
    wxColour bitmapDisabledColour;
    // Colours of the background on DISABLED state
    wxColour backgroundDisabledColour;
};

/**
 * @brief BitmapButton Type 3
 * @image html type3state.png
 * @image latex type3state.png
 *
 */
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