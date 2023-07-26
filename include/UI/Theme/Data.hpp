#pragma once

#include "UI/Button/BitmapButton/Type2/BitmapButtonT2.hpp"
#include "UI/Button/TextButton/TextButton.hpp"
#include <UI/Theme/Theme.hpp>
#include <wx/gdicmn.h>

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

const BitmapData BitmapOK = {
    .filename = wxT("Assets/accept_96.png"),
    .size = T::BitmapDefaultSize,
    .normal = T::BitmapNormal,
    .active = T::BitmapActive,
    .disabled = T::BitmapDisabled,
    .text = wxT("OK"),
};

const BitmapData BitmapCancel = {
    .filename = wxT("Assets/cancel_96.png"),
    .size = T::BitmapDefaultSize,
    .normal = T::BitmapNormal,
    .active = T::BitmapActive,
    .disabled = T::BitmapDisabled,
    .text = wxT("Cancel"),
};

const BitmapData BitmapTarget = {
    .filename = wxT("Assets/target_96.png"),
    .size = T::BitmapDefaultSize,
    .normal = T::BitmapNormal,
    .active = T::BitmapActive,
    .disabled = T::BitmapDisabled,
    .text = wxT("Select Point"),
};

const BitmapData BitmapColorPicker = {
    .filename = wxT("Assets/colorPicker_96.png"),
    .size = T::BitmapDefaultSize,
    .normal = T::BitmapNormal,
    .active = T::BitmapActive,
    .disabled = T::BitmapDisabled,
    .text = wxT("Recalibrate Color"),
};

const BitmapData BitmapUser = {
    .filename = wxT("Assets/user_96.png"),
    .size = T::BitmapDefaultSize,
    .normal = T::BitmapNormal,
    .active = T::BitmapActive,
    .disabled = T::BitmapDisabled,
    .text = wxT("Manual Calibration"),
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

// TextButton Data
const TextButtonData AcceptTextButton = {
    .text = wxT("Accept"),
    .bgColor = T::Primary,
    .fgColor = CC::Twitter_ExtExtLightGray,
    .size = wxSize(100, 50),
};

const TextButtonData CancelTextButton = {
    .text = wxT("Cancel"),
    .bgColor = CC::Twitter_ExtExtLightGray,
    .fgColor = T::Text,
    .size = wxSize(100, 50),
};

} // namespace Data