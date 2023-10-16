#pragma once

#include <UI/Dialog/DialogBase.hpp>
#include <wx/wx.h>

class ResetDataDialog : public DialogBaseYesNo {
  public:
    ResetDataDialog(wxWindow *parent);
};