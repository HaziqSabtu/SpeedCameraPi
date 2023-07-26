#include "UI/Button/BitmapButton/Button_ColorPicker.hpp"
#include "UI/Theme/Data.hpp"
#include "UI/Theme/Theme.hpp"

BitmapColorPicker::BitmapColorPicker(wxWindow *parent, wxWindowID id)
    : BitmapButton(parent, id, Data::BitmapColorPicker) {}