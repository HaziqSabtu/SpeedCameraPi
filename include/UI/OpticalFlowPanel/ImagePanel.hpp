#ifndef OPTICAL_FLOW_PANEL_IMAGE
#define OPTICAL_FLOW_PANEL_IMAGE

#include <Algorithm/object_tracker/ObjectTracker.hpp>
#include <Algorithm/optical_flow/SparseOpticalFlow.hpp>
#include <Utils/BufferedBitmap/Derived/BBOptF.hpp>
#include <Utils/fileWR.hpp>
#include <wx/wx.h>

class OpticalFlowPanelImage : public wxPanel {
  public:
    OpticalFlowPanelImage(wxWindow *parent, wxWindowID id,
                          const std::vector<ImgData> &imgData);

    void OnKeyPress(wxKeyEvent &e);
    void OnSize(wxSizeEvent &e);
    void OnButtonIncrement();
    void OnButtonDecrement();
    void SetCount(int count);
    void SetTrueRect(cv::Rect r);
    void StartTracking();
    void StartOpticalFlow();
    void EvalOFResult();

    std::vector<std::vector<PointData>> GetRoiData();
    int GetCount();

  private:
    // OpticalFlow Variables
    const int OF_MAX_COUNT = 5;
    const int OF_LIMIT = 3;
    bool isOpticalFlow = false;

    int count = 0;
    bool isObjectTracked = false;
    std::vector<ImgData> imgData;
    std::vector<std::vector<PointData>> roiData;

    OBJECTTRACKER *tracker;
    SparseOF *opticalFlow;

    wxPanel *img_panel;
    BBOpticalFlow *img_bitmap;
    wxBoxSizer *img_sizer;
    DECLARE_EVENT_TABLE()
};
#endif
