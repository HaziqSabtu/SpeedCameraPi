#ifndef OBJECT_DETECTION_PANEL
#define OBJECT_DETECTION_PANEL

#include <Algorithm/object_tracker/OpticalFlowTracker.hpp>
#include <Algorithm/speed_calculation/speedCalculation.hpp>
#include <Thread/ObjectDetectionThread.hpp>
#include <UI/ObjectDetectionPanel/ButtonPanel.hpp>
#include <Utils/Config/AppConfig.hpp>
#include <Utils/Enum.hpp>
#include <Utils/ImageBitmap/Derived/ObjectDetectionBitmap.hpp>
#include <wx/wx.h>

class ObjectDetectionPanel : public wxPanel {
  public:
    ObjectDetectionPanel(wxWindow *parent, wxWindowID id, AppConfig *config);
    void OnPageChange();

  private:
    bool isBBox;
    bool isOptF;
    bool isBotL;
    bool isLine;
    bool isRunning;

    int c = 0;
    int CameraPanelRefreshRate;
    cv::Rect *bbox;
    std::vector<std::vector<cv::Point2f>> *result;
    std::vector<cv::Point2f> *bottomLine;
    std::vector<cv::Vec4i> selectedLines;
    std::vector<std::vector<cv::Point2f>> opticalFlowPoints;
    std::vector<ImageData> imgData;
    double calculatedSpeed;

    ObjectDetectionPanelButton *button_panel;

    wxBoxSizer *main_sizer;

    ObjectDetectionBitmap *img_bitmap;

    cv::RNG rng;
    ObjectDetection objectDetection;
    SpeedCalculation speedCalculation;
    wxThread *objectDetectionThread;
    wxTimer timer;
    wxTimer loopTimer;

    void handleBBox();
    void handleOptF();
    void handleBotL();
    void handleSpeed();

    void OnButton(wxCommandEvent &e);
    void OnIncrement();
    void OnSize(wxSizeEvent &e);
    void OnTimer(wxTimerEvent &e);
    void OnImageLoop(wxTimerEvent &e);

    DECLARE_EVENT_TABLE()
};
#endif
