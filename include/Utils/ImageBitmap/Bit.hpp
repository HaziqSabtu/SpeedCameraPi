#ifndef BIT_HPP
#define BIT_HPP

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <wx/rawbmp.h>
#include <wx/sizer.h>
#include <wx/wx.h>

class wxImagePanel : public wxPanel {
    cv::Mat image, noImage;
    wxBitmap resized;
    int w, h;

  public:
    wxImagePanel(wxPanel *parent);

    void paintEvent(wxPaintEvent &evt);
    void paintNow();
    void OnSize(wxSizeEvent &event);
    void render(wxDC &dc);
    bool ConvertMatBitmapTowxBitmap(const cv::Mat &matBitmap, wxBitmap &bitmap);

    void SetImage(cv::Mat &img);
    void SetImage();

    DECLARE_EVENT_TABLE()
};

#endif