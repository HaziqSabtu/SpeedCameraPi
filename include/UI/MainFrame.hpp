#ifndef MAIN_FRAME_HPP
#define MAIN_FRAME_HPP

#include <UI/Panel2.hpp>
#include <UI/SelectROI/Panel.hpp>
#include <Utils/Enum.hpp>
#include <wx/notebook.h>
#include <wx/wx.h>

class MainFrame : public wxFrame {
  public:
    MainFrame(const wxString &title);

  private:
    wxNotebook *notebook;
    SelectRoiPanel *select_roi_panel;
    Panel2 *p2, *p3, *p4, *p5;
};

#endif