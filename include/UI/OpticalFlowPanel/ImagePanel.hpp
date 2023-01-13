#ifndef OPTICAL_FLOW_PANEL_IMAGE
#define OPTICAL_FLOW_PANEL_IMAGE

#include <Utils/BufferedBitmap/Derived/BBImage.hpp>
#include <Utils/fileWR.hpp>
#include <wx/wx.h>

class OpticalFlowPanelImage : public wxPanel {
  public:
    OpticalFlowPanelImage(wxWindow *parent, wxWindowID id,
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
    BBImage *img_bitmap;
    wxBoxSizer *img_sizer;
};
#endif
