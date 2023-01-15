#ifndef MAIN_FRAME_HPP
#define MAIN_FRAME_HPP

#include <UI/LaneDetectionPanel/Panel.hpp>
#include <UI/OpticalFlowPanel/Panel.hpp>
#include <UI/Panel2.hpp>
#include <UI/SelectROIPanel/Panel.hpp>
#include <Utils/Enum.hpp>
#include <Utils/fileWR.hpp>
#include <wx/notebook.h>
#include <wx/wx.h>

class MainFrame : public wxFrame {
  public:
    MainFrame(const wxString &title);

  private:
    std::vector<ImgData> imgData;

    wxNotebook *notebook;
    SelectRoiPanel *select_roi_panel;
    OpticalFlowPanel *optical_flow_panel;
    LaneDetectionPanel *lane_detection_panel;

    Panel2 *p2, *p3, *p4;
    void OnPageChange(wxNotebookEvent &event);
};

#endif