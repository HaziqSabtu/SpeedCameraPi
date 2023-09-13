#pragma once

#include <UI/Dialog/DialogBase.hpp>
#include <wx/wx.h>

class ExitAppDialog : public DialogBaseYesNo {
  public:
    ExitAppDialog(wxWindow *parent);
    int getShutdownButtonID();

  private:
    wxButton *shutdown_Button;
    int shutdown_ButtonID;

    void OnShutdownButton(wxCommandEvent &event);
};