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
    void toggleLine();

    bool GetIsBBox();
    bool GetIsOptF();
    bool GetIsBotL();
    bool GetIsLine();

    void SetRect(cv::Rect r);
    void SetPoints(std::vector<std::vector<cv::Point2f>> p);
    void SetBotL(std::vector<cv::Point2f> p);
    void SetLine(std::vector<cv::Vec4i> l);

    std::vector<cv::Vec4i> GetLine();

  protected:
  private:
    bool isBBox = false;
    bool isOptF = false;
    bool isBotL = false;
    bool isLine = false;

    cv::Rect rect;
    std::vector<std::vector<cv::Point2f>> points;
    std::vector<cv::Point2f> botL;
    std::vector<cv::Vec4i> line;

    void OnPaint(wxPaintEvent &e);
    wxDECLARE_EVENT_TABLE();
};

#endif