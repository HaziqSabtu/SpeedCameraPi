#pragma once

#include <UI/Dialog/DialogBase.hpp>
#include <wx/wx.h>

class RemoveRoiDialog : public DialogBaseYesNo {
  public:
    RemoveRoiDialog(wxWindow *parent);
};