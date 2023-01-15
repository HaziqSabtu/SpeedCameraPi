#ifndef BB_LANE_DETECTION_HPP
#define BB_LANE_DETECTION_HPP

#include <Utils/BufferedBitmap/BufferedBitmap.hpp>
#include <opencv2/core.hpp>

class BBLaneD : public BufferedBitmap {
  public:
    BBLaneD(wxWindow *parent, wxWindowID id);
    void RefreshBitmap();

  protected:
  private:
    void OnPaint(wxPaintEvent &e);
    wxDECLARE_EVENT_TABLE();
};

#endif