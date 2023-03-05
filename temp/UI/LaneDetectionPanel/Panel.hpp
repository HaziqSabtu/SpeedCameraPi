#ifndef LANE_DETECTION_PANEL
#define LANE_DETECTION_PANEL

#include <Algorithm/optical_flow/SparseOpticalFlow.hpp>
#include <UI/LaneDetectionPanel/ButtonPanel.hpp>
#include <UI/LaneDetectionPanel/ImagePanel.hpp>
#include <UI/OpticalFlowPanel/ImagePanel.hpp>
#include <Utils/FileReader/fileWR.hpp>
#include <wx/wx.h>

class LaneDetectionPanel : public wxPanel {
  public:
    LaneDetectionPanel(wxWindow *parent, wxWindowID id,
                       const std::vector<ImgData> &imgData);
    void OnPageChange();

  private:
    LaneDetectionPanelButton *button_panel;
    LaneDetectionPanelImage *img_panel;

    wxBoxSizer *main_sizer;

    DECLARE_EVENT_TABLE()
};
#endif
