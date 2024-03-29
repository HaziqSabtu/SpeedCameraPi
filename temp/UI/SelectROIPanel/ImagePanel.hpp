#ifndef SELECT_ROI_PANEL_IMAGE
#define SELECT_ROI_PANEL_IMAGE

#include <Utils/BufferedBitmap/Derived/BBImage.hpp>
#include <Utils/FileReader/fileWR.hpp>
#include <wx/wx.h>

class SelectRoiPanelImage : public wxPanel {
  public:
    SelectRoiPanelImage(wxWindow *parent, wxWindowID id,
                        std::vector<ImgData> &imgData);
    void OnKeyPress(wxKeyEvent &e);
    void OnToggleROI(wxCommandEvent &e);
    void OnSize(wxSizeEvent &e);
    void OnLeftUp(wxMouseEvent &e);
    void OnButtonIncrement();
    void OnButtonDecrement();
    int GetCount();
    cv::Rect GetTrueRect();

  private:
    int count = 0;

    std::vector<ImgData> imgData;

    wxPanel *img_panel;
    BBImage *img_bitmap;
    wxBoxSizer *img_sizer;

    DECLARE_EVENT_TABLE();
};
#endif
