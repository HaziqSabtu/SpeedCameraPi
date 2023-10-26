#pragma once

#include <Model/Enum.hpp>
#include <UI/Data/Theme.hpp>

#include <wx/gdicmn.h>
#include <wx/wx.h>

namespace T = Theme;

/**
 * @brief BitmapButton Data for Type 1
 *
 */
struct BitmapData {
    // Filename of the bitmap
    wxString filename;

    // Size of the bitmap
    wxSize size = T::BitmapDefaultSize;

    // Colours of the bitmap on NORMAL state
    wxColour normal = T::BitmapNormal;

    // Colours of the bitmap on ACTIVE state
    wxColour active = T::BitmapActive;

    // Colours of the bitmap on DISABLED state
    wxColour disabled = T::BitmapDisabled;

    // Text of the button
    wxString text;
};

/**
 * @brief BitmapButton Type 1
 * @image html type1state.png
 * @image latex type1state.png
 *
 */
class BitmapButton : public wxPanel {
  public:
    BitmapButton(wxWindow *parent, wxWindowID id, const BitmapData &data);

    void update(ButtonState state);

    wxButton *button;

  protected:
  private:
    wxBoxSizer *sizer;

    wxBitmap normal;
    wxBitmap active;
    wxBitmap disabled;

    void setNormal();
    void setActive();
    void setDisabled();
    void setHidden();
};