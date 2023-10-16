#pragma once

#include <UI/Dialog/DialogBase.hpp>
#include <wx/wx.h>

class SwitchModeDialog : public DialogBaseYesNo {
  public:
    SwitchModeDialog(wxWindow *parent);
};