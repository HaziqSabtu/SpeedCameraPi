#include "UI/Theme/Theme.hpp"
#include "Utils/Enum.hpp"
#include "Utils/wxUtils.hpp"
#include <UI/Button/BitmapButton/Type3/Button_Exit.hpp>
#include <wx/app.h>
#include <wx/gdicmn.h>
#include <wx/stringimpl.h>

ButtonExit::ButtonExit(wxWindow *parent, const BitmapDataT3 &data)
    : BitmapButtonT3(parent, Enum::G_Exit_Button_ID, data) {}

ButtonExit::~ButtonExit() {}

BEGIN_EVENT_TABLE(ButtonExit, wxButton)
END_EVENT_TABLE()