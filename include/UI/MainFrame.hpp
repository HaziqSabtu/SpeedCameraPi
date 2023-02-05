#ifndef MAIN_FRAME_HPP
#define MAIN_FRAME_HPP

#include <UI/LaneDetectionPanel/Panel.hpp>
#include <UI/ObjectDetectionPanel/Panel.hpp>
#include <UI/OpticalFlowPanel/Panel.hpp>
#include <UI/Panel2.hpp>
#include <UI/SelectLinePanel/Panel.hpp>
#include <UI/SelectROIPanel/Panel.hpp>
#include <Utils/Enum.hpp>
#include <Utils/ImageUtils.hpp>
#include <Utils/fileAVI.hpp>
#include <Utils/fileH264.hpp>
#include <Utils/fileWR.hpp>
#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <wx/notebook.h>
#include <wx/wx.h>

class MainFrame : public wxFrame {
  public:
    MainFrame(const wxString &title);
    ~MainFrame();

  private:
    cv::VideoCapture *video_capture;
    std::vector<ImgData> imgData;
    wxNotebook *notebook;
    SelectLinePanel *select_line_panel;
    ObjectDetectionPanel *object_detection_panel;
    Panel2 *p2, *p3, *p4;
    void OnPageChange(wxNotebookEvent &event);
};

#endif