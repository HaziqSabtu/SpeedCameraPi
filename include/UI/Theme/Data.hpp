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
    .text = wxT("Start"),
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

const BitmapData BitmapStop = {
    .filename = wxT("Assets/stop_96.png"),
    .size = T::BitmapDefaultSize,
    .normal = T::BitmapNormal,
    .active = T::BitmapActive,
    .disabled = T::BitmapDisabled,
    .text = wxT("Stop"),
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

const BitmapData BitmapL = {
    .filename = wxT("Assets/l_96.png"),
    .size = T::BitmapDefaultSize,
    .normal = T::BitmapNormal,
    .active = T::BitmapActive,
    .disabled = T::BitmapDisabled,
    .text = wxT("Select Left"),
};

const BitmapData BitmapR = {
    .filename = wxT("Assets/r_96.png"),
    .size = T::BitmapDefaultSize,
    .normal = T::BitmapNormal,
    .active = T::BitmapActive,
    .disabled = T::BitmapDisabled,
    .text = wxT("Select Right"),
};

const BitmapData BitmapPreview = {
    .filename = wxT("Assets/preview_96.png"),
    .size = T::BitmapDefaultSize,
    .normal = T::BitmapNormal,
    .active = T::BitmapActive,
    .disabled = T::BitmapDisabled,
    .text = wxT("Preview"),
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

const BitmapDataT2 BitmapT2MagnifyGlass = {
    .size = T::BitmapDefaultSize,
    .onName = "Assets/preview_96.png",
    .onColour = T::BitmapActive,
    .onText = "Stop Preview",
    .offName = "Assets/preview_96.png",
    .offColour = T::BitmapNormal,
    .offText = "Start Preview",
    .disabledName = "Assets/preview_96.png",
    .disabledColour = T::BitmapDisabled,
    .disabledText = "Stop Preview",
};

// TextButton Data
const TextButtonData AcceptTextButton = {
    .text = wxT("Accept"),
    .normalBgColor = T::Primary,
    .normalFgColor = CC::Twitter_ExtExtLightGray,
    .disabledBgColor = CC::Twitter_LightGray,
    .disabledFgColor = CC::Twitter_ExtExtLightGray,
    .size = wxSize(100, 58),
};

const TextButtonData CancelTextButton = {
    .text = wxT("Cancel"),
    .normalBgColor = CC::Twitter_ExtExtLightGray,
    .normalFgColor = T::Text,
    .disabledBgColor = CC::Twitter_LightGray,
    .disabledFgColor = CC::Twitter_ExtExtLightGray,
    .size = wxSize(100, 58),
};

} // namespace Data