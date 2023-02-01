#ifndef OBJECT_DETECTION_PANEL_IMAGE
#define OBJECT_DETECTION_PANEL_IMAGE

#include <Utils/BufferedBitmap/Derived/BBImage.hpp>
#include <Utils/BufferedBitmap/Derived/BBObjD.hpp>
#include <Utils/Enum.hpp>
#include <Utils/fileWR.hpp>
#include <wx/wx.h>

class ObjectDetectionPanelImage : public wxPanel {
  public:
    ObjectDetectionPanelImage(wxWindow *parent, wxWindowID id,
                              std::vector<ImgData> &imgData);
    void OnSize(wxSizeEvent &e);
    void OnButtonIncrement();
    void OnButtonDecrement();
    int GetCount();

  private:
    int count = 0;

    std::vector<ImgData> imgData;

    wxPanel *img_panel;
    BBObjD *img_bitmap;
    wxBoxSizer *img_sizer;

    DECLARE_EVENT_TABLE();
};
#endif
