#pragma once

#include <Model/Enum.hpp>
#include <UI/Data/Theme.hpp>

#include <wx/gdicmn.h>
#include <wx/wx.h>

namespace T = Theme;

struct BitmapData {
    wxString filename;
    wxSize size = T::BitmapDefaultSize;

    wxColour normal = T::BitmapNormal;
    wxColour active = T::BitmapActive;
    wxColour disabled = T::BitmapDisabled;

    wxString text;
};

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