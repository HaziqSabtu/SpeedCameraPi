#pragma once

#include "UI/Button/BitmapButton/BitmapButton.hpp"
#include <UI/Theme/ColorCollection.hpp>
#include <wx/gtk/colour.h>

namespace CC = ColorCollection;

namespace Theme {
const wxColour Background = CC::Twitter_ExtExtLightGray;
const wxColour Primary = CC::Twitter_Primary;
const wxColour Text = CC::Twitter_Secondary;

const wxColour ButtonBackground = CC::Twitter_ExtLightGray;
const wxColour ButtonText = CC::Twitter_Secondary;

const wxColour StatusBackground = CC::Twitter_Secondary;
const wxColour StatusText = CC::Twitter_ExtExtLightGray;

const wxColour ImageBackground = CC::Twitter_Secondary;
const wxColour ImageText = CC::Twitter_ExtExtLightGray;
const wxString noImageIcon = wxT("Assets/noImage_96.png");

const wxColour BitmapNormal = CC::Twitter_Secondary;
const wxColour BitmapActive = CC::Twitter_Primary;
const wxColour BitmapDisabled = CC::Twitter_LightGray;
const wxSize BitmapDefaultSize = wxSize(50, 50);

// PanelTitle
const wxColour ExitColor = CC::Red_Mandy;
const wxString ExitFilename = wxT("Assets/exit_24.ico");

const wxColour SettingsColor = CC::Yellow_Gamboge;
const wxString SettingsFilename = wxT("Assets/settings_24.ico");

const wxColour InfoColor = CC::Twitter_Primary;
const wxString InfoFilename = wxT("Assets/info_24.ico");

// PanelStatus
const wxColour StatusNone = CC::Red_Mandy;
const wxColour StatusOk = CC::Green_Bice;

}; // namespace Theme