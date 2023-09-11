#include "UI/Button/BitmapButton/Button_Reset.hpp"
#include "UI/Data/Data.hpp"
#include "UI/Data/Theme.hpp"

BitmapReset::BitmapReset(wxWindow *parent, wxWindowID id,
                         const BitmapData &data)
    : BitmapButton(parent, id, data) {}