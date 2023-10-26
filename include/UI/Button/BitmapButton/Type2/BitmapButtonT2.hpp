#pragma once

#include "wx/wx.h"
#include <Model/Enum.hpp>
#include <wx/gtk/bitmap.h>

/**
 * @brief BitmapButton Data for Type 2
 *
 */
struct BitmapDataT2 {
    // Size of the bitmap
    wxSize size;

    // Filename of the bitmap on ON state
    wxString onName;
    // Colours of the bitmap on ON state
    wxColour onColour;
    // Text of the button on ON state
    wxString onText;

    // Filename of the bitmap on OFF state
    wxString offName;
    // Colours of the bitmap on OFF state
    wxColour offColour;
    // Text of the button on OFF state
    wxString offText;

    // Filename of the bitmap on DISABLED state
    wxString disabledName;
    // Colours of the bitmap on DISABLED state
    wxColour disabledColour;
    // Text of the button on DISABLED state
    wxString disabledText;
};

/**
 * @brief BitmapButton Type 2
 * @image html type2state.png
 * @image latex type2state.png
 *
 */
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