#pragma once

#include "UI/Button/BitmapButton/BitmapButton.hpp"
#include "UI/Font/Font.hpp"
#include <UI/Data/ColorCollection.hpp>
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
const wxColour TitleActiveBitmap = CC::Twitter_ExtExtLightGray;

const wxColour ExitColor = CC::Red_Mandy;
const wxColour SettingsColor = CC::Yellow_Gamboge;
const wxColour InfoColor = CC::Twitter_Primary;

const wxColour TitleDisabledBitmap = CC::Twitter_LightGray;
const wxColour TitleDisabledBg = CC::Twitter_ExtExtLightGray;

// Settings
const wxSize SettingsTextDefaultSize = wxSize(200, 20);
const wxColour SettingsTextBackground = CC::Twitter_ExtExtLightGray;

const wxColour SettingsButtonBackground = CC::Twitter_ExtExtLightGray;
const wxColour SettingsButtonNormal = CC::Twitter_Secondary;
const wxColour SettingsButtonDisabled = CC::Twitter_LightGray;

const FontData TitleFontData = {
    .fontSize = 20,
    .fontStyle = FontStyle::FONT_BOLD,
};

const FontData TitleChildFontData = {
    .fontSize = 13,
    .fontStyle = FontStyle::FONT_BOLD,
};

const FontData descriptionFontData = {
    .fontSize = 10,
    .fontStyle = FontStyle::FONT_LIGHT,
};

// PanelStatus
const wxColour StatusNone = CC::Red_Mandy;
const wxColour StatusOk = CC::Green_Bice;

}; // namespace Theme