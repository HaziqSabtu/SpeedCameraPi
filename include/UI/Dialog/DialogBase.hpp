#pragma once

#include "UI/Data/DialogData.hpp"
#include <wx/wx.h>

class DialogBaseYesNo : public wxDialog {
  public:
    DialogBaseYesNo(wxWindow *parent, const wxString &title,
                    const wxString &text);

    bool GetConfirmationResult() const;

  protected:
    void OnYesButton(wxCommandEvent &event);
    void OnNoButton(wxCommandEvent &event);

    bool result;

    wxBoxSizer *buttonSizer;
};
