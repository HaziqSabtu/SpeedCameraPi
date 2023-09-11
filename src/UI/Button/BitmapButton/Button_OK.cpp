#include "UI/Button/BitmapButton/Button_OK.hpp"
#include "UI/Data/Data.hpp"
#include "UI/Data/Theme.hpp"

BitmapOK::BitmapOK(wxWindow *parent, wxWindowID id)
    : BitmapButton(parent, id, Data::BitmapOK) {}