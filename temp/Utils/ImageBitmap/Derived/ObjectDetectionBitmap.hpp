#ifndef OBJECT_DETECTION_BITMAP_HPP
#define OBJECT_DETECTION_BITMAP_HPP

#include <Utils/ImageBitmap/ImageBitmap.hpp>

class ObjectDetectionBitmap : public ImageBitmap {
  public:
    ObjectDetectionBitmap(wxWindow *parent, wxWindowID id,
                          const wxBitmap &bitmap = wxNullBitmap,
                          const wxPoint &pos = wxDefaultPosition,
                          const wxSize &size = wxDefaultSize, long style = 0,
                          const wxString &name = wxStaticBitmapNameStr);
    virtual ~ObjectDetectionBitmap();

    void SetBBox(cv::Rect *bbox);
    void SetBottomLine(std::vector<cv::Point2f> *bottomLine);
    void SetResult(std::vector<std::vector<cv::Point2f>> *result);
    void SetSelectedLines(std::vector<cv::Vec4i> selectedLines);
    void SetSpeed(double *speed);
    virtual void drawBitMap() override;

  private:
    cv::Rect *bbox;
    std::vector<std::vector<cv::Point2f>> *result;
    std::vector<cv::Point2f> *bottomLine;
    std::vector<cv::Vec4i> selectedLines;
    double *speed;

    wxDECLARE_EVENT_TABLE();
};

#endif