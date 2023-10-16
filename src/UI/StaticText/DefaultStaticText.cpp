#include <UI/StaticText/DefaultStaticText.hpp>

DefaultStaticText::DefaultStaticText(wxWindow *parent, wxWindowID id,
                                     const StaticTextData &textData)
    : wxStaticText(parent, id, textData.text) {
    SetForegroundColour(textData.textColor);
    SetBackgroundColour(textData.backgroundColor);
    SetFont(AppFont(textData.fontData));
}