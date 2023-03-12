#ifndef CAMERA_PANEL_HPP
#define CAMERA_PANEL_HPP

#include <Event/Event_CaptureImage.hpp>
#include <Event/Event_Hough.hpp>
#include <Event/Event_ProcessImage.hpp>
#include <Event/Event_UpdateImage.hpp>
#include <Thread/Task/Task_Capture.hpp>
#include <Thread/Task/Task_HoughLine.hpp>
#include <Thread/Task/Task_Load.hpp>
#include <Thread/Task/Task_OpticalFlow.hpp>
#include <Thread/Task/Task_Sift.hpp>
#include <Thread/ThreadPool.hpp>
#include <Thread/Thread_Capture.hpp>
#include <Thread/Thread_Hough.hpp>
#include <Thread/Thread_LoadFile.hpp>
#include <Thread/Thread_Process.hpp>
#include <UI/CameraPanel/ButtonPanel.hpp>
#include <UI/CameraPanel/ButtonPanel_Hough.hpp>
#include <UI/CameraPanel/Panel_Button_Result.hpp>
#include <Utils/Config/AppConfig.hpp>
#include <Utils/Config/ConfigStruct.hpp>
#include <Utils/DataStruct.hpp>
#include <Utils/Enum.hpp>
#include <Utils/ImageBitmap/Bit.hpp>
#include <Utils/ImageBitmap/Derived/CameraBitmap.hpp>
#include <Utils/Struct/D_Line.hpp>
#include <opencv2/opencv.hpp>
#include <wx/wx.h>

class CameraPanel : public wxPanel {
  public:
    CameraPanel(wxWindow *parent, wxWindowID id);
    ~CameraPanel();

  private:
    cv::VideoCapture camera;
    ThreadPool threadPool;

    ProcessThread *processThread;
    HoughThread *houghThread;

    CameraPanelButton *button_panel;
    ButtonPanelHough *button_panel_hough;
    PanelButtonResult *button_panel_result;

    wxImagePanel *img_bitmap;
    wxBoxSizer *main_sizer;

    std::vector<ImageData> *imgData;
    std::vector<Detection::Line> selectedLine;
    std::vector<cv::Point2f> selectedPoint;

    void addLine(Detection::Line line);
    void searchLine(cv::Point2f realMousePos);

    int currentImageIndex = 0;
    void OnIncrement();
    void OnDecrement();

    void OnButton(wxCommandEvent &e);
    void OnLeftDown(wxMouseEvent &e);
    void OnSize(wxSizeEvent &e);
    void OnUpdateImage(UpdateImageEvent &e);
    void OnProcessImage(wxCommandEvent &e);
    void OnCaptureImage(CaptureImageEvent &e);
    void OnHough(HoughEvent &e);

    DECLARE_EVENT_TABLE()
};
#endif