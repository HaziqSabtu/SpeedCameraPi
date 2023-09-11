#pragma once

#include "UI/Button/BitmapButton/BitmapButton.hpp"
#include "UI/Data/Data.hpp"

class BitmapPrevious : public BitmapButton {
  public:
    BitmapPrevious(wxWindow *parent, wxWindowID id,
                   const BitmapData &data = Data::BitmapPrevious);
};