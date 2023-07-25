#include <UI/Frame/MainFrame.hpp>
#include <Utils/Config/AppConfig.hpp>
#include <Utils/Logger/Logger.hpp>
#include <wx/thread.h>
#include <wx/utils.h>
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
        wxWakeUpIdle();

        std::cerr << "Application Closed" << std::endl;
        return wxApp::OnExit();
    }
};

wxIMPLEMENT_APP(MyApp);
