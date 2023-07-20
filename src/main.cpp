#include <UI/Frame/MainFrame.hpp>
#include <Utils/Config/AppConfig.hpp>
#include <Utils/Logger/Logger.hpp>
#include <wx/thread.h>
#include <wx/wx.h>

class MyApp : public wxApp {
  public:
    bool OnInit() {
        AppConfig conf;
        wxInitAllImageHandlers();

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
