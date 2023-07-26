#include "UI/Button/BitmapButton/Button_Preview.hpp"
#include "UI/Theme/Data.hpp"
#include "UI/Theme/Theme.hpp"

BitmapPreview::BitmapPreview(wxWindow *parent, wxWindowID id)
    : BitmapButton(parent, id, Data::BitmapPreview) {}