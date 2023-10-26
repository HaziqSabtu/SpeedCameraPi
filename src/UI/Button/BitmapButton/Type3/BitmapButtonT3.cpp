#include "Model/AppState.hpp"
#include "Utils/wxUtils.hpp"
#include <UI/Button/BitmapButton/Type3/BitmapButtonT3.hpp>

/**
 * @brief Construct a new Bitmap Button T3:: Bitmap Button T3 object
 *
 * @param parent Pointer to the parent window
 * @param id ID of the button
 * @param data BitmapDataT3 of the button
 */
BitmapButtonT3::BitmapButtonT3(wxWindow *parent, wxWindowID id,
                               const BitmapDataT3 &data)
    : wxButton(parent, id, wxEmptyString, wxDefaultPosition, data.size,
               wxBORDER_NONE) {
    SetBackgroundColour(data.backgroundActiveColour);

    wxBitmap bitmap = wxBitmap(data.onName, wxBITMAP_TYPE_ANY);

    onBitmap = Utils::recolor(bitmap, data.bitmapActiveColour);
    offBitmap = Utils::recolor(bitmap, data.bitmapDisabledColour);

    backgroundActiveColour = data.backgroundActiveColour;
    backgroundDisabledColour = data.backgroundDisabledColour;
    SetBitmapLabel(onBitmap);
}

/**
 * @brief Set the state of the button
 *
 * @param state State to set to
 */
void BitmapButtonT3::setState(ButtonState state) {
    this->state = state;

    if (state == ButtonState::NORMAL) {
        SetBitmapLabel(onBitmap);
        SetBackgroundColour(backgroundActiveColour);
        this->Enable();
    }

    if (state == ButtonState::DISABLED) {
        SetBitmapLabel(offBitmap);
        SetBackgroundColour(backgroundDisabledColour);
        this->Disable();
    }

    Refresh();
}

/**
 * @brief Get the state of the button
 *
 * @return ButtonState State of the button
 */
ButtonState BitmapButtonT3::getState() { return state; }

/**
 * @brief Set the button to disabled state
 *
 */
void BitmapButtonT3::setDisabled() { setState(ButtonState::DISABLED); }

/**
 * @brief Set the button to enabled state
 *
 */
void BitmapButtonT3::setEnabled() { setState(ButtonState::NORMAL); }