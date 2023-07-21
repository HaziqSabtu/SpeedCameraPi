#pragma once

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

// PanelTitle
const wxColour ExitColor = CC::Red_Mandy;
const wxString ExitFilename = wxT("exit_24.ico");

const wxColour SettingsColor = CC::Yellow_Gamboge;
const wxString SettingsFilename = wxT("settings_24.ico");

const wxColour InfoColor = CC::Twitter_Primary;
const wxString InfoFilename = wxT("info_24.ico");

// PanelStatus
const wxColour StatusNone = CC::Red_Mandy;
const wxColour StatusOk = CC::Green_Bice;

}; // namespace Theme