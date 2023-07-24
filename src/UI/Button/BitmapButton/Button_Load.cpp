#include "UI/Button/BitmapButton/Button_Load.hpp"
#include "UI/Theme/Theme.hpp"

BitmapLoad::BitmapLoad(wxWindow *parent, wxWindowID id)
    : BitmapButton(parent, id, Theme::BitmapLoad) {}