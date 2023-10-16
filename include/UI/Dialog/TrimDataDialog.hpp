#pragma once

#include <UI/Dialog/DialogBase.hpp>
#include <wx/wx.h>

class TrimDataDialog : public DialogBaseYesNo {
  public:
    TrimDataDialog(wxWindow *parent);
};