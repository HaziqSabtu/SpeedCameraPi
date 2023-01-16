#ifndef LANE_DETECTION_PANEL_IMAGE
#define LANE_DETECTION_PANEL_IMAGE

#include <Algorithm/lane_detection/LaneDetectionAlgorithm.hpp>
#include <Utils/BufferedBitmap/Derived/BBLaneD.hpp>
#include <Utils/fileWR.hpp>
#include <wx/wx.h>

class LaneDetectionPanelImage : public wxPanel {
  public:
    LaneDetectionPanelImage(wxWindow *parent, wxWindowID id,
                            const std::vector<ImgData> &imgData);

    void SetROIPoints(std::vector<std::vector<cv::Point2f>> roiPoints);
    void SetCount(int count);
    void SetFirstImage(cv::Mat firstImg);
    void RunLaneDetection();
    void OnIncrement();
    void OnDecrement();

  private:
    const int IMAGE_TO_GENERATE = 9;
    const int IMAGE_PER_ROW = 3;
    int imgC = 0;
    int count = 0;
    cv::Mat firstImg;
    std::vector<ImgData> imgData;
    std::vector<std::vector<cv::Point2f>> roiPoints;

    void OnSize(wxSizeEvent &e);
    void GenerateImage();

    wxPanel *img_panel;
    BBLaneD *img_bitmap;
    wxBoxSizer *img_sizer;

    LaneDetectionAlgorithm *laneDetection;

    DECLARE_EVENT_TABLE();
};
#endif