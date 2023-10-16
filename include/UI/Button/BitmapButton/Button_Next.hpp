#pragma once

#include "UI/Button/BitmapButton/BitmapButton.hpp"
#include "UI/Data/Data.hpp"

class BitmapNext : public BitmapButton {
  public:
    BitmapNext(wxWindow *parent, wxWindowID id,
               const BitmapData &data = Data::BitmapNext);
};