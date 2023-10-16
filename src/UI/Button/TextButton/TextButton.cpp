#include <UI/Button/TextButton/TextButton.hpp>
#include <wx/font.h>

TextButton::TextButton(wxWindow *parent, wxWindowID id,
                       const TextButtonData &data)
    : wxPanel(parent, wxID_ANY) {
    sizer = new wxBoxSizer(wxVERTICAL);

    normalBgColor = data.normalBgColor;
    normalFgColor = data.normalFgColor;

    disabledBgColor = data.disabledBgColor;
    disabledFgColor = data.disabledFgColor;

    button = new wxButton(this, id, data.text, wxDefaultPosition, data.size);

    wxFontInfo fontInfo(20);
    fontInfo.Family(wxFONTFAMILY_DEFAULT).FaceName("Roboto").Bold();
    wxFont font(fontInfo);

    button->SetFont(font);

    sizer->Add(button, 1, wxEXPAND);

    SetSizer(sizer);
    Fit();

    setNormal();
}

void TextButton::update(const ButtonState &buttonState) {
    if (buttonState == ButtonState::DISABLED) {
        return setDisabled();
    }

    if (buttonState == ButtonState::NORMAL) {
        return setNormal();
    }

    throw std::runtime_error("Unknown button state");
}

void TextButton::setDisabled() {
    button->SetBackgroundColour(disabledBgColor);
    button->SetForegroundColour(disabledFgColor);
    button->Disable();
}

void TextButton::setNormal() {
    button->SetBackgroundColour(normalBgColor);
    button->SetForegroundColour(normalFgColor);
    button->Enable();
}