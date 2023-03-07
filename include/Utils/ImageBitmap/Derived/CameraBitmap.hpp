#ifndef CAMERA_BITMAP_HPP
#define CAMERA_BITMAP_HPP

#include <Utils/ImageBitmap/ImageBitmap.hpp>
#include <Utils/Struct/D_Line.hpp>

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
    void SetHoughLines(std::vector<Detection::Line> houghLines);
    void setSelectedLines(std::vector<Detection::Line> *selectedLines);
    virtual void drawBitMap() override;
    void SetImg(cv::Mat *img);

  private:
    std::vector<cv::Point2f> *ptns;
    std::vector<Detection::Line> houghLines;
    std::vector<Detection::Line> *selectedLines;

    bool *isCapturing;
    bool *isProcessing;
    wxDECLARE_EVENT_TABLE();
};

#endif