#pragma once

#include <UI/Dialog/DialogBase.hpp>
#include <wx/wx.h>

class SaveDataDialog : public DialogBaseYesNo {
  public:
    SaveDataDialog(wxWindow *parent, wxString s);
};