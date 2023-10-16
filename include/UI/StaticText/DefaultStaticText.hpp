#pragma once

#include <UI/Font/Font.hpp>
#include <wx/wx.h>

#define StaticTextDataVector std::vector<StaticTextData>

struct StaticTextData {
    wxColour textColor;
    wxColour backgroundColor;
    wxString text;
    FontData fontData;
};

class DefaultStaticText : public wxStaticText {
  public:
    DefaultStaticText(wxWindow *parent, wxWindowID id,
                      const StaticTextData &textData);

  private:
    const wxColour textColor;
    const wxString text;
};