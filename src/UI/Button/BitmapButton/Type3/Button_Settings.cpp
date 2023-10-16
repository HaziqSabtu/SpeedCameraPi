#include "Utils/Enum.hpp"
#include <UI/Button/BitmapButton/Type3/Button_Settings.hpp>
#include <wx/app.h>
#include <wx/gdicmn.h>
#include <wx/stringimpl.h>

ButtonSettings::ButtonSettings(wxWindow *parent, const BitmapDataT3 &data)
    : BitmapButtonT3(parent, Enum::G_Setting_Button_ID, data) {}

ButtonSettings::~ButtonSettings() {}

BEGIN_EVENT_TABLE(ButtonSettings, wxButton)
END_EVENT_TABLE()