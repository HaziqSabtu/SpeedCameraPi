#include <UI/Button/BitmapButton/BitmapButton.hpp>
#include <Utils/wxUtils.hpp>

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
    button->SetBitmapDisabled(disabled);

    text = new wxStaticText(this, wxID_ANY, data.text);

    wxFontInfo fontInfo(10);
    fontInfo.Family(wxFONTFAMILY_DEFAULT).FaceName("Roboto").Light();
    wxFont font(fontInfo);

    text->SetFont(font);

    sizer->Add(button, 0, wxALIGN_CENTER_HORIZONTAL);
    sizer->Add(text, 0, wxALIGN_CENTER_HORIZONTAL);

    SetSizer(sizer);
    Fit();
}

void BitmapButton::update(ButtonState state) {
    if (state == ButtonState::NORMAL) {
        setNormal();
    } else if (state == ButtonState::ACTIVE) {
        setActive();
    } else if (state == ButtonState::DISABLED) {
        setDisabled();
    } else
        throw new std::runtime_error("Invalid ButtonState");
}

void BitmapButton::setNormal() { button->SetBitmap(normal); }

void BitmapButton::setActive() { button->SetBitmap(active); }

void BitmapButton::setDisabled() { button->Disable(); }