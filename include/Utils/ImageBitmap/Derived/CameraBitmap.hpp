#ifndef CAMERA_BITMAP_HPP
#define CAMERA_BITMAP_HPP

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
    virtual void drawBitMap() override;

  private:
    // std::vector<cv::Point2f> *ptns;
    bool *isCapturing;
    bool *isProcessing;
    wxDECLARE_EVENT_TABLE();
};

#endif