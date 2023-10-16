#ifndef SELECT_LINE_BITMAP_HPP
#define SELECT_LINE_BITMAP_HPP

#include <Algorithm/Struct/D_Line.hpp>

#include <Utils/ImageBitmap/ImageBitmap.hpp>
class SelectLineBitmap : public ImageBitmap {
  public:
    SelectLineBitmap(wxWindow *parent, wxWindowID id,
                     const wxBitmap &bitmap = wxNullBitmap,
                     const wxPoint &pos = wxDefaultPosition,
                     const wxSize &size = wxDefaultSize, long style = 0,
                     const wxString &name = wxStaticBitmapNameStr);
    virtual ~SelectLineBitmap();

    void SetPoints(std::vector<cv::Point2f> *ptns);
    void SetHoughLines(std::vector<Line> houghLines);
    void setSelectedLines(std::vector<Line> *selectedLines);
    virtual void drawBitMap() override;

  private:
    std::vector<cv::Point2f> *ptns;
    std::vector<Line> houghLines;
    std::vector<Line> *selectedLines;

    wxDECLARE_EVENT_TABLE();
};

#endif