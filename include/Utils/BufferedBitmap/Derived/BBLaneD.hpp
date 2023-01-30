#ifndef BB_LANE_DETECTION_HPP
#define BB_LANE_DETECTION_HPP

#include <Utils/BufferedBitmap/BufferedBitmap.hpp>
#include <opencv2/core.hpp>

class BBLaneD : public BufferedBitmap {
  public:
    BBLaneD(wxWindow *parent, wxWindowID id, wxSize size);
    void RefreshBitmap();
    void OnLeftDown(wxMouseEvent &e);

  protected:
  private:
    const int IMAGE_TO_GENERATE = 9;
    const int IMAGE_PER_ROW = 3;
    const wxSize DEFAULT_IMG_SIZE;
    int RECT_WIDTH;
    int RECT_HEIGHT;

    bool isDrawRect = false;
    cv::Rect rectangle;

    void OnPaint(wxPaintEvent &e);
    wxDECLARE_EVENT_TABLE();
};

#endif