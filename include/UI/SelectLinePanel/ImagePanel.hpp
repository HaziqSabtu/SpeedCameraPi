#ifndef SELECT_LINE_PANEL_IMAGE
#define SELECT_LINE_PANEL_IMAGE

#include <Algorithm/line_detection/lineDetection.hpp>
#include <Utils/BufferedBitmap/Derived/BBLane.hpp>
#include <Utils/Enum.hpp>
#include <Utils/fileWR.hpp>
#include <wx/wx.h>

class SelectLinePanelImage : public wxPanel {
  public:
    SelectLinePanelImage(wxWindow *parent, wxWindowID id,
                         std::vector<ImgData> &imgData);
    void OnCanny();
    void OnHough();
    void OnClear();
    void checkForLine(wxPoint realMousePos);
    std::vector<cv::Vec4i> GetDetectedLines();

  private:
    int count = 0;
    bool isCanny = false;

    std::vector<ImgData> imgData;

    wxPanel *img_panel;
    BBLane *img_bitmap;
    wxBoxSizer *img_sizer;

    LineDetection lineDetection;

    void OnSize(wxSizeEvent &e);
    void OnLeftDown(wxMouseEvent &e);
    DECLARE_EVENT_TABLE();
};
#endif

/**
 * Event Propagation
 * Some event () does not propagate to parent window
 * So we need to manually propagate it with dynamically (Bind)
 */
