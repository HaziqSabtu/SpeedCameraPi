#include <UI/Panel2.hpp>

Panel2::Panel2(wxWindow *parent, wxWindowID id) : wxPanel(parent, id) {
    wxButton *next_button = new wxButton(this, Enum::NEXT_PANEL_ID, "Next");
    wxButton *prev_button = new wxButton(this, Enum::PREV_PANEL_ID, "Prev");
    m_captureButton = new wxButton(this, Enum::P2_C_Button_ID, "Start Capture");
    m_stopCaptureButton =
        new wxButton(this, Enum::P2_S_Button_ID, "Stop Capture");

    wxBoxSizer *ButtonSizer = new wxBoxSizer(wxHORIZONTAL);
    ButtonSizer->Add(next_button, 0, wxALL, 5);
    ButtonSizer->Add(prev_button, 0, wxALL, 5);
    ButtonSizer->Add(m_captureButton, 0, wxALL, 5);
    ButtonSizer->Add(m_stopCaptureButton, 0, wxALL, 5);
    m_bitmap = new wxStaticBitmap(this, wxID_ANY, wxBitmap(320, 240));

    wxBoxSizer *panelSizer = new wxBoxSizer(wxVERTICAL);
    panelSizer->Add(ButtonSizer);
    panelSizer->Add(m_bitmap);

    SetSizer(panelSizer);

    SetSize(800, 600);
    Center();

    m_camera.open(0);
    if (!m_camera.isOpened()) {
        wxMessageBox("Could not open camera", "Error", wxOK | wxICON_ERROR);
        Close();
    }
    m_camera.set(cv::CAP_PROP_FRAME_WIDTH, 640);
    m_camera.set(cv::CAP_PROP_FRAME_HEIGHT, 480);
    m_camera.set(cv::CAP_PROP_FPS, 30);

    m_timer.SetOwner(this, wxID_ANY);
    m_timer.Start(33); // 30 FPS

    // Bind(wxEVT_TIMER, &Panel2::OnTimer, this);
    Connect(wxID_ANY, wxEVT_TIMER, wxTimerEventHandler(Panel2::OnTimer));
    // Connect(wxID_ANY, wxEVT_COMMAND_BUTTON_CLICKED,
    // wxCommandEventHandler(Panel2::OnCapture)); Connect(wxID_ANY,
    // wxEVT_COMMAND_BUTTON_CLICKED,
    // wxCommandEventHandler(Panel2::OnStopCapture));
};

Panel2::~Panel2() {
    m_timer.Stop();
    if (m_captureThread != NULL) {
        m_captureThread->Delete();
        m_captureThread = NULL;
    }
    m_camera.release();
}

void Panel2::OnTimer(wxTimerEvent &event) {
    m_camera >> m_frame;
    if (!m_frame.empty()) {
        wxImage image = wxImage(m_frame.cols, m_frame.rows, m_frame.data, true);
        m_bitmap->SetBitmap(wxBitmap(image));
        Refresh();
    }
}

void Panel2::OnCapture(wxCommandEvent &event) {
    wxLogMessage("capture");
    if (m_isCapturing) {
        wxLogMessage("im returnunig");
        return;
    }
    wxLogMessage("capture2");

    m_isCapturing = true;
    wxLogMessage("capture21");

    // m_captureButton->Disable();
    wxLogMessage("capture22");

    // m_stopCaptureButton->Enable();
    wxLogMessage("capture31");

    m_captureThread = new MyCaptureThread(this);
    m_captureThread->Create();
    m_captureThread->Run();
    wxLogMessage("capture4");
}

void Panel2::OnStopCapture(wxCommandEvent &event) {
    // m_stopCaptureButton->Disable();
    wxLogMessage("stopping");
    if (m_captureThread != NULL) {
        wxLogMessage("thread not null");
        m_captureThread->Delete();
        wxLogMessage("thread deleted");
        m_captureThread = NULL;
    }
    wxLogMessage("thread already null");
    m_isCapturing = false;
    // m_captureButton->Enable();
    std::cout << "collected data: " << m_capturedFrames.size() << std::endl;
}

void Panel2::OnButton(wxCommandEvent &e) {
    wxNotebook *notebook = (wxNotebook *)FindWindowById(Enum::NOTEBOOK_ID);
    int current_page = notebook->GetSelection();
    if (e.GetId() == Enum::NEXT_PANEL_ID) {
        if (current_page < notebook->GetPageCount() - 1) {
            notebook->SetSelection(current_page + 1);
        }
    } else if (e.GetId() == Enum::PREV_PANEL_ID) {
        if (current_page > 0) {
            notebook->SetSelection(current_page - 1);
        }
    }
}

// clang-format off
wxBEGIN_EVENT_TABLE(Panel2, wxPanel) 
EVT_BUTTON(Enum::P2_C_Button_ID, Panel2::OnCapture)
EVT_BUTTON(Enum::P2_S_Button_ID, Panel2::OnStopCapture)
EVT_BUTTON(wxID_ANY, Panel2::OnButton)
wxEND_EVENT_TABLE()


// void *MyCaptureThread::Entry()
// {
//     cv::Mat frame;
//     time_t start = time(0);
//     time_t current;

//     while ((current = time(0)) - start < 2)
//     {
//         if (TestDestroy())
//             break;
//         m_parent->m_camera >> frame;
//         wxCriticalSectionLocker lock(m_parent->m_criticalSection);
//         m_parent->m_capturedFrames.push_back(std::make_pair(frame.clone(), current));
//     }

//     return NULL;
// }
