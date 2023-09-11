#include "UI/Button/BitmapButton/Button_ColorPicker.hpp"
#include "UI/Data/Data.hpp"
#include "UI/Data/Theme.hpp"

BitmapColorPicker::BitmapColorPicker(wxWindow *parent, wxWindowID id,
                                     const BitmapData &data)
    : BitmapButton(parent, id, data) {}