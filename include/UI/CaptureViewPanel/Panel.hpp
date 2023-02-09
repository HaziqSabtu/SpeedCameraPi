#ifndef CAPTURE_VIEW_PANEL_HPP
#define CAPTURE_VIEW_PANEL_HPP

#include <UI/CameraPanel/Panel.hpp>
#include <UI/CaptureViewPanel/ButtonPanel.hpp>
#include <Utils/Enum.hpp>
#include <Utils/ImageBitmap/ImageBitmap.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/videoio.hpp>
#include <wx/notebook.h>
#include <wx/wx.h>

class CaptureViewPanel : public wxPanel {
  public:
    CaptureViewPanel(wxWindow *parent, wxWindowID id);
    ~CaptureViewPanel();
    void OnPageChange();

  private:
    int c = 0;

    std::vector<std::pair<cv::Mat, time_t>> imgData;

    CaptureViewPanelButton *button_panel;
    ImageBitmap *img_bitmap;

    wxBoxSizer *main_sizer;

    void OnIncrement();
    void OnDecrement();

    void OnButton(wxCommandEvent &e);
    void OnSize(wxSizeEvent &e);
    DECLARE_EVENT_TABLE()
};
#endif