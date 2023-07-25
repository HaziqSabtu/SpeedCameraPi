#pragma once

#include "UI/Button/BitmapButton/Type2/BitmapButtonT2.hpp"
#include <UI/Theme/Theme.hpp>

namespace T = Theme;

namespace Data {
// BitmapButtonT2 Data
const BitmapDataT2 BitmapT2Camera = {
    .size = T::BitmapDefaultSize,
    .onName = "Assets/eyeOn_96.png",
    .onColour = T::BitmapActive,
    .onText = "Camera On",
    .offName = "Assets/eyeOff_96.png",
    .offColour = T::BitmapNormal,
    .offText = "Camera Off",
    .disabledName = "Assets/eyeOff_96.png",
    .disabledColour = T::BitmapDisabled,
    .disabledText = "Camera Off",
};
} // namespace Data