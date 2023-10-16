#pragma once

#include <wx/hyperlink.h>
#include <wx/wx.h>

struct HyperLinkData {
    wxString text;
    wxString url;
};

class HyperLinkCtrl : public wxHyperlinkCtrl {
  public:
    HyperLinkCtrl(wxWindow *parent, wxWindowID id, HyperLinkData data)
        : wxHyperlinkCtrl(parent, id, data.text, data.url) {}
};