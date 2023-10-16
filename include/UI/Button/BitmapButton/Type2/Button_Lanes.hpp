#pragma once

#include "UI/Button/BitmapButton/Type2/BitmapButtonT2.hpp"
#include "UI/Data/Data.hpp"

class BitmapT2Lanes : public BitmapButtonT2 {
  public:
    BitmapT2Lanes(wxWindow *parent, wxWindowID id,
                  BitmapDataT2 = Data::BitmapT2Lanes);
};