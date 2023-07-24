#include "UI/Theme/Theme.hpp"
#include <UI/Button/BitmapButton/Button_Capture.hpp>

BitmapCapture::BitmapCapture(wxWindow *parent, wxWindowID id)
    : BitmapButton(parent, id, Theme::BitmapCapture) {}