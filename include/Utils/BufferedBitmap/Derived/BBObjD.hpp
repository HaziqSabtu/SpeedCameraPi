#ifndef BB_OBJECT_DETECTION2_HPP
#define BB_OBJECT_DETECTION2_HPP

#include <Utils/BufferedBitmap/BufferedBitmap.hpp>
#include <opencv2/core.hpp>

class BBObjD : public BufferedBitmap {
  public:
    BBObjD(wxWindow *parent, wxWindowID id);
    void toggleBBox();
    void toggleOptF();
    void toggleBotL();
    bool GetIsBBox();
    bool GetIsOptF();
    bool GetIsBotL();
    void SetRect(cv::Rect r);
    void setPoints(std::vector<std::vector<cv::Point2f>> p);
    void setBotL(std::vector<cv::Point2f> p);

  protected:
  private:
    bool isBBox = false;
    bool isOptF = false;
    bool isBotL = false;

    cv::Rect rect;
    std::vector<std::vector<cv::Point2f>> points;
    std::vector<cv::Point2f> botL;

    void OnPaint(wxPaintEvent &e);
    wxDECLARE_EVENT_TABLE();
};

#endif