#pragma once

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

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

  public:
    BaseImagePanel(wxPanel *parent);

    void setImage(wxBitmap &image);
    void setNoImage();

  protected:
    virtual void render(wxDC &dc);
    void calcRatio(wxDC &dc);
    const wxBitmap createBitmap(std::string text);
    wxBitmap resize(wxBitmap &bitmap, const wxSize &size);

    void OnPaint(wxPaintEvent &e);
    void OnSize(wxSizeEvent &e);

    DECLARE_EVENT_TABLE()
};
