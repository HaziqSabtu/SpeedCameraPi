#pragma once

#include "UI/Button/BitmapButton/Type2/BitmapButtonT2.hpp"
#include <UI/Theme/Theme.hpp>

namespace T = Theme;

namespace Data {

// BitmapButton Data
const BitmapData BitmapStart = {
    .filename = wxT("Assets/start_96.png"),
    .size = T::BitmapDefaultSize,
    .normal = T::BitmapNormal,
    .active = T::BitmapActive,
    .disabled = T::BitmapDisabled,
    .text = wxT("Capture"),
};

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

const BitmapDataT2 BitmapT2Calibration = {
    .size = T::BitmapDefaultSize,
    .onName = "Assets/start_96.png",
    .onColour = T::BitmapActive,
    .onText = "Start Calibration",
    .offName = "Assets/cancel_96.png",
    .offColour = T::BitmapNormal,
    .offText = "Cancel Calibration",
    .disabledName = "Assets/cancel_96.png",
    .disabledColour = T::BitmapDisabled,
    .disabledText = "Auto Calibration Off",
};

} // namespace Data