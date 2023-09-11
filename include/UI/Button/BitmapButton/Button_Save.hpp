#pragma once

#include "UI/Button/BitmapButton/BitmapButton.hpp"
#include "UI/Data/Data.hpp"

class BitmapSave : public BitmapButton {
  public:
    BitmapSave(wxWindow *parent, wxWindowID id,
               const BitmapData &data = Data::BitmapSaveConfig);
};