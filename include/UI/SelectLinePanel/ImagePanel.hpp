#ifndef SELECT_LINE_PANEL_IMAGE
#define SELECT_LINE_PANEL_IMAGE

#include <Utils/BufferedBitmap/Derived/BBLane.hpp>
#include <Utils/fileWR.hpp>
#include <wx/wx.h>

class SelectLinePanelImage : public wxPanel {
  public:
    SelectLinePanelImage(wxWindow *parent, wxWindowID id,
                         std::vector<ImgData> &imgData);
    void OnSize(wxSizeEvent &e);
    void OnButtonIncrement();
    void OnButtonDecrement();
    void OnKeyPress(wxKeyEvent &e);

  private:
    int count = 0;

    std::vector<ImgData> imgData;

    wxPanel *img_panel;
    BBLane *img_bitmap;
    wxBoxSizer *img_sizer;

    DECLARE_EVENT_TABLE();
};
#endif
