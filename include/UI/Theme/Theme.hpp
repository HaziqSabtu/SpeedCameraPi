#pragma once

#include <UI/Theme/ColorCollection.hpp>
#include <wx/gtk/colour.h>

namespace CC = ColorCollection;

namespace Theme {
const wxColour Background = CC::Twitter_ExtExtLightGray;
const wxColour Primary = CC::Twitter_Primary;

const wxColour ButtonBackground = CC::Twitter_ExtLightGray;

// PanelTitle
const wxColour ExitColor = CC::Red_Mandy;
const wxColour SettingsColor = CC::Yellow_Gamboge;
const wxColour InfoColor = CC::Blue_Dodger;

}; // namespace Theme