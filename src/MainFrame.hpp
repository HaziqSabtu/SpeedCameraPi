#ifndef MAIN_FRAME_HPP
#define MAIN_FRAME_HPP

#include "BufferedBitmap.hpp"
#include "OtherFrame.hpp"
#include "data_srz/fileWR.hpp"
#include <wx/wx.h>

enum {
    Next_Button_ID = 1,
    Prev_Button_ID = 2,
    Sel_Button_ID = 3,
    Frame_Button_ID = 4
};

class MainFrame : public wxFrame {
  public:
    std::vector<ImgData> imgData;

    MainFrame(const wxString &title);

  private:
    int count = 0;

    wxPanel *button_panel;
    wxBoxSizer *button_sizer;
    wxButton *Next_Button;
    wxButton *Prev_Button;
    wxButton *Sel_Button;
    wxButton *Frame_Button;

    wxPanel *img_panel;
    BufferedBitmap *img_bitmap;
    wxBoxSizer *img_sizer;

    wxPanel *img_panel2;
    BufferedBitmap *img_bitmap2;
    wxBoxSizer *img_sizer2;

    wxBoxSizer *img_sizer3;

    wxBoxSizer *main_sizer;
    void OnButton(wxCommandEvent &e);
    void OnKeyPress(wxKeyEvent &e);
    void OnSwitchPanel(wxCommandEvent &e);
    DECLARE_EVENT_TABLE()
};

#endif