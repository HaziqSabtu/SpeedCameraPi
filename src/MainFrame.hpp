#ifndef MAIN_FRAME_HPP
#define MAIN_FRAME_HPP

#include "SelectroiPanel.hpp"
#include <wx/wx.h>

class MainFrame : public wxFrame {
  public:
    MainFrame(const wxString &title);

  private:
    SelectRoiPanel *select_roi_panel;
};

#endif