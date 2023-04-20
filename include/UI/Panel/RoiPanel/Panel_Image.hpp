#pragma once

#include <UI/Panel/Base/Panel_Image.hpp>

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include <wx/sizer.h>
#include <wx/wx.h>

class RoiImagePanel : public BaseImagePanel {
  public:
    wxRect rect;
    wxPoint p1;
    wxPoint p2;
    bool isDown = false;

  public:
    RoiImagePanel(wxPanel *parent);
    wxRect getRect(wxPoint p1, wxPoint p2);

  private:
    void render(wxDC &dc) override;

    wxBitmap CropBitmap(wxBitmap &originalBitmap, wxRect region);

    DECLARE_EVENT_TABLE()
};
