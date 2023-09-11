#include "UI/Data/Data.hpp"
#include "UI/Data/Theme.hpp"
#include <UI/Button/BitmapButton/Bitmap_Calibration.hpp>

BitmapCalibration::BitmapCalibration(wxWindow *parent, wxWindowID id)
    : BitmapButton(parent, id, Data::BitmapStart) {}