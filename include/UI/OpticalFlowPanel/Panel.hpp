#ifndef OPTICAL_FLOW_PANEL
#define OPTICAL_FLOW_PANEL

#include <UI/OpticalFlowPanel/ButtonPanel.hpp>
#include <UI/OpticalFlowPanel/ImagePanel.hpp>
#include <Utils/Enum.hpp>
#include <Utils/fileWR.hpp>
#include <wx/wx.h>

class OpticalFlowPanel : public wxPanel {
  public:
    OpticalFlowPanel(wxWindow *parent, wxWindowID id,
                     std::vector<ImgData> &imgData);

  private:
    OpticalFlowPanelButton *button_panel;
    OpticalFlowPanelImage *img_panel;

    wxBoxSizer *main_sizer;

    DECLARE_EVENT_TABLE()
};
#endif
