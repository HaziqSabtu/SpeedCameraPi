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
    .text = "Project Documentation",
    .url = "https://haziqsabtu.github.io/SpeedCameraPi/",
};

const HyperLinkData repo = {
    .text = "Github",
    .url = "https://github.com/HaziqSabtu/SpeedCameraPi",
};

const HyperLinkData usermanual = {
    .text = "User Manual",
    .url = "https://drive.google.com/file/d/1CKM41b0lVNlPVhcOHVzftnJ13RWR5m6Y/"
           "view?usp=drive_link",
};

const HyperLinkData developermanual = {
    .text = "Developer Manual",
    .url = "https://drive.google.com/file/d/1Dm2La7uIj3iK4M7hl8aNyZqYd4_LneJs/"
           "view?usp=sharing",
};

const HyperLinkData paper = {
    .text = "Paper",
    .url = "http://paper-link",
};

} // namespace Data::Info