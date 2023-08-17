#include "Utils/Enum.hpp"
#include <UI/Button/BitmapButton/Type3/Button_Info.hpp>
#include <wx/app.h>
#include <wx/gdicmn.h>
#include <wx/stringimpl.h>

ButtonInfo::ButtonInfo(wxWindow *parent, const BitmapDataT3 &data)
    : BitmapButtonT3(parent, Enum::G_Info_Button_ID, data) {}

ButtonInfo::~ButtonInfo() {}

BEGIN_EVENT_TABLE(ButtonInfo, wxButton)
END_EVENT_TABLE()