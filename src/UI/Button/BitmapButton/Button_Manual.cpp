#include "UI/Button/BitmapButton/Button_Manual.hpp"
#include "UI/Data/Data.hpp"
#include "UI/Data/Theme.hpp"

BitmapManual::BitmapManual(wxWindow *parent, wxWindowID id)
    : BitmapButton(parent, id, Data::BitmapManual) {}