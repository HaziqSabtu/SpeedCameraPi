#pragma once

#include <UI/Dialog/DialogBase.hpp>
#include <wx/wx.h>

class CancelDialog : public DialogBaseYesNo {
  public:
    CancelDialog(wxWindow *parent);
};