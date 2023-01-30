#ifndef BB_LANE_HPP
#define BB_LANE_HPP

#include <Utils/BufferedBitmap/BufferedBitmap.hpp>
#include <opencv2/core.hpp>

class BBLane : public BufferedBitmap {
  public:
    BBLane(wxWindow *parent, wxWindowID id);

    void DrawRectangle(int x, int y, int width, int height);
    void RemoveRectangle();
    cv::Rect GetTrueRect();

  protected:
  private:
    int start_x = -1;
    int start_y = -1;
    int end_x = -1;
    int end_y = -1;

    boolean draw_rect = false;
    cv::Rect rectangle;
    cv::Rect trueRectangle;

    void processRect();

    void OnPaint(wxPaintEvent &e);
    void OnLeftDown(wxMouseEvent &e);
    void OnLeftUp(wxMouseEvent &e);
    void OnMouseMove(wxMouseEvent &e);
    wxDECLARE_EVENT_TABLE();
};

#endif