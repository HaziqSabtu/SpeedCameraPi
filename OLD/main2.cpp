#include <wx/wx.h>

class MyApp : public wxApp {
  public:
    virtual bool OnInit();
};

class MyFrame : public wxFrame {
  public:
    MyFrame(const wxString &title, const wxPoint &pos, const wxSize &size);

  private:
    void OnButtonClick(wxCommandEvent &event);

    wxTextCtrl *textCtrl;
    wxButton *button;

    DECLARE_EVENT_TABLE()
};

enum { ID_Button = 1 };

BEGIN_EVENT_TABLE(MyFrame, wxFrame)
EVT_BUTTON(ID_Button, MyFrame::OnButtonClick)
END_EVENT_TABLE()

IMPLEMENT_APP(MyApp)

bool MyApp::OnInit() {
    MyFrame *frame =
        new MyFrame("Output to wxTextCtrl", wxPoint(50, 50), wxSize(450, 340));
    frame->Show(true);
    return true;
}

MyFrame::MyFrame(const wxString &title, const wxPoint &pos, const wxSize &size)
    : wxFrame(NULL, wxID_ANY, title, pos, size) {
    // Create a wxTextCtrl widget where the output will be displayed
    textCtrl = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxPoint(200, 200),
                              wxDefaultSize, wxTE_MULTILINE | wxTE_READONLY);

    // Create a button that will trigger the output
    button = new wxButton(this, ID_Button, "Output Text");

    // Connect the button's wxEVT_COMMAND_BUTTON_CLICKED event to a handler
    // function
    Connect(ID_Button, wxEVT_COMMAND_BUTTON_CLICKED,
            wxCommandEventHandler(MyFrame::OnButtonClick));
}

int gogo = 0;

void MyFrame::OnButtonClick(wxCommandEvent &event) {
    // Output text to the wxTextCtrl widget
    gogo = gogo + 10;
    textCtrl->AppendText(std::to_string(gogo) + "\r");
}
