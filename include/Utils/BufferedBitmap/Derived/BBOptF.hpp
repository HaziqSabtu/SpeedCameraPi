#ifndef BB_OPTICAL_FLOW_HPP
#define BB_OPTICAL_FLOW_HPP

#include <Utils/BufferedBitmap/BufferedBitmap.hpp>
#include <opencv2/core.hpp>

class BBOpticalFlow : public BufferedBitmap {
  public:
    BBOpticalFlow(wxWindow *parent, wxWindowID id);
    void SetTrueRect(cv::Rect r);
    cv::Rect GetTrueRect();
    void ToggleDrawRect();

  private:
    boolean draw_rect = false;
    cv::Rect rectangle;
    cv::Rect trueRectangle;

    void OnPaint(wxPaintEvent &e);
    wxDECLARE_EVENT_TABLE();
};

#endif