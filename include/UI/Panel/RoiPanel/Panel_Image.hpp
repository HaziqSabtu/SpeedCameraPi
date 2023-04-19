#pragma once

#include <UI/Panel/Base/Panel_Image.hpp>

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include <wx/sizer.h>
#include <wx/wx.h>

class RoiImagePanel : public BaseImagePanel {
  private:
    wxRect rect;
    wxPoint p1;

    bool isDown = false;

  public:
    RoiImagePanel(wxPanel *parent);

  private:
    void render(wxDC &dc) override;

    wxBitmap CropBitmap(wxBitmap &originalBitmap, wxRect region);
    wxRect getRect(wxPoint p1, wxPoint p2);

    void OnLeftDown(wxMouseEvent &e);
    void OnLeftUp(wxMouseEvent &e);
    void OnMotion(wxMouseEvent &e);

    DECLARE_EVENT_TABLE()
};
