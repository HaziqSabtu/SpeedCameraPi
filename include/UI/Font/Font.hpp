#pragma once

#include <wx/wx.h>

enum FontStyle { FONT_NORMAL, FONT_ITALIC, FONT_BOLD, FONT_LIGHT };

struct FontData {
    wxString fontName = "Roboto";
    int fontSize;
    FontStyle fontStyle = FontStyle::FONT_NORMAL;
};

class AppFontInfo : public wxFontInfo {
  public:
    AppFontInfo(const FontData &data);

  private:
    void setFontStyle(FontStyle fontStyle);
};

class AppFont : public wxFont {
  public:
    AppFont(const FontData &data);
};