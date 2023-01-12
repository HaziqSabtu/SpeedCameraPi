#ifndef SELECT_ROI_PANEL
#define SELECT_ROI_PANEL

#include "BufferedBitmap.hpp"
#include "SelectroiPanel.Button.hpp"
#include "SelectroiPanel.Image.hpp"
#include "data_srz/fileWR.hpp"
#include <wx/wx.h>

enum { IMG_PANEL_ID = 100, BUTTON_PANEL_ID };

class SelectRoiPanel : public wxPanel {
  public:
    SelectRoiPanel(wxWindow *parent, wxWindowID id);
    void OnButton(wxCommandEvent &e);
    void OnKeyPress(wxKeyEvent &e);
    void OnToggleROI(wxCommandEvent &e);
    void OnSize(wxSizeEvent &e);
    DECLARE_EVENT_TABLE()

  private:
    int count = 0;
    std::vector<ImgData> imgData;

    wxBoxSizer *button_sizer;
    wxButton *Next_Button;
    wxButton *Prev_Button;
    wxButton *Sel_Button;
    wxButton *RemoveROI_Button;

    wxPanel *img_panel;
    BufferedBitmap *img_bitmap;
    wxBoxSizer *img_sizer;

    wxBoxSizer *img_sizer3;

    wxBoxSizer *main_sizer;
};
#endif
