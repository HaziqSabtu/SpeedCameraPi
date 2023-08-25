#pragma once

#include "Model/AppState.hpp"
#include <wx/gdicmn.h>
#include <wx/wx.h>

struct BitmapData {
    wxString filename;
    wxSize size;

    wxColour normal;
    wxColour active;
    wxColour disabled;

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