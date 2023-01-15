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
    void RunLaneDetection();
    void SetCount(int count);

  private:
    int count = 0;
    std::vector<ImgData> imgData;

    std::vector<std::vector<cv::Point2f>> roiPoints;

    void OnSize(wxSizeEvent &e);

    wxPanel *img_panel;
    BBLaneD *img_bitmap;
    wxBoxSizer *img_sizer;

    LaneDetectionAlgorithm *laneDetection;

    DECLARE_EVENT_TABLE();
};
#endif
