#ifndef CAMERA_PANEL_HPP
#define CAMERA_PANEL_HPP

#include <Thread/CaptureThread.hpp>
#include <Thread/DemoThread.hpp>
#include <UI/CameraPanel/ButtonPanel.hpp>
#include <Utils/DataStruct.hpp>
#include <Utils/Enum.hpp>
#include <Utils/FileReader/fileH264.hpp>
#include <Utils/ImageBitmap/Derived/CameraBitmap.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/videoio.hpp>
#include <wx/notebook.h>
#include <wx/wx.h>

class CameraPanel : public wxPanel {
  public:
    CameraPanel(wxWindow *parent, wxWindowID id, wxString filePath);
    ~CameraPanel();
    std::vector<ImageData> GetImgData();

  public:
    void OnButton(wxCommandEvent &e);
    void OnTimer(wxTimerEvent &event);
    void OnCapture();
    void OnStopCapture();

  private:
    wxString filePath;
    cv::Mat frame;
    bool isCapturing;
    bool isProcessing;

    cv::VideoCapture camera;
    wxTimer timer;
    CameraPanelButton *button_panel;
    CameraBitmap *img_bitmap;

    wxBoxSizer *main_sizer;

    wxCriticalSection criticalSection;
    std::vector<ImageData> imgData;

    wxThread *captureThread;
    wxThread *loadThread;

    void OnSize(wxSizeEvent &e);
    DECLARE_EVENT_TABLE()
};
#endif