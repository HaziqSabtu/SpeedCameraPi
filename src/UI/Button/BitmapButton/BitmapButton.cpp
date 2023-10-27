#include <UI/Button/BitmapButton/BitmapButton.hpp>
#include <Utils/wxUtils.hpp>
#include <wx/gtk/colour.h>

/**
 * @brief Construct a new Bitmap Button:: Bitmap Button object
 *
 * @param parent Pointer to the parent window
 * @param id ID of the button
 * @param data BitmapData of the button
 */
BitmapButton::BitmapButton(wxWindow *parent, wxWindowID id,
                           const BitmapData &data)
    : wxPanel(parent, wxID_ANY) {
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

    button = new wxButton(this, id, data.text, wxDefaultPosition, wxDefaultSize,
                          wxBORDER_NONE);

    button->SetBitmap(normal);
    button->SetBitmapPressed(active);
    button->SetBitmapPosition(wxTOP);

    wxBoxSizer *hsizer = new wxBoxSizer(wxHORIZONTAL);
    hsizer->Add(button, 1, wxEXPAND);

    wxFontInfo fontInfo(10);
    fontInfo.Family(wxFONTFAMILY_DEFAULT).FaceName("Roboto").Light();
    wxFont font(fontInfo);

    button->SetFont(font);

    sizer->Add(hsizer, 1, wxEXPAND);

    SetSizer(sizer);
    Fit();
}

/**
 * @brief Update the button to the given state
 *
 * @param state State to update to
 */
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

    if (state == ButtonState::HIDDEN) {
        return setHidden();
    }

    throw new std::runtime_error("Invalid ButtonState");
}

/**
 * @brief Set the button to NORMAL state
 *
 */
void BitmapButton::setNormal() {
    button->SetBitmap(normal);
    button->Enable();
    button->SetBitmapPosition(wxTOP);
    Show();
}

/**
 * @brief Set the button to ACTIVE state
 *
 */
void BitmapButton::setActive() {
    button->SetBitmap(active);
    button->Disable();
    button->SetBitmapPosition(wxTOP);
    Show();
}

/**
 * @brief Set the button to DISABLED state
 *
 */
void BitmapButton::setDisabled() {
    button->SetBitmap(disabled);
    button->Disable();
    button->SetBitmapPosition(wxTOP);
    Show();
}

/**
 * @brief Set the button to HIDDEN state
 *
 */
void BitmapButton::setHidden() { Hide(); }