#include "Utils/Enum.hpp"
#include <UI/Button/BitmapButton/Type3/Button_SwitchMode.hpp>
#include <wx/app.h>
#include <wx/gdicmn.h>
#include <wx/stringimpl.h>

ButtonSwitchMode::ButtonSwitchMode(wxWindow *parent, const BitmapDataT3 &data)
    : BitmapButtonT3(parent, Enum::G_SwitchMode_Button_ID, data) {}

ButtonSwitchMode::~ButtonSwitchMode() {}

BEGIN_EVENT_TABLE(ButtonSwitchMode, wxButton)
END_EVENT_TABLE()