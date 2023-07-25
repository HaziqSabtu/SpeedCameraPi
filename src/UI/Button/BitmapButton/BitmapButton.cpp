#include <UI/Button/BitmapButton/BitmapButton.hpp>
#include <Utils/wxUtils.hpp>
#include <wx/gtk/colour.h>

BitmapButton::BitmapButton(wxWindow *parent, wxWindowID id,
                           const BitmapData &data)
    : wxPanel(parent, id) {
    sizer = new wxBoxSizer(wxVERTICAL);

    wxBitmap bit = wxBitmap(data.filename);
    wxSize s = data.size;

    wxBitmap bitmapImage = Utils::resize(bit, s);

    wxColour normalColor = data.normal;
    normal = Utils::recolor(bitmapImage, normalColor);

    wxColour disabledColor = data.disabled;
    disabled = Utils::recolor(bitmapImage, disabledColor);

    wxColour activeColor = data.active;
    active = Utils::recolor(bitmapImage, activeColor);

    button = new wxBitmapButton(this, id, normal, wxDefaultPosition,
                                wxDefaultSize, wxBORDER_NONE);

    button->SetBitmapPressed(active);

    wxBoxSizer *hsizer = new wxBoxSizer(wxHORIZONTAL);
    hsizer->Add(button, 1, wxEXPAND);

    text = new wxStaticText(this, wxID_ANY, data.text);

    wxFontInfo fontInfo(10);
    fontInfo.Family(wxFONTFAMILY_DEFAULT).FaceName("Roboto").Light();
    wxFont font(fontInfo);

    text->SetFont(font);

    sizer->Add(hsizer, 1, wxEXPAND);
    sizer->Add(text, 0, wxALIGN_CENTER_HORIZONTAL);

    SetSizer(sizer);
    Fit();
}

void BitmapButton::update(ButtonState state) {
    if (state == ButtonState::NORMAL) {
        return setNormal();
    }

    if (state == ButtonState::ACTIVE) {
        return setActive();
    }

    if (state == ButtonState::DISABLED) {
        return setDisabled();
    }

    throw new std::runtime_error("Invalid ButtonState");
}

void BitmapButton::setNormal() {
    button->SetBitmap(normal);
    button->Enable();
}

void BitmapButton::setActive() {
    button->SetBitmap(active);
    button->Disable();
}

void BitmapButton::setDisabled() {
    button->SetBitmap(disabled);
    button->Disable();
}