#ifndef CAMERA_PANEL_HPP
#define CAMERA_PANEL_HPP

#include <Event/Temp.hpp>
#include <Event/UpdateImageEvent.hpp>
#include <Thread/Task/Task_Capture.hpp>
#include <Thread/Task/Task_HoughLine.hpp>
#include <Thread/Task/Task_Load.hpp>
#include <Thread/Task/Task_OpticalFlow.hpp>
#include <Thread/Task/Task_Sift.hpp>
#include <Thread/ThreadPool.hpp>
#include <UI/CameraPanel/ButtonPanel.hpp>
#include <Utils/Config/AppConfig.hpp>
#include <Utils/Config/ConfigStruct.hpp>
#include <Utils/DataStruct.hpp>
#include <Utils/Enum.hpp>
#include <Utils/ImageBitmap/Derived/CameraBitmap.hpp>
#include <opencv2/opencv.hpp>
#include <wx/wx.h>

class CameraPanel : public wxPanel {
  public:
    CameraPanel(wxWindow *parent, wxWindowID id);
    ~CameraPanel();
    // std::vector<ImageData> GetImgData();

  public:
    // void OnTimer(wxTimerEvent &e);
    // void OnThreadCheck(wxTimerEvent &e);
    // void OnCapture();
    // void OnLoadFile();
    // void OnToggleCamera();

  private:
    // void addPoints(wxPoint realMousePos);
    // void captureExecutor(const int max);
    // void loadExecutor(const int max);
    // void siftExecutor(const int max);
    // void houghExecutor(const int max);
    // void houghExecutorSingle(int id);
    // void flowExecutor(const int max);
    // void checkForLine(wxPoint realMousePos);
    // void addLine(Detection::Line line);

    // int maxLoadFrame;
    // wxString filePath;
    // cv::Mat frame;
    // bool isCapturing;
    // bool isProcessing;
    // bool isThreadRunning;
    // bool isTimerRunning = true;

    // std::vector<cv::Point2f> *ptns;
    // std::vector<Detection::Line> *selectedLines;

    cv::VideoCapture camera;
    // ThreadPool threadPool;

    // wxTimer timer;
    // wxTimer threadCheckTimer;
    CameraPanelButton *button_panel;
    CameraBitmap *img_bitmap;
    wxBoxSizer *main_sizer;

    // wxCriticalSection criticalSection;
    // std::vector<ImageData> imgData;

    // wxThread *captureThread;
    // wxThread *loadThread;

    void OnButton(wxCommandEvent &e);
    void OnLeftDown(wxMouseEvent &e);
    void OnSize(wxSizeEvent &e);
    void OnImageUpdate(UpdateImageEvent &e);
    ImageThread *m_imageThread;

    DECLARE_EVENT_TABLE()
};
#endif