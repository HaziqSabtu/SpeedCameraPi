#pragma once

#include "UI/StaticText/Hyperlink.hpp"
#include <UI/Data/Data.hpp>

namespace Data::Info {
const wxString Title = "SpeedCameraPi";
const FontData TitleFontData = {
    .fontSize = 25,
};

const wxSize iconSize = wxSize(256, 0);
const wxString logo = "Assets/speed_512_flat.png";
const wxString thbLogo = "Assets/thblogo.png";

const HyperLinkData contact = {
    .text = "binmohds@th-brandenburg.de",
    .url = "mailto:binmohds@th-brandenburg.de",
};

const HyperLinkData docs = {
    .text = "Docs",
    .url = "http://docs-link",
};

const HyperLinkData repo = {
    .text = "Github",
    .url = "https://github.com/HaziqSabtu/SpeedCameraPi",
};

const HyperLinkData paper = {
    .text = "Paper",
    .url = "http://paper-link",
};

const HyperLinkData otherRepo = {
    .text = "Other repository",
    .url = "https://github.com/HaziqSabtu",
};
} // namespace Data::Info