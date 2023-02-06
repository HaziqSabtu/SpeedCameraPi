#ifndef BUFFERED_BITMAP_HPP
#define BUFFERED_BITMAP_HPP

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <wx/dcbuffer.h>
#include <wx/wx.h>

class BufferedBitmap : public wxStaticBitmap {

    // Double buffering: To fix screen flickering. This can be done by creating
    // a wxBufferedPaintDC instead of a wxPaintDC when the control is repainted.
    // This creates a bitmap in memory that is used to draw the new image, then
    // the memory bitmap is drawn on the window, this will avoid flickering by
    // avoiding the immediate repainting on the control.
  public:
    BufferedBitmap(wxWindow *parent, wxWindowID id);
    void SetImage(const cv::Mat &image);
    double GetWidthRatio();
    double GetHeightRatio();

  protected:
    cv::Mat img;
    cv::Mat RGBImg;

    wxSize client_size;

    int width;
    int height;

    int resizeWidth;
    int resizeHeight;

    double imgRatio;
    double clientRatio;

    double widthRatio;
    double heightRatio;

    void processRatio();
    wxImage matToWxImage(const cv::Mat &mat);

  private:
    virtual void OnPaint(wxPaintEvent &e) = 0;

    wxDECLARE_EVENT_TABLE();
};

// inline method should be defined in the header file
// -> avoid linker error
// https://isocpp.org/wiki/faq/inline-functions#where-to-put-inline-keyword
inline void BufferedBitmap::processRatio() {
    client_size = GetClientSize();

    width = client_size.GetWidth();
    height = client_size.GetHeight();

    imgRatio = (double)img.cols / (double)img.rows;
    clientRatio = (double)width / (double)height;

    if (imgRatio > clientRatio) {
        resizeWidth = width;
        resizeHeight = (int)((double)width / imgRatio);
    } else {
        resizeHeight = height;
        resizeWidth = (int)((double)height * imgRatio);
    }


    widthRatio = (double)img.cols / (double)resizeWidth;
    heightRatio = (double)img.rows / (double)resizeHeight;


    std::cout << "width: " << width << std::endl;
    std::cout << "height: " << height << std::endl;
    std::cout << "imgRatio: " << imgRatio << std::endl;
    std::cout << "clientRatio: " << clientRatio << std::endl;
    std::cout << "resizeWidth: " << resizeWidth << std::endl;
    std::cout << "resizeHeight: " << resizeHeight << std::endl;
    std::cout << "widthRatio: " << widthRatio << std::endl;
    std::cout << "heightRatio: " << heightRatio << std::endl;
}

#endif