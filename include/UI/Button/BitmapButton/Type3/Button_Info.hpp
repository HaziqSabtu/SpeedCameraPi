#pragma once

#include "UI/Button/BitmapButton/Type3/BitmapButtonT3.hpp"
#include "UI/Theme/Data.hpp"
#include "UI/Theme/Theme.hpp"
#include <wx/wx.h>

class ButtonInfo : public BitmapButtonT3 {
  public:
    ButtonInfo(wxWindow *parent, const BitmapDataT3 &data = Data::BitmapT3Info);
    ~ButtonInfo();

  private:
    DECLARE_EVENT_TABLE()
};