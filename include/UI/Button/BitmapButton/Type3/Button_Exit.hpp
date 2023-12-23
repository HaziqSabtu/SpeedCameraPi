#pragma once

#include "UI/Button/BitmapButton/Type3/BitmapButtonT3.hpp"
#include "UI/Data/Data.hpp"
#include "UI/Data/Theme.hpp"
#include <wx/wx.h>

class ButtonExit : public BitmapButtonT3 {
  public:
    ButtonExit(wxWindow *parent, const BitmapDataT3 &data = Data::BitmapT3Exit);
    ~ButtonExit();

  private:
    DECLARE_EVENT_TABLE()
};