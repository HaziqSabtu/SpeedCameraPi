#ifndef CAMERA_PANEL_HPP
#define CAMERA_PANEL_HPP

#include <Event/Event_Hough.hpp>
#include <Event/Event_LoadImage.hpp>
#include <Event/Event_ProcessImage.hpp>
#include <Event/Event_Speed.hpp>
#include <Event/Event_UpdateImage.hpp>
#include <Thread/ThreadPool.hpp>
#include <Thread/Thread_Capture.hpp>
#include <Thread/Thread_Hough.hpp>
#include <Thread/Thread_LoadCapture.hpp>
#include <Thread/Thread_LoadFile.hpp>
#include <Thread/Thread_Process.hpp>
#include <Thread/Thread_Result.hpp>
#include <Thread/Thread_Speed.hpp>
#include <UI/CameraPanel/Panel_Button_Capture.hpp>
#include <UI/CameraPanel/Panel_Button_Hough.hpp>
#include <UI/CameraPanel/Panel_Button_Result.hpp>
#include <UI/CameraPanel/Panel_Image.hpp>
#include <Utils/Camera/CameraBase.hpp>
#include <Utils/Camera/libcam.hpp>
#include <Utils/Config/AppConfig.hpp>
#include <Utils/DataStruct.hpp>
#include <Utils/Enum.hpp>
#include <Utils/Struct/D_Line.hpp>
#include <opencv2/opencv.hpp>
#include <wx/wx.h>

class CameraPanel : public wxPanel {
  public:
    CameraPanel(wxWindow* parent, wxWindowID id, AppConfig* config);
    ~CameraPanel();

  private:
    LibCam camera;
    ThreadPool threadPool;

    ProcessThread* processThread;
    HoughThread* houghThread;
    ResultThread* resultThread;
    SpeedThread* speedThread;
    LoadFileThread* loadFileThread;
    LoadCaptureThread* loadCaptureThread;
    CaptureThread* captureThread;

    CameraPanelButton* button_panel;
    ButtonPanelHough* button_panel_hough;
    PanelButtonResult* button_panel_result;
    ImagePanel* img_bitmap;

    wxBoxSizer* main_sizer;

    const int circleRadius;
    std::vector<ImageData>* imgData;
    std::vector<Detection::Line> selectedLine;
    std::vector<cv::Point2f> selectedPoint;

    void addLine(Detection::Line line);
    void searchLine(cv::Point2f realMousePos);

    int currentImageIndex = 0;
    void OnIncrement();
    void OnDecrement();

    void deleteThread(wxThread* thread);
    void waitThenDeleteThread(wxThread* thread);

    void OnButton(wxCommandEvent& e);
    void OnLeftDown(wxMouseEvent& e);
    void OnSize(wxSizeEvent& e);
    void OnUpdateImage(UpdateImageEvent& e);
    void OnProcessImage(wxCommandEvent& e);
    void OnCaptureImage(wxCommandEvent& e);
    void OnHough(HoughEvent& e);
    void OnSpeed(SpeedCalcEvent& e);

    DECLARE_EVENT_TABLE()
};
#endif