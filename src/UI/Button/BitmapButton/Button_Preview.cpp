#include "UI/Button/BitmapButton/Button_Preview.hpp"
#include "UI/Data/Data.hpp"
#include "UI/Data/Theme.hpp"

BitmapPreview::BitmapPreview(wxWindow *parent, wxWindowID id)
    : BitmapButton(parent, id, Data::BitmapPreview) {}