#include "UI/Button/BitmapButton/Button_Cancel.hpp"
#include "UI/Data/Data.hpp"
#include "UI/Data/Theme.hpp"

BitmapCancel::BitmapCancel(wxWindow *parent, wxWindowID id)
    : BitmapButton(parent, id, Data::BitmapCancel) {}