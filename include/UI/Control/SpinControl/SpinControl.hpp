#pragma once

#include "UI/Button/BitmapButton/Type3/BitmapButtonT3.hpp"
#include <wx/event.h>
#include <wx/gtk/stattext.h>
#include <wx/gtk/textctrl.h>
#include <wx/sizer.h>
#include <wx/wx.h>

template <typename T>
struct SpinControlData {
    T minValue;
    T maxValue;
    T increment;
    bool isDisabled = false;
};

template <typename T>
class SpinControl : public wxPanel {
  public:
    SpinControl(wxWindow *parent, wxWindowID id, T value);

    T getValue();
    void setValue(T value);

    void setMinValue(T minValue);
    void setMaxValue(T maxValue);

    void setIncrement(T increment);

    void setText(const wxString &text);

    void setSpinData(const SpinControlData<T> &data);

    void setEnabled() {
        plusButton->setEnabled();
        minusButton->setEnabled();
        textCtrl->Enable();
    }

    void setDisabled() {
        plusButton->setDisabled();
        minusButton->setDisabled();
        textCtrl->Disable();
    }

  private:
    wxBoxSizer *mainSizer;

    BitmapButtonT3 *plusButton;
    BitmapButtonT3 *minusButton;
    wxTextCtrl *textCtrl;

    wxStaticText *spacer1;
    wxStaticText *spacer2;

    T value;

    T minValue;
    T maxValue;

    T increment;

    void OnPlusButton(wxCommandEvent &event);
    void OnMinusButton(wxCommandEvent &event);
};

typedef SpinControl<int> SpinControlInt;
typedef SpinControl<double> SpinControlDouble;