#pragma once

#include "UI/Button/BitmapButton/BitmapButton.hpp"
#include "UI/Data/Data.hpp"

class BitmapColorPicker : public BitmapButton {
  public:
    BitmapColorPicker(wxWindow *parent, wxWindowID id,
                      const BitmapData &data = Data::BitmapColorPicker);
};