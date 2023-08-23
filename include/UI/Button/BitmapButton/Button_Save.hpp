#pragma once

#include "UI/Button/BitmapButton/BitmapButton.hpp"
#include "UI/Theme/Data.hpp"

class BitmapSave : public BitmapButton {
  public:
    BitmapSave(wxWindow *parent, wxWindowID id,
               const BitmapData &data = Data::BitmapSaveConfig);
};