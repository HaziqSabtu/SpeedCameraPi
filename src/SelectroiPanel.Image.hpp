#ifndef SELECT_ROI_PANEL_IMAGE
#define SELECT_ROI_PANEL_IMAGE

#include "BufferedBitmap.hpp"
#include "data_srz/fileWR.hpp"
#include <wx/wx.h>

// enum {
//     Next_Button_ID = 1,
//     Prev_Button_ID = 2,
//     Sel_Button_ID = 3,
//     RemoveROI_Button_ID = 4,
// };

class SelectRoiPanelImage : public wxPanel {
  public:
    SelectRoiPanelImage(wxWindow *parent, wxWindowID id,
                        std::vector<ImgData> &imgData);
    void OnKeyPress(wxKeyEvent &e);
    void OnToggleROI(wxCommandEvent &e);
    void OnSize(wxSizeEvent &e);
    void OnButtonIncrement();
    void OnButtonDecrement();

    DECLARE_EVENT_TABLE()

  private:
    int count = 0;
    std::vector<ImgData> imgData;

    wxPanel *img_panel;
    BufferedBitmap *img_bitmap;
    wxBoxSizer *img_sizer;
};
#endif
