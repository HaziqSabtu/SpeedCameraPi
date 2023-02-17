#ifndef MAIN_FRAME_HPP
#define MAIN_FRAME_HPP

#include <UI/CameraPanel/Panel.hpp>
#include <UI/ObjectDetectionPanel/Panel.hpp>
#include <UI/SelectLinePanel/Panel.hpp>
#include <Utils/Enum.hpp>
#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <wx/filename.h>
#include <wx/notebook.h>
#include <wx/wx.h>

class MainFrame : public wxFrame {
  public:
    MainFrame(const wxString &title, wxString filename, wxString dirLocation,
              wxSize size);
    ~MainFrame();

  private:
    cv::VideoCapture *video_capture;
    std::vector<ImageData> imgData;

    wxNotebook *notebook;
    CameraPanel *camera_panel;
    SelectLinePanel *select_line_panel;
    ObjectDetectionPanel *object_detection_panel;

    void OnPageChange(wxNotebookEvent &event);
};

#endif