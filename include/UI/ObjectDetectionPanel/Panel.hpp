#ifndef OBJECT_DETECTION_PANEL
#define OBJECT_DETECTION_PANEL

#include <Algorithm/object_detection/ObjectDetection.hpp>
#include <Algorithm/speed_calculation/speedCalculation.hpp>
#include <UI/ObjectDetectionPanel/ButtonPanel.hpp>
#include <UI/ObjectDetectionPanel/ImagePanel.hpp>
#include <UI/SelectLinePanel/ImagePanel.hpp>
#include <Utils/BufferedBitmap/Derived/BBObjD.hpp>
#include <Utils/Enum.hpp>
#include <Utils/fileWR.hpp>
#include <wx/wx.h>

class ObjectDetectionPanel : public wxPanel {
  public:
    ObjectDetectionPanel(wxWindow *parent, wxWindowID id,
                         std::vector<ImgData> &imgData);
    void OnPageChange();

  private:
    ObjectDetectionPanelButton *button_panel;
    ObjectDetectionPanelImage *img_panel;

    wxBoxSizer *main_sizer;

    BBObjD *img_bitmap;

    void OnButton(wxCommandEvent &e);

    DECLARE_EVENT_TABLE()
};
#endif
