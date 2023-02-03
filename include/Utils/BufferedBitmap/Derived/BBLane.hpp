#ifndef BB_LANE_HPP
#define BB_LANE_HPP

#include <Algorithm/line_detection/lineDetection.hpp>
#include <Utils/BufferedBitmap/BufferedBitmap.hpp>
#include <opencv2/core.hpp>

class BBLane : public BufferedBitmap {
  public:
    BBLane(wxWindow *parent, wxWindowID id);
    void ToggleHough();
    void SetLinesP(const std::vector<cv::Vec4i> &linesP);
    bool GetIsHough();
    wxPoint GetRealMousePos(wxPoint mousePos);
    void addLine(cv::Vec4i line);
    void clearLines();
    std::vector<cv::Vec4i> GetDetectedLines();

  private:
    bool isHough = false;
    std::vector<cv::Vec4i> linesP;
    std::vector<cv::Vec4i> detLines;
    void OnPaint(wxPaintEvent &e);
    wxDECLARE_EVENT_TABLE();
};

#endif