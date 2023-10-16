#include "UI/Button/BitmapButton/Button_Save.hpp"
#include "UI/Data/Data.hpp"
#include "UI/Data/Theme.hpp"

BitmapSave::BitmapSave(wxWindow *parent, wxWindowID id, const BitmapData &data)
    : BitmapButton(parent, id, data) {}