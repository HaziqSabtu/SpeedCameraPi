#ifndef STATIC_BITMAP_HPP
#define STATIC_BITMAP_HPP

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <wx/wx.h>

class ImageBitmap : public wxStaticBitmap {
  public:
    ImageBitmap(wxWindow *parent, wxWindowID id,
                const wxBitmap &bitmap = wxNullBitmap,
                const wxPoint &pos = wxDefaultPosition,
                const wxSize &size = wxDefaultSize, long style = 0,
                const wxString &name = wxStaticBitmapNameStr);
    void SetImage(const cv::Mat &image);
    void SetImage();
    void OnSize();
    virtual void drawBitMap();
    wxPoint GetRealMousePos(wxPoint mousePos);

  protected:
    cv::Mat image;
    cv::Mat rgbImage;
    cv::Mat noImage;

    wxSize clientSize;
    int width;
    int height;

    int resizeWidth;
    int resizeHeight;

    double imgRatio;
    double clientRatio;

    double widthRatio;
    double heightRatio;

    void processRatio();

    wxImage matToWxImage(cv::Mat &image);

    wxDECLARE_EVENT_TABLE();
};

#endif