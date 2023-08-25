#pragma once

#include <wx/wx.h>

class Spacer : public wxStaticText {
  public:
    Spacer(wxWindow *parent, wxWindowID id = wxID_ANY,
           wxSize size = wxSize(10, 10))
        : wxStaticText(parent, id, "", wxDefaultPosition, size) {}
};