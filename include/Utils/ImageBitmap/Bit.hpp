#ifndef BIT_HPP
#define BIT_HPP

#include <Utils/DataStruct.hpp>
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

class wxImagePanel : public wxPanel {
    cv::Mat image, noImage;
    ImageData imgData;
    wxBitmap resized;
    int w, h;
    SHOW_TYPE showType;
    bool isShowHoughLine;

  public:
    wxImagePanel(wxPanel *parent);

    void paintEvent(wxPaintEvent &evt);
    void paintNow();
    void OnSize(wxSizeEvent &event);
    void render(wxDC &dc);
    bool ConvertMatBitmapTowxBitmap(const cv::Mat &matBitmap, wxBitmap &bitmap);
    void SetShowType(SHOW_TYPE showType);
    void SetImageData(ImageData &imgData);
    void SetImageData();
    void SetShowHoughLine(bool isShowHoughLine);
    // void SetImage(cv::Mat &img);
    // void SetImage();

    DECLARE_EVENT_TABLE()
};

#endif