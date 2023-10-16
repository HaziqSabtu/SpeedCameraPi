#ifndef CAMERA_BITMAP_HPP
#define CAMERA_BITMAP_HPP

#include <Algorithm/Struct/D_Line.hpp>

#include <Utils/ImageBitmap/ImageBitmap.hpp>
class CameraBitmap : public ImageBitmap {
  public:
    CameraBitmap(wxWindow *parent, wxWindowID id,
                 const wxBitmap &bitmap = wxNullBitmap,
                 const wxPoint &pos = wxDefaultPosition,
                 const wxSize &size = wxDefaultSize, long style = 0,
                 const wxString &name = wxStaticBitmapNameStr);
    virtual ~CameraBitmap();

    void SetIsCapturing(bool *isCapturing);
    void SetIsProcessing(bool *isProcessing);
    void SetPoints(std::vector<cv::Point2f> *ptns);
    void SetHoughLines(std::vector<Line> houghLines);
    void setSelectedLines(std::vector<Line> *selectedLines);
    virtual void drawBitMap() override;
    void SetImg(cv::Mat *img);

  private:
    std::vector<cv::Point2f> *ptns;
    std::vector<Line> houghLines;
    std::vector<Line> *selectedLines;

    bool *isCapturing;
    bool *isProcessing;
    wxDECLARE_EVENT_TABLE();
};

#endif