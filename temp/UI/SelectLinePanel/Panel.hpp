#ifndef SELECT_LINE_PANEL
#define SELECT_LINE_PANEL

#include <>
#include <Algorithm/Struct/D_Line.hpp>
#include <UI/CameraPanel/Panel.hpp>
#include <UI/SelectLinePanel/ButtonPanel.hpp>
#include <Utils/Enum.hpp>
#include <Utils/FileReader/fileWR.hpp>
#include <Utils/ImageBitmap/Derived/SelectLineBitmap.hpp>
#include <wx/wx.h>

class SelectLinePanel : public wxPanel {
  public:
    SelectLinePanel(wxWindow *parent, wxWindowID id);
    ~SelectLinePanel();

    std::vector<Line> GetSelectedLines();
    std::vector<ImageData> GetImgData();
    void OnPageChange();

  private:
    SelectLinePanelButton *button_panel;
    SelectLineBitmap *img_bitmap;

    std::vector<ImageData> imgData;
    std::vector<cv::Point2f> *ptns;
    std::vector<cv::Vec4i> *houghLines;
    std::vector<Line> *selectedLines;

    LineDetection lineDetection;

    int c = 0;

    bool isCanny;
    bool isHough;

    wxBoxSizer *main_sizer;

    void OnButton(wxCommandEvent &e);
    void OnLeftDown(wxMouseEvent &e);
    void OnSize(wxSizeEvent &e);
    void OnIncrement();
    void OnDecrement();

    void checkForLine(wxPoint realMousePos);
    void addLine(Line line);
    void addPoints(wxPoint realMousePos);

    DECLARE_EVENT_TABLE()
};
#endif
