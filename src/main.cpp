#include <UI/MainFrame.hpp>
#include <Utils/Logger.hpp>
#include <wx/wx.h>

class MyApp : public wxApp {
  public:
    bool OnInit() {
        // wxLog *logger = new Logger();
        wxLog::SetActiveTarget(new AppLogger);
        wxLogMessage("Application Started");
        MainFrame *frame = new MainFrame("Speed Gun");
        frame->Show(true);
        return true;
    }

    virtual int OnExit() {
        wxLogMessage("Application Closed");
        return wxApp::OnExit();
    }
};

wxIMPLEMENT_APP(MyApp);
