#include <UI/Font/Font.hpp>

AppFontInfo::AppFontInfo(const FontData &data) : wxFontInfo(data.fontSize) {
    Family(wxFONTFAMILY_DEFAULT).FaceName("Roboto");
    setFontStyle(data.fontStyle);
};

void AppFontInfo::setFontStyle(FontStyle fontStyle) {
    switch (fontStyle) {
        case FONT_NORMAL: break;
        case FONT_ITALIC: Italic(); break;
        case FONT_BOLD: Bold(); break;
        case FONT_LIGHT: Light(); break;
    }
}

AppFont::AppFont(const FontData &data) : wxFont(AppFontInfo(data)) {}