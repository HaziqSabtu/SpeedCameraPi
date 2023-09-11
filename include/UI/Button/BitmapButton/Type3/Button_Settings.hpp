#pragma once

#include "UI/Data/Data.hpp"
#include "UI/Data/Theme.hpp"
#include <wx/wx.h>

class ButtonSettings : public BitmapButtonT3 {
  public:
    ButtonSettings(wxWindow *parent,
                   const BitmapDataT3 &data = Data::BitmapT3Settings);
    ~ButtonSettings();

  private:
    DECLARE_EVENT_TABLE()
};