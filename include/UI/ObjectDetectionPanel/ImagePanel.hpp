#ifndef OBJECT_DETECTION_PANEL_IMAGE
#define OBJECT_DETECTION_PANEL_IMAGE

#include <Algorithm/object_detection/ObjectDetection.hpp>
#include <Algorithm/speed_calculation/speedCalculation.hpp>
#include <Utils/BufferedBitmap/Derived/BBObjD.hpp>
#include <Utils/Enum.hpp>
#include <Utils/fileWR.hpp>
#include <wx/wx.h>

class ObjectDetectionPanelImage : public wxPanel {
  public:
    ObjectDetectionPanelImage(wxWindow *parent, wxWindowID id,
                              ObjectDetection &objD, SpeedCalculation &spdC,
                              std::vector<ImgData> &imgData);
    void OnSize(wxSizeEvent &e);
    void OnButtonIncrement();
    void OnButtonDecrement();

    void OnBBox();
    void OnOptF();
    void OnBotL();
    void OnLine();
    void OnSpeed();

    void runDetection();
    int GetCount();
    void SetLine(std::vector<cv::Vec4i> l);
    std::vector<std::vector<cv::Point2f>> GetOpticalFlowPoints();

  private:
    int count = 0;

    void handleBBox();
    void handleOptF();
    void handleBotL();

    std::vector<ImgData> imgData;
    std::vector<std::vector<cv::Point2f>> opticalFlowPoints;

    wxPanel *img_panel;
    BBObjD *img_bitmap;
    wxBoxSizer *img_sizer;

    ObjectDetection objD;
    SpeedCalculation speedCalc;

    DECLARE_EVENT_TABLE();
};
#endif
