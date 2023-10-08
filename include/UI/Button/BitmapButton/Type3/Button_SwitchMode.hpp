#pragma once

#include "UI/Data/Data.hpp"
#include "UI/Data/Theme.hpp"
#include <wx/wx.h>

class ButtonSwitchMode : public BitmapButtonT3 {
  public:
    ButtonSwitchMode(wxWindow *parent,
                     const BitmapDataT3 &data = Data::BitmapT3Replace);
    ~ButtonSwitchMode();

  private:
    DECLARE_EVENT_TABLE()
};