#ifndef SELECT_LINE_PANEL
#define SELECT_LINE_PANEL

#include <UI/SelectLinePanel/ButtonPanel.hpp>
#include <UI/SelectLinePanel/ImagePanel.hpp>
#include <Utils/Enum.hpp>
#include <Utils/fileWR.hpp>
#include <wx/wx.h>

class SelectLinePanel : public wxPanel {
  public:
    SelectLinePanel(wxWindow *parent, wxWindowID id,
                    std::vector<ImgData> &imgData);

  private:
    SelectLinePanelButton *button_panel;
    SelectLinePanelImage *img_panel;

    wxBoxSizer *main_sizer;

    void OnButton(wxCommandEvent &e);
    void OnLeftDown(wxMouseEvent &e);

    DECLARE_EVENT_TABLE()
};
#endif
