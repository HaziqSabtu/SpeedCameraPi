#include "Utils/wxUtils.hpp"
#include <UI/Button/BitmapButton/Type2/BitmapButtonT2.hpp>
#include <wx/gdicmn.h>
#include <wx/tracker.h>

BitmapButtonT2::BitmapButtonT2(wxWindow *parent, wxWindowID id,
                               const BitmapDataT2 &data)
    : wxPanel(parent, wxID_ANY) {
    sizer = new wxBoxSizer(wxVERTICAL);

    onText = data.onText;
    offText = data.offText;
    disabledText = data.disabledText;

    onBitmap = wxBitmap(data.onName, wxBITMAP_TYPE_ANY);
    offBitmap = wxBitmap(data.offName, wxBITMAP_TYPE_ANY);
    disabledBitmap = wxBitmap(data.disabledName, wxBITMAP_TYPE_ANY);

    wxSize s = data.size;

    wxColour onColour = data.onColour;
    onBitmap = Utils::resize(onBitmap, s);
    onBitmap = Utils::recolor(onBitmap, onColour);

    wxColour offColour = data.offColour;
    offBitmap = Utils::resize(offBitmap, s);
    offBitmap = Utils::recolor(offBitmap, offColour);

    wxColour disabledColour = data.disabledColour;
    disabledBitmap = Utils::resize(disabledBitmap, s);
    disabledBitmap = Utils::recolor(disabledBitmap, disabledColour);

    button = new wxButton(this, id, data.offText, wxDefaultPosition,
                          wxDefaultSize, wxBORDER_NONE);
    button->SetBitmap(offBitmap);
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

    this->state = ButtonState::OFF;
}

void BitmapButtonT2::update(ButtonState state) {
    if (state == ButtonState::ON) {
        this->Show();
        return setOn();
    }

    if (state == ButtonState::OFF) {
        this->Show();
        return setOff();
    }

    if (state == ButtonState::DISABLED) {
        this->Show();
        return setDisabled();
    }

    if (state == ButtonState::HIDDEN) {
        this->Hide();
        return;
    }

    throw std::invalid_argument("Invalid ButtonState");
}

void BitmapButtonT2::setOn() {
    button->SetBitmapLabel(onBitmap);
    button->Enable();

    button->SetLabel(onText);

    button->SetBitmapPosition(wxTOP);

    this->state = ButtonState::ON;
}

void BitmapButtonT2::setOff() {
    button->SetBitmapLabel(offBitmap);
    button->Enable();

    button->SetLabel(offText);

    button->SetBitmapPosition(wxTOP);

    this->state = ButtonState::OFF;
}

void BitmapButtonT2::setDisabled() {
    button->SetBitmapLabel(disabledBitmap);
    button->Disable();

    button->SetLabel(disabledText);

    button->SetBitmapPosition(wxTOP);

    this->state = ButtonState::DISABLED;
}

ButtonState BitmapButtonT2::getState() { return state; }