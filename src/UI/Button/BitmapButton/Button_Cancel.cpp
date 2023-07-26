#include "UI/Button/BitmapButton/Button_Cancel.hpp"
#include "UI/Theme/Data.hpp"
#include "UI/Theme/Theme.hpp"

BitmapCancel::BitmapCancel(wxWindow *parent, wxWindowID id)
    : BitmapButton(parent, id, Data::BitmapCancel) {}