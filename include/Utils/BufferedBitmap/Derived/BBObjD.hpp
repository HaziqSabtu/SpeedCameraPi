#ifndef BB_OBJECT_DETECTION2_HPP
#define BB_OBJECT_DETECTION2_HPP

#include <Utils/BufferedBitmap/BufferedBitmap.hpp>
#include <opencv2/core.hpp>

class BBObjD : public BufferedBitmap {
  public:
    BBObjD(wxWindow *parent, wxWindowID id);

  protected:
  private:
    void OnPaint(wxPaintEvent &e);
    wxDECLARE_EVENT_TABLE();
};

#endif