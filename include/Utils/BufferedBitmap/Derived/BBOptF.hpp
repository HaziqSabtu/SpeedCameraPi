#ifndef BB_OPTICAL_FLOW_HPP
#define BB_OPTICAL_FLOW_HPP

#include <Utils/BufferedBitmap/BufferedBitmap.hpp>
#include <opencv2/core.hpp>

class BBOpticalFlow : public BufferedBitmap {
  public:
    BBOpticalFlow(wxWindow *parent, wxWindowID id);

  private:
    void OnPaint(wxPaintEvent &e);
    // wxDECLARE_EVENT_TABLE();
};

#endif