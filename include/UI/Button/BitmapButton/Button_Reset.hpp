#pragma once

#include "UI/Button/BitmapButton/BitmapButton.hpp"
#include "UI/Theme/Data.hpp"

class BitmapReset : public BitmapButton {
  public:
    BitmapReset(wxWindow *parent, wxWindowID id,
                const BitmapData &data = Data::BitmapReset);
};