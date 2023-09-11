#pragma once

#include "UI/Data/Theme.hpp"
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include <wx/gdicmn.h>
#include <wx/sizer.h>
#include <wx/wx.h>

class BaseImagePanel : public wxPanel {
  protected:
    wxBitmap noImageBitmap;
    wxBitmap errorBitmap;
    wxBitmap image;
    wxBitmap resized;

    int w, h;

    float widthRatio;
    float heightRatio;

    wxRect rect;
    wxPoint p1;
    bool isDown = false;

    const wxString noImage = Theme::noImageIcon;

    const int DEF_WIDTH = 640;
    const int DEF_HEIGHT = 480;

  public:
    BaseImagePanel(wxPanel *parent);

    void setImage(wxBitmap &image);
    void setNoImage();

    wxSize getImageSize();

  protected:
    virtual void render(wxDC &dc);
    void calcRatio(wxDC &dc);
    const wxBitmap createBitmapText(wxString text);
    const wxBitmap createBitmapPNG(wxString fileName);
    wxBitmap resize(wxBitmap &bitmap, const wxSize &size);

    void OnPaint(wxPaintEvent &e);
    void OnSize(wxSizeEvent &e);

    DECLARE_EVENT_TABLE()
};
