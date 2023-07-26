#include "UI/Button/BitmapButton/Button_Target.hpp"
#include "UI/Theme/Data.hpp"
#include "UI/Theme/Theme.hpp"

BitmapTarget::BitmapTarget(wxWindow *parent, wxWindowID id)
    : BitmapButton(parent, id, Data::BitmapTarget) {}