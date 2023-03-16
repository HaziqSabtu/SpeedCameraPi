#ifndef PANEL_IMAGE_HPP
#define PANEL_IMAGE_HPP

#include <Utils/DataStruct.hpp>
#include <Utils/Struct/D_Line.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <wx/rawbmp.h>
#include <wx/sizer.h>
#include <wx/wx.h>

enum SHOW_TYPE {
    SHOW_TYPE_NONE,
    SHOW_TYPE_IMAGE,
    SHOW_TYPE_CANNY,
};

class ImagePanel : public wxPanel {
    cv::Mat image, noImage;
    ImageData imgData;
    wxBitmap resized;
    int w, h;

    SHOW_TYPE showType;
    bool isShowHoughLine;
    bool isShowSelectedLine;
    bool isRect;
    bool isOFPoint;
    bool isBotLine;
    std::vector<Detection::Line> selectedLine;
    std::vector<cv::Point2f> selectedPoint;
    double speed;

    float widthRatio;
    float heightRatio;

  public:
    void SetDefaultState();
    void calcRatio(wxDC &dc);
    cv::Point2f calcMousePos(wxPoint &mousePos);
    ImagePanel(wxPanel *parent);
    void paintEvent(wxPaintEvent &evt);
    void OnLeftDown(wxMouseEvent &e);
    void paintNow();
    void OnSize(wxSizeEvent &event);
    void render(wxDC &dc);
    bool ConvertMatBitmapTowxBitmap(const cv::Mat &matBitmap, wxBitmap &bitmap);
    void SetShowType(SHOW_TYPE showType);
    void SetImageData(ImageData &imgData);
    void SetImageData();
    void SetIsRect(bool isRect);
    void SetIsOFPoint(bool isOFPoint);
    void SetIsBotLine(bool isBotLine);
    void SetShowHoughLine(bool isShowHoughLine);
    void SetShowSelectedLine(bool isShowSelectedLine);
    void SetSpeed(double speed);
    void SetSelectedLine(std::vector<Detection::Line> &selectedLine);
    void SetSelectedPoint(std::vector<cv::Point2f> &selectedPoint);
    // void SetImage(cv::Mat &img);
    // void SetImage();

    DECLARE_EVENT_TABLE()
};

#endif