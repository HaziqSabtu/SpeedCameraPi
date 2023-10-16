#pragma once

#include "UI/Button/BitmapButton/BitmapButton.hpp"
#include "UI/Data/Data.hpp"

class BitmapReplay : public BitmapButton {
  public:
    BitmapReplay(wxWindow *parent, wxWindowID id,
                 const BitmapData &data = Data::BitmapReplay);
};