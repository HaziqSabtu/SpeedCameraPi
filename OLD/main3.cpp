// wxWidgets "Hello world" Program
// For compilers that support precompilation, includes "wx/wx.h".
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

class MyApp : public wxApp {
  public:
    virtual bool OnInit();
};
int gogo = 0;

wxIMPLEMENT_APP(MyApp);

class MyFrame : public wxFrame {
  public:
    MyFrame(const wxString &title, const wxPoint &pos, const wxSize &size);

  private:
    void OnClick(wxCommandEvent &);
    wxDECLARE_EVENT_TABLE();
};

enum ButtonId { first_button_id = wxID_LAST + 1, other_button_id };

// clang-format off

wxBEGIN_EVENT_TABLE(MyFrame, wxFrame)
EVT_BUTTON(wxID_ANY, MyFrame::OnClick)
wxEND_EVENT_TABLE()

; // clang-format on

class MyPanel : public wxPanel {
  public:
    MyPanel(wxWindow *parent);
    void changeBG(int col);

  private:
    void OnClick(wxCommandEvent &);
    wxDECLARE_EVENT_TABLE();
};

MyPanel::MyPanel(wxWindow *parent) : wxPanel(parent) {
    this->SetBackgroundColour(wxColor(gogo, gogo, gogo));
}

void MyPanel::changeBG(int col) {
    this->SetBackgroundColour(wxColor(col, col, col));
}

void MyPanel::OnClick(wxCommandEvent &e) {
    std::cout << "PANEL OnClick, id = " << e.GetId() << std::endl;
    gogo = gogo + 10;
    Refresh();
}

// clang-format off

wxBEGIN_EVENT_TABLE(MyPanel, wxPanel)
EVT_BUTTON(wxID_ANY, MyPanel::OnClick)
wxEND_EVENT_TABLE()

; // clang-format on

bool MyApp::OnInit() {
    MyFrame *frame =
        new MyFrame("Hello World", wxDefaultPosition, wxSize(1024, 768));
    frame->Show(true);
    return true;
}

MyFrame::MyFrame(const wxString &title, const wxPoint &pos, const wxSize &size)
    : wxFrame(nullptr, wxID_ANY, title, pos, size,
              wxMINIMIZE_BOX | wxMAXIMIZE_BOX | wxSYSTEM_MENU | wxCAPTION |
                  wxCLOSE_BOX | wxCLIP_CHILDREN) {
    int panelWidth = this->GetClientSize().GetWidth() / 2;
    int panelHeight = this->GetClientSize().GetHeight();

    MyPanel *panel_left = new MyPanel(this);
    panel_left->changeBG(gogo);
    auto button = new wxButton(panel_left, first_button_id, "Click me");
    auto sizer = new wxBoxSizer(wxHORIZONTAL);
    Connect(first_button_id, wxEVT_COMMAND_BUTTON_CLICKED,
            wxCommandEventHandler(MyFrame::OnClick));
    sizer->Add(button, 0, wxCenter);
    // panel_left->SetSizerAndFit(sizer);
    // wxPanel *panel_left = new wxPanel(this, wxID_ANY, wxDefaultPosition,
    //                                   wxSize(panelWidth, panelHeight));
    // panel_left->SetBackgroundColour(wxColor(100, 100, 255));

    // wxPanel *panel_right = new wxPanel(this, wxID_ANY, wxDefaultPosition,
    //                                    wxSize(panelWidth, panelHeight));
    // panel_right->SetBackgroundColour(wxColor(100, 255, 100));

    // wxBoxSizer *sizer2 = new wxBoxSizer(wxHORIZONTAL);
    // sizer2->Add(panel_left, 1);
    // sizer->Add(panel_right, 0);

    // this->SetSizerAndFit(sizer2);
}

void MyFrame::OnClick(wxCommandEvent &e) {
    std::cout << "Hey, button clicked. It's id = " << e.GetId() << std::endl;
    wxLogDebug("Hey, button clicked. It's id = %d", e.GetId());
    gogo += 10;
    Refresh();
}
