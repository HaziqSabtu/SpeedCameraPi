#ifndef BB_LANE_HPP
#define BB_LANE_HPP

#include <Utils/BufferedBitmap/BufferedBitmap.hpp>
#include <opencv2/core.hpp>

class BBLane : public BufferedBitmap {
  public:
    BBLane(wxWindow *parent, wxWindowID id);
    void ToggleHough();
    void SetLinesP(const std::vector<cv::Vec4i> &linesP);
    bool GetIsHough();

  private:
    bool isHough = false;
    std::vector<cv::Vec4i> linesP;
    void OnPaint(wxPaintEvent &e);
    wxDECLARE_EVENT_TABLE();
};

#endif