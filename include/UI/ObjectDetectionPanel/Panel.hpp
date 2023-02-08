#ifndef OBJECT_DETECTION_PANEL
#define OBJECT_DETECTION_PANEL

#include <Algorithm/object_detection/ObjectDetection.hpp>
#include <Algorithm/speed_calculation/speedCalculation.hpp>
#include <UI/ObjectDetectionPanel/ButtonPanel.hpp>
#include <UI/ObjectDetectionPanel/ImagePanel.hpp>
#include <UI/SelectLinePanel/Panel.hpp>
#include <Utils/BufferedBitmap/Derived/BBObjD.hpp>
#include <Utils/Enum.hpp>
#include <Utils/ImageBitmap/Derived/ObjectDetectionBitmap.hpp>
#include <Utils/fileWR.hpp>
#include <wx/wx.h>

class ObjectDetectionPanel : public wxPanel {
  public:
    ObjectDetectionPanel(wxWindow *parent, wxWindowID id,
                         std::vector<ImgData> &imgData);
    void OnPageChange();

  private:
    bool isBBox;
    bool isOptF;
    bool isBotL;
    bool isLine;

    int c = 0;
    cv::Rect *bbox;
    std::vector<std::vector<cv::Point2f>> *result;
    std::vector<cv::Point2f> *bottomLine;
    std::vector<cv::Vec4i> selectedLines;
    std::vector<std::vector<cv::Point2f>> opticalFlowPoints;
    std::vector<ImgData> imgData;

    ObjectDetectionPanelButton *button_panel;
    // ObjectDetectionPanelImage *img_panel;

    wxBoxSizer *main_sizer;

    ObjectDetectionBitmap *img_bitmap;

    cv::RNG rng;
    ObjectDetection objectDetection;

    void handleBBox();
    void handleOptF();
    void handleBotL();

    void OnButton(wxCommandEvent &e);
    void OnIncrement();
    void OnSize(wxSizeEvent &e);

    DECLARE_EVENT_TABLE()
};
#endif
