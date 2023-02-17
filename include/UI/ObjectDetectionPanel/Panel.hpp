#ifndef OBJECT_DETECTION_PANEL
#define OBJECT_DETECTION_PANEL

#include <Algorithm/object_detection/ObjectDetection.hpp>
#include <Algorithm/speed_calculation/speedCalculation.hpp>
#include <Thread/ObjectDetectionThread.hpp>
#include <UI/ObjectDetectionPanel/ButtonPanel.hpp>
#include <UI/SelectLinePanel/Panel.hpp>
#include <Utils/Enum.hpp>
#include <Utils/FileReader/fileWR.hpp>
#include <Utils/ImageBitmap/Derived/ObjectDetectionBitmap.hpp>
#include <wx/wx.h>

class ObjectDetectionPanel : public wxPanel {
  public:
    ObjectDetectionPanel(wxWindow *parent, wxWindowID id);
    void OnPageChange();

  private:
    bool isBBox;
    bool isOptF;
    bool isBotL;
    bool isLine;
    bool isRunning;

    int c = 0;
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
