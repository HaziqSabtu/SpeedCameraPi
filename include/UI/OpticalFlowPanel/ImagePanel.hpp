#ifndef OPTICAL_FLOW_PANEL_IMAGE
#define OPTICAL_FLOW_PANEL_IMAGE

#include <Utils/BufferedBitmap/Derived/BBOptF.hpp>
#include <Utils/fileWR.hpp>
#include <wx/wx.h>

class OpticalFlowPanelImage : public wxPanel {
  public:
    OpticalFlowPanelImage(wxWindow *parent, wxWindowID id,
                          std::vector<ImgData> &imgData);
    void OnKeyPress(wxKeyEvent &e);
    void OnSize(wxSizeEvent &e);
    void OnButtonIncrement();
    void OnButtonDecrement();
    void SetCount(int count);

  private:
    int count = 0;
    std::vector<ImgData> imgData;

    wxPanel *img_panel;
    BBOpticalFlow *img_bitmap;
    wxBoxSizer *img_sizer;
    DECLARE_EVENT_TABLE()
};
#endif
