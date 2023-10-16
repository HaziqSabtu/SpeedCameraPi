#include "Model/AppState.hpp"
#include "Utils/wxUtils.hpp"
#include <UI/Button/BitmapButton/Type3/BitmapButtonT3.hpp>

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

ButtonState BitmapButtonT3::getState() { return state; }

void BitmapButtonT3::setDisabled() { setState(ButtonState::DISABLED); }

void BitmapButtonT3::setEnabled() { setState(ButtonState::NORMAL); }