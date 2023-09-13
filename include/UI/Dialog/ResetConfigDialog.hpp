#pragma once

#include <UI/Dialog/DialogBase.hpp>
#include <wx/wx.h>

class ResetConfigDialog : public DialogBaseYesNo {
  public:
    ResetConfigDialog(wxWindow *parent);
};