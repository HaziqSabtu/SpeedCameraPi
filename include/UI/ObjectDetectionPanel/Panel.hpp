#ifndef OBJECT_DETECTION_PANEL
#define OBJECT_DETECTION_PANEL

#include <UI/ObjectDetectionPanel/ButtonPanel.hpp>
#include <UI/ObjectDetectionPanel/ImagePanel.hpp>
#include <Utils/Enum.hpp>
#include <Utils/fileWR.hpp>
#include <wx/wx.h>

class ObjectDetectionPanel : public wxPanel {
  public:
    ObjectDetectionPanel(wxWindow *parent, wxWindowID id,
                         std::vector<ImgData> &imgData);

  private:
    ObjectDetectionPanelButton *button_panel;
    ObjectDetectionPanelImage *img_panel;

    wxBoxSizer *main_sizer;

    void OnButton(wxCommandEvent &e);

    DECLARE_EVENT_TABLE()
};
#endif
