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
    void SetImage(const cv::Mat &image);
    void DrawRectangle(int x, int y, int width, int height);
    void DrawRectangle(wxPoint p1, wxPoint p2);
    void RemoveRectangle();
    void setClientSize(wxSize size);

  private:
    cv::Rect rectangle;
    cv::Rect trueRectangle;

    bool draw_rect = false;

    int resizeWidth;
    int resizeHeight;

    double imgRatio;
    double clientRatio;

    double widthRatio;
    double heightRatio;

    wxSize client_size;
    wxSize client_size2 = wxSize(-1, -1);
    int start_x = -1, start_y = -1, end_x = -1, end_y = -1;
    void OnPaint(wxPaintEvent &event);
    void OnLeftDown(wxMouseEvent &event);
    void OnLeftUp(wxMouseEvent &event);
    void OnMouseMove(wxMouseEvent &e);

    wxImage matToWxImage(const cv::Mat &mat);
    inline void processRatio();
    wxDECLARE_EVENT_TABLE();
};

#endif