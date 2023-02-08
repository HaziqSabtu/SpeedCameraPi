#include <Utils/Enum.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/videoio.hpp>
#include <wx/notebook.h>
#include <wx/wx.h>

class Panel2 : public wxPanel {
  public:
    Panel2(wxWindow *parent, wxWindowID id);
    ~Panel2();

  public:
    void OnButton(wxCommandEvent &e);
    void OnTimer(wxTimerEvent &event);
    void OnCapture(wxCommandEvent &event);
    void OnStopCapture(wxCommandEvent &event);

    cv::VideoCapture m_camera;
    wxTimer m_timer;
    wxButton *m_captureButton;
    wxButton *m_stopCaptureButton;
    wxStaticBitmap *m_bitmap;
    cv::Mat m_frame;
    bool m_isCapturing = false;
    wxCriticalSection m_criticalSection;
    std::vector<std::pair<cv::Mat, wxDateTime>> m_capturedFrames;

    wxThread *m_captureThread;

    DECLARE_EVENT_TABLE()
};

class MyCaptureThread : public wxThread {
  public:
    MyCaptureThread(Panel2 *parent)
        : wxThread(wxTHREAD_JOINABLE), m_parent(parent) {
        wxLogMessage("creating new thread");
    }
    virtual ~MyCaptureThread() {}
    virtual void *Entry() {
        cv::Mat frame;
        time_t start = time(0);
        time_t current;

        wxLogMessage("running on thread");

        while ((current = time(0)) - start < 2) {
            wxLogMessage("in while loop");
            if (TestDestroy()) {
                wxLogMessage("break");
                break;
            }
            wxLogMessage("fetching camera");
            frame = m_parent->m_frame;
            // m_parent->m_camera >> frame;
            // if (frame.empty()) {
            //     wxLogMessage("frame is empty");
            // }
            wxLogMessage("lock");
            wxCriticalSectionLocker lock(m_parent->m_criticalSection);
            wxLogMessage("pushing");
            m_parent->m_capturedFrames.push_back(
                std::make_pair(frame.clone(), current));
            wxLogMessage("done loop");
            wxThread::Sleep(100);
        }

        return NULL;
    };

    Panel2 *m_parent;
};