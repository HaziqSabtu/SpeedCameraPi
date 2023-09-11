#include "UI/Button/BitmapButton/Button_Roi.hpp"
#include "UI/Data/Data.hpp"

BitmapRoi::BitmapRoi(wxWindow *parent, wxWindowID id)
    : BitmapButton(parent, id, Data::BitmapROI) {}