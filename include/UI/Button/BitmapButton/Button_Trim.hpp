#pragma once

#include "UI/Button/BitmapButton/BitmapButton.hpp"
#include "UI/Data/Data.hpp"

class BitmapTrim : public BitmapButton {
  public:
    BitmapTrim(wxWindow *parent, wxWindowID id,
               const BitmapData &data = Data::BitmapTrimData);
};