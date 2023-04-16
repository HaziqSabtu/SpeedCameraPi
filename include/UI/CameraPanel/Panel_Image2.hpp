#ifndef PANEL_IMAGE2_HPP
#define PANEL_IMAGE2_HPP

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <wx/sizer.h>
#include <wx/wx.h>

class ImagePanelBitmap : public wxPanel {
    wxBitmap noImageBitmap;
    wxBitmap errorBitmap;
    wxBitmap image;
    wxBitmap resized;

    int w, h;

    float widthRatio;
    float heightRatio;

  public:
    ImagePanelBitmap(wxPanel* parent);

    void setImage(wxBitmap& image);
    void setNoImage();

  private:
    void render(wxDC& dc);
    void calcRatio(wxDC& dc);
    const wxBitmap createBitmap(std::string text);
    wxBitmap resize(wxBitmap& bitmap, const wxSize& size);

    void onPaint(wxPaintEvent& e);
    void onSize(wxSizeEvent& e);

    DECLARE_EVENT_TABLE()
};

#endif