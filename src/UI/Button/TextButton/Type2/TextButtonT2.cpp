#include <UI/Button/TextButton/Type2/TextButtonT2.hpp>

TextButtonT2::TextButtonT2(wxWindow *parent, wxWindowID id,
                           const TextButtonDataT2 &data)
    : wxPanel(parent, wxID_ANY, wxDefaultPosition) {
    sizer = new wxBoxSizer(wxHORIZONTAL);

    button = new wxButton(this, id, data.offText, wxDefaultPosition, data.size,
                          wxBORDER_NONE);
    button->SetBackgroundColour(data.offBgColor);
    button->SetForegroundColour(data.offFgColor);

    sizer->Add(button, 1, wxEXPAND | wxALL, 0);

    SetSizer(sizer);
    Layout();

    onText = data.onText;
    offText = data.offText;

    onBgColor = data.onBgColor;
    onFgColor = data.onFgColor;

    offBgColor = data.offBgColor;
    offFgColor = data.offFgColor;
}

void TextButtonT2::update(const ButtonState &buttonState) {
    if (buttonState == ButtonState::ON) {
        return setOn();
    }

    if (buttonState == ButtonState::OFF) {
        return setOff();
    }

    throw std::runtime_error("Invalid button state");
}

void TextButtonT2::setOn() {
    button->SetLabel(onText);
    button->SetBackgroundColour(onBgColor);
    button->SetForegroundColour(onFgColor);
}

void TextButtonT2::setOff() {
    button->SetLabel(offText);
    button->SetBackgroundColour(offBgColor);
    button->SetForegroundColour(offFgColor);
}
