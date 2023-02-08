#ifndef SELECT_LINE_PANEL
#define SELECT_LINE_PANEL

#include <Algorithm/line_detection/lineDetection.hpp>
#include <UI/SelectLinePanel/ButtonPanel.hpp>
#include <Utils/Enum.hpp>
#include <Utils/ImageBitmap/Derived/SelectLineBitmap.hpp>
#include <Utils/fileWR.hpp>
#include <wx/wx.h>

class SelectLinePanel : public wxPanel {
  public:
    SelectLinePanel(wxWindow *parent, wxWindowID id,
                    std::vector<ImgData> &imgData);
    ~SelectLinePanel();

    std::vector<cv::Vec4i> GetSelectedLines();

  private:
    SelectLinePanelButton *button_panel;
    SelectLineBitmap *img_bitmap;

    std::vector<ImgData> imgData;
    std::vector<cv::Point2f> *ptns;
    std::vector<cv::Vec4i> *houghLines;
    std::vector<cv::Vec4i> *selectedLines;

    LineDetection lineDetection;

    int c = 0;

    bool isCanny;
    bool isHough;

    wxBoxSizer *main_sizer;

    void OnButton(wxCommandEvent &e);
    void OnLeftDown(wxMouseEvent &e);
    void OnSize(wxSizeEvent &e);

    void checkForLine(wxPoint realMousePos);
    void addLine(cv::Vec4i line);
    void addPoints(wxPoint realMousePos);

    DECLARE_EVENT_TABLE()
};
#endif
