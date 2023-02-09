#ifndef CAMERA_PANEL_HPP
#define CAMERA_PANEL_HPP

#include <Thread/CaptureThread.hpp>
#include <UI/CameraPanel/ButtonPanel.hpp>
#include <Utils/Enum.hpp>
#include <Utils/ImageBitmap/ImageBitmap.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/videoio.hpp>
#include <wx/notebook.h>
#include <wx/wx.h>

class CameraPanel : public wxPanel {
  public:
    CameraPanel(wxWindow *parent, wxWindowID id);
    ~CameraPanel();

  public:
    void OnButton(wxCommandEvent &e);
    void OnTimer(wxTimerEvent &event);
    void OnCapture(wxCommandEvent &event);
    void OnStopCapture(wxCommandEvent &event);

    cv::Mat m_frame;
    cv::VideoCapture m_camera;
    wxTimer m_timer;
    bool m_isCapturing = false;

    wxCriticalSection m_criticalSection;
    std::vector<std::pair<cv::Mat, wxDateTime>> m_capturedFrames;

    wxThread *m_captureThread;

  private:
    CameraPanelButton *button_panel;
    ImageBitmap *img_bitmap;

    wxBoxSizer *main_sizer;

    void OnSize(wxSizeEvent &e);
    DECLARE_EVENT_TABLE()
};
#endif