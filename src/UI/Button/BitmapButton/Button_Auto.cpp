#include "UI/Button/BitmapButton/Button_Auto.hpp"
#include "UI/Data/Data.hpp"
#include "UI/Data/Theme.hpp"

BitmapAuto::BitmapAuto(wxWindow *parent, wxWindowID id)
    : BitmapButton(parent, id, Data::BitmapAuto) {}