#pragma once

#include "UI/Button/BitmapButton/BitmapButton.hpp"
#include "UI/Button/BitmapButton/Type2/BitmapButtonT2.hpp"
#include "UI/Button/TextButton/TextButton.hpp"
#include <UI/Theme/Theme.hpp>
#include <wx/gdicmn.h>

namespace T = Theme;

namespace Data {

// App General Data
const wxString AppName = wxT("SpeedCameraPi");
const wxString AppIcon = wxT("Assets/speed_64.ico");

// BitmapButton Data
const BitmapData BitmapCapture = {
    .filename = wxT("Assets/cam_96.png"),
    .size = T::BitmapDefaultSize,
    .normal = T::BitmapNormal,
    .active = T::BitmapActive,
    .disabled = T::BitmapDisabled,
    .text = wxT("Capture"),
};

const BitmapData BitmapLoad = {
    .filename = wxT("Assets/doc_96.png"),
    .size = T::BitmapDefaultSize,
    .normal = T::BitmapNormal,
    .active = T::BitmapActive,
    .disabled = T::BitmapDisabled,
    .text = wxT("Load"),
};

const BitmapData BitmapReplay = {
    .filename = wxT("Assets/repeat_96.png"),
    .size = T::BitmapDefaultSize,
    .normal = T::BitmapNormal,
    .active = T::BitmapActive,
    .disabled = T::BitmapDisabled,
    .text = wxT("Replay"),
};

const BitmapData BitmapRemove = {
    .filename = wxT("Assets/remove_96.png"),
    .size = T::BitmapDefaultSize,
    .normal = T::BitmapNormal,
    .active = T::BitmapActive,
    .disabled = T::BitmapDisabled,
    .text = wxT("Remove"),
};

const BitmapData BitmapRoad = {
    .filename = wxT("Assets/road_96.png"),
    .size = T::BitmapDefaultSize,
    .normal = T::BitmapNormal,
    .active = T::BitmapActive,
    .disabled = T::BitmapDisabled,
    .text = wxT("Calibrate"),
};

const BitmapData BitmapROI = {
    .filename = wxT("Assets/roi_96.png"),
    .size = T::BitmapDefaultSize,
    .normal = T::BitmapNormal,
    .active = T::BitmapActive,
    .disabled = T::BitmapDisabled,
    .text = wxT("Select ROI"),
};

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

const BitmapData BitmapSave = {
    .filename = wxT("Assets/floppy_96.png"),
    .size = T::BitmapDefaultSize,
    .normal = T::BitmapNormal,
    .active = T::BitmapActive,
    .disabled = T::BitmapDisabled,
    .text = wxT("Save To Config"),
};

const BitmapData BitmapSelectBlue = {
    .filename = wxT("Assets/colorPicker_96.png"),
    .size = T::BitmapDefaultSize,
    .normal = T::BitmapNormal,
    .active = T::BitmapActive,
    .disabled = T::BitmapDisabled,
    .text = wxT("Select Blue"),
};

const BitmapData BitmapSelectYellow = {
    .filename = wxT("Assets/colorPicker_96.png"),
    .size = T::BitmapDefaultSize,
    .normal = T::BitmapNormal,
    .active = T::BitmapActive,
    .disabled = T::BitmapDisabled,
    .text = wxT("Select Yellow"),
};

const BitmapData BitmapReset = {
    .filename = wxT("Assets/reset_96.png"),
    .size = T::BitmapDefaultSize,
    .normal = T::BitmapNormal,
    .active = T::BitmapActive,
    .disabled = T::BitmapDisabled,
    .text = wxT("Reset"),
};
const BitmapData BitmapRestore = {
    .filename = wxT("Assets/reset_96.png"),
    .size = T::BitmapDefaultSize,
    .normal = T::BitmapNormal,
    .active = T::BitmapActive,
    .disabled = T::BitmapDisabled,
    .text = wxT("Restore Default"),
};

const BitmapData BitmapAccept = {
    .filename = wxT("Assets/tick_96.png"),
    .size = T::BitmapDefaultSize,
    .normal = T::BitmapNormal,
    .active = T::BitmapActive,
    .disabled = T::BitmapDisabled,
    .text = wxT("Accept"),
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
    .onName = "Assets/stop_96.png",
    .onColour = T::BitmapActive,
    .onText = "Stop Calibration",
    .offName = "Assets/start_96.png",
    .offColour = T::BitmapNormal,
    .offText = "Start Calibration",
    .disabledName = "Assets/start_96.png",
    .disabledColour = T::BitmapDisabled,
    .disabledText = "Start Calibration",
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

const BitmapDataT2 BitmapT2Box = {
    .size = T::BitmapDefaultSize,
    .onName = "Assets/roi_96.png",
    .onColour = T::BitmapActive,
    .onText = "Hide Box",
    .offName = "Assets/roi_96.png",
    .offColour = T::BitmapNormal,
    .offText = "Show Box",
    .disabledName = "Assets/roi_96.png",
    .disabledColour = T::BitmapDisabled,
    .disabledText = "Show Box",
};

const BitmapDataT2 BitmapT2Line = {
    .size = T::BitmapDefaultSize,
    .onName = "Assets/ruler_96.png",
    .onColour = T::BitmapActive,
    .onText = "Hide Line",
    .offName = "Assets/ruler_96.png",
    .offColour = T::BitmapNormal,
    .offText = "Show Line",
    .disabledName = "Assets/ruler_96.png",
    .disabledColour = T::BitmapDisabled,
    .disabledText = "Show Line",
};

const BitmapDataT2 BitmapT2Lanes = {
    .size = T::BitmapDefaultSize,
    .onName = "Assets/road_96.png",
    .onColour = T::BitmapActive,
    .onText = "Hide Lanes",
    .offName = "Assets/road_96.png",
    .offColour = T::BitmapNormal,
    .offText = "Show Lanes",
    .disabledName = "Assets/road_96.png",
    .disabledColour = T::BitmapDisabled,
    .disabledText = "Show Lanes",
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

const TextButtonData MeasureTextButton = {
    .text = wxT("Measure"),
    .normalBgColor = T::Primary,
    .normalFgColor = CC::Twitter_ExtExtLightGray,
    .disabledBgColor = CC::Twitter_LightGray,
    .disabledFgColor = CC::Twitter_ExtExtLightGray,
    .size = wxSize(100, 58),
};

} // namespace Data