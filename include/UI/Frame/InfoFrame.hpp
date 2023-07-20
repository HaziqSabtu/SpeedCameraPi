#pragma once

#include <wx/wx.h>

class InfoFrame : public wxFrame {
  public:
    InfoFrame();

  private:
    void OnButton(wxCommandEvent &e);

    DECLARE_EVENT_TABLE()
};