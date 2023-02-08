#ifndef BIT_HPP
#define BIT_HPP

#include <Utils/ImageBitmap/Derived/SelectLineBitmap.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include <wx/wx.h>
class Bit : public wxPanel {
  public:
    cv::Mat img;
    Bit(wxWindow *parent, wxWindowID id);

    void OnSize(wxSizeEvent &e);
    void OnLeftDown(wxMouseEvent &e);
    void SetImage(cv::Mat &img);

    std::vector<cv::Point2f> *ptns;

    SelectLineBitmap *m_bitmap;
    wxDECLARE_EVENT_TABLE();
};

#endif