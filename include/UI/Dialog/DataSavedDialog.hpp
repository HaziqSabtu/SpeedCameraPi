#pragma once

#include <UI/Dialog/DialogBase.hpp>
#include <wx/wx.h>

class DataSavedDialog : public DialogBaseYesNo {
  public:
    DataSavedDialog(wxWindow *parent);

    wxButton *resetButton;

    wxWindowID resetButtonID = wxID_HIGHEST + 1;

  private:
    void OnResetButton(wxCommandEvent &event);
};
