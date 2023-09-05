#pragma once

#include <UI/Dialog/DialogBase.hpp>
#include <wx/wx.h>

class RemoveCalibrationDialog : public DialogBaseYesNo {
  public:
    RemoveCalibrationDialog(wxWindow *parent);
};