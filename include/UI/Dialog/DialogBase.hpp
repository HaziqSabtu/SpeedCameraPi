#pragma once

#include "UI/Data/DialogData.hpp"
#include <wx/wx.h>

/**
 * @brief Dialog Base
 * @image html dialog.png
 * @image latex dialog.png
 */
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
