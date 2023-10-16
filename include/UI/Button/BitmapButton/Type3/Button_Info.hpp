#pragma once

#include "UI/Button/BitmapButton/Type3/BitmapButtonT3.hpp"
#include "UI/Data/Data.hpp"
#include "UI/Data/Theme.hpp"
#include <wx/wx.h>

class ButtonInfo : public BitmapButtonT3 {
  public:
    ButtonInfo(wxWindow *parent, const BitmapDataT3 &data = Data::BitmapT3Info);
    ~ButtonInfo();

  private:
    DECLARE_EVENT_TABLE()
};