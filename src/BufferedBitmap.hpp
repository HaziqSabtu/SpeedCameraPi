#ifndef BUFFERED_BITMAP_HPP
#define BUFFERED_BITMAP_HPP

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <wx/dcbuffer.h>
#include <wx/wx.h>

class BufferedBitmap : public wxStaticBitmap {
    cv::Mat img;
    cv::Mat RGBImg;
    // Double buffering: To fix screen flickering. This can be done by creating
    // a wxBufferedPaintDC instead of a wxPaintDC when the control is repainted.
    // This creates a bitmap in memory that is used to draw the new image, then
    // the memory bitmap is drawn on the window, this will avoid flickering by
    // avoiding the immediate repainting on the control.
  public:
    BufferedBitmap(wxWindow *parent, wxWindowID id);
    void BufferedBitmap::SetImage(const cv::Mat &image);
    void BufferedBitmap::OnPaint(wxPaintEvent &event);
    wxImage BufferedBitmap::matToWxImage(const cv::Mat &mat);
    wxDECLARE_EVENT_TABLE();
};

#endif