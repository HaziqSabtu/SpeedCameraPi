#include <Utils/Enum.hpp>
#include <wx/notebook.h>
#include <wx/wx.h>


class Panel2 : public wxPanel {
  public:
    Panel2(wxWindow *parent, wxWindowID id);

  private:
    void OnButton(wxCommandEvent &e);
    DECLARE_EVENT_TABLE()
};