#ifndef SELECT_ROI_PANEL
#define SELECT_ROI_PANEL

#include <UI/SelectROIPanel/ButtonPanel.hpp>
#include <UI/SelectROIPanel/ImagePanel.hpp>
#include <Utils/Enum.hpp>
#include <Utils/fileWR.hpp>
#include <wx/wx.h>

class SelectRoiPanel : public wxPanel {
  public:
    SelectRoiPanel(wxWindow *parent, wxWindowID id,
                   std::vector<ImgData> &imgData);

  private:
    SelectRoiPanelButton *button_panel;
    SelectRoiPanelImage *img_panel;

    wxBoxSizer *main_sizer;

    DECLARE_EVENT_TABLE()
};
#endif
