#pragma once

#include <wx/wx.h>

class ButtonExit : public wxButton {
  public:
    ButtonExit(wxWindow *parent);
    ~ButtonExit();

  private:
    const wxSize size = wxSize(40, 40);
    const wxColour colour = wxColour(234, 84, 85);
    const wxString filename = wxT("exit_24.ico");

    void OnButton(wxCommandEvent &e);
    DECLARE_EVENT_TABLE()
};