#include "UI/Theme/Data.hpp"
#include "UI/Theme/Theme.hpp"
#include "Utils/Enum.hpp"
#include <UI/Control/SpinControl/SpinControl.hpp>
#include <wx/gtk/stattext.h>
#include <wx/gtk/textctrl.h>

template <typename T>
SpinControl<T>::SpinControl(wxWindow *parent, wxWindowID id, T value)
    : wxPanel(parent, id), value(value) {
    plusButton =
        new BitmapButtonT3(this, Enum::G_Plus_Button_ID, Data::BitmapT3Plus);
    minusButton =
        new BitmapButtonT3(this, Enum::G_Minus_Button_ID, Data::BitmapT3Minus);

    textCtrl =
        new wxTextCtrl(this, wxID_ANY, std::to_string(value), wxDefaultPosition,
                       wxDefaultSize, wxTE_READONLY | wxTE_CENTRE);
    // textCtrl->SetBackgroundColour(Theme::SettingsTextBackground);

    spacer1 = new wxStaticText(this, wxID_ANY, "", wxDefaultPosition,
                               wxDefaultSize, wxALIGN_CENTER);
    spacer2 = new wxStaticText(this, wxID_ANY, "", wxDefaultPosition,
                               wxSize(100, 40));

    mainSizer = new wxBoxSizer(wxHORIZONTAL);
    mainSizer->Add(spacer1, 1, wxALIGN_CENTER_VERTICAL);
    mainSizer->Add(minusButton, 0, wxRIGHT, 5);
    mainSizer->Add(textCtrl, 2, wxEXPAND | wxRIGHT | wxLEFT, 5);
    mainSizer->Add(plusButton, 0, wxLEFT, 5);
    mainSizer->Add(spacer2, 1, wxALIGN_CENTER_VERTICAL);

    SetSizer(mainSizer);

    // Bind Events
    Bind(wxEVT_BUTTON, &SpinControl<T>::OnPlusButton, this,
         Enum::G_Plus_Button_ID);
    Bind(wxEVT_BUTTON, &SpinControl<T>::OnMinusButton, this,
         Enum::G_Minus_Button_ID);
}

template <typename T>
void SpinControl<T>::setText(const wxString &text) {
    spacer1->SetLabelText(text);
}

template <typename T>
T SpinControl<T>::getValue() {
    return value;
}

template <typename T>
void SpinControl<T>::setValue(T value) {
    this->value = value;
    textCtrl->SetValue(std::to_string(value));
}

template <typename T>
void SpinControl<T>::setMinValue(T minValue) {
    this->minValue = minValue;
}

template <typename T>
void SpinControl<T>::setMaxValue(T maxValue) {
    this->maxValue = maxValue;
}

template <typename T>
void SpinControl<T>::setIncrement(T increment) {
    this->increment = increment;
}

template <typename T>
void SpinControl<T>::setSpinData(const SpinControlData<T> &data) {
    minValue = data.minValue;
    maxValue = data.maxValue;
    increment = data.increment;

    data.isDisabled ? setDisabled() : setEnabled();
}

template <typename T>
void SpinControl<T>::OnPlusButton(wxCommandEvent &e) {
    if (value < maxValue) {
        T newValue = value + increment;
        value = newValue > maxValue ? maxValue : newValue;
        textCtrl->SetValue(std::to_string(value));
    }

    e.Skip();
}

template <typename T>
void SpinControl<T>::OnMinusButton(wxCommandEvent &e) {
    if (value > minValue) {
        T newValue = value - increment;
        value = newValue < minValue ? minValue : newValue;
        textCtrl->SetValue(std::to_string(value));
    }

    e.Skip();
}

template class SpinControl<int>;    // Explicit instantiation for int
template class SpinControl<double>; // Explicit instantiation for double
