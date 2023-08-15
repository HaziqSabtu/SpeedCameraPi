#pragma once

#include "UI/Button/BitmapButton/Type2/BitmapButtonT2.hpp"
#include "UI/Theme/Data.hpp"

class BitmapT2Ruler : public BitmapButtonT2 {
  public:
    BitmapT2Ruler(wxWindow *parent, wxWindowID id,
                  BitmapDataT2 = Data::BitmapT2Line);
};