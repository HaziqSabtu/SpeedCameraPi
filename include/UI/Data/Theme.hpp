#pragma once

#include "UI/Font/Font.hpp"
#include <UI/Data/ColorCollection.hpp>
#include <wx/gtk/colour.h>

namespace CC = ColorCollection;

namespace Theme {

// 60-30-10 rule
const wxColour Primary60 = CC::Twitter_ExtExtLightGray;
const wxColour Secondary30 = CC::Twitter_Secondary;
const wxColour Accent10 = CC::Twitter_Primary;
//

const wxColour GrayDisabled = CC::Twitter_LightGray;

const wxColour Background = Primary60;
// const wxColour Primary = ;
const wxColour Text = Secondary30;

const wxColour ButtonBackground = CC::Twitter_ExtLightGray;
const wxColour ButtonText = Secondary30;

const wxColour StatusBackground = Secondary30;
const wxColour StatusText = Primary60;

const wxColour ImageBackground = Secondary30;
const wxColour ImageText = Primary60;
const wxString noImageIcon = wxT("Assets/noImage_96.png");

const wxColour BitmapNormal = Secondary30;
const wxColour BitmapActive = Accent10;
const wxColour BitmapDisabled = GrayDisabled;
const wxSize BitmapDefaultSize = wxSize(50, 50);

// PanelTitle
const wxColour TitleActiveBitmap = Primary60;

const wxColour ExitColor = CC::Red_Mandy;
const wxColour SettingsColor = CC::Yellow_Gamboge;
const wxColour InfoColor = Accent10;

const wxColour TitleDisabledBitmap = GrayDisabled;
const wxColour TitleDisabledBg = Primary60;

// Settings
const wxSize SettingsTextDefaultSize = wxSize(200, 20);
const wxColour SettingsTextBackground = Primary60;

const wxColour SettingsButtonBackground = Primary60;
const wxColour SettingsButtonNormal = Secondary30;
const wxColour SettingsButtonDisabled = GrayDisabled;

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
