#pragma once

#include "Model/AppState.hpp"
#include <wx/wx.h>

class TB : public wxPanel {
  public:
    TB(wxWindow *parent, wxWindowID id = wxID_ANY,
       const wxPoint &pos = wxDefaultPosition,
       const wxSize &size = wxDefaultSize, long style = wxTAB_TRAVERSAL,
       const wxString &name = wxPanelNameStr);
    ~TB();

    wxBitmap recolor(wxBitmap &b, wxColour &c);
    wxBitmap rescale(wxBitmap &b, wxSize &s);

    void update(ButtonState state);

    wxBitmap normal;
    wxBitmap active;
    wxBitmap disabled;

    wxButton *b;

  protected:
    wxBoxSizer *hSizer;
    wxBoxSizer *vSizer;

    wxStaticText *t;

    void setNormal();
    void setActive();
    void setDisabled();
};
