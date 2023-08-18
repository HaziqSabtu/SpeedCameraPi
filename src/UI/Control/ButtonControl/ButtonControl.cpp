#include "Model/AppState.hpp"
#include "UI/Button/TextButton/Type2/Button_OnOff.hpp"
#include "Utils/Enum.hpp"
#include <UI/Control/ButtonControl/ButtonControl.hpp>

ButtonControl::ButtonControl(wxWindow *parent, wxWindowID id)
    : wxPanel(parent, id) {

    mainSizer = new wxBoxSizer(wxHORIZONTAL);

    button = new OnOffT2TextButton(this, Enum::G_Toggle_Button_ID);

    spacer1 = new wxStaticText(this, wxID_ANY, "", wxDefaultPosition,
                               wxDefaultSize, wxBORDER_NONE);
    spacer2 = new wxStaticText(this, wxID_ANY, "", wxDefaultPosition,
                               wxDefaultSize, wxBORDER_NONE);

    mainSizer->Add(spacer1, 1, wxEXPAND | wxALL, 0);
    mainSizer->Add(button, 2, wxEXPAND | wxALL, 0);
    mainSizer->Add(spacer2, 1, wxEXPAND | wxALL, 0);

    SetSizer(mainSizer);
    Layout();

    // Bind(wxEVT_BUTTON, &ButtonControl::onToggle, this, wxID_ANY);
    Bind(wxEVT_BUTTON, &ButtonControl::onToggle, this,
         Enum::G_Toggle_Button_ID);
}

void ButtonControl::setValue(bool value) { this->value = value; }

bool ButtonControl::getValue() { return value; }

void ButtonControl::update() {
    if (value) {
        button->update(ButtonState::ON);
    } else {
        button->update(ButtonState::OFF);
    }
}

void ButtonControl::onToggle(wxCommandEvent &e) {
    value = !value;
    update();
}