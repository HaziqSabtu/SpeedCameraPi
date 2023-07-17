#pragma once

#include <wx/wx.h>

class ConfirmationDialog : public wxDialog {
  public:
    ConfirmationDialog(wxWindow *parent, const wxString &message);

    bool GetConfirmationResult() const;

  private:
    void OnYesButton(wxCommandEvent &event);
    void OnNoButton(wxCommandEvent &event);

    bool m_confirmationResult;
};
