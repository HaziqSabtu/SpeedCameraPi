#include "UI/Button/BitmapButton/Button_Target.hpp"
#include "UI/Data/Data.hpp"
#include "UI/Data/Theme.hpp"

BitmapTarget::BitmapTarget(wxWindow *parent, wxWindowID id)
    : BitmapButton(parent, id, Data::BitmapTarget) {}