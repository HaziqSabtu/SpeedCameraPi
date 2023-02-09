#include <UI/CameraPanel/Panel.hpp>

CameraPanel::CameraPanel(wxWindow *parent, wxWindowID id)
    : wxPanel(parent, id) {
    button_panel = new CameraPanelButton(this, Enum::CP_BUTTON_PANEL_ID);

    img_bitmap = new ImageBitmap(this, Enum::CP_IMG_PANEL_ID);
    img_bitmap->Bind(wxEVT_SIZE, &CameraPanel::OnSize, this);

    main_sizer = new wxBoxSizer(wxVERTICAL);
    main_sizer->Add(button_panel, 0, wxEXPAND);
    main_sizer->Add(img_bitmap, 1, wxEXPAND);

    SetSizer(main_sizer);

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

    Connect(wxID_ANY, wxEVT_TIMER, wxTimerEventHandler(CameraPanel::OnTimer));
};

CameraPanel::~CameraPanel() {
    m_timer.Stop();
    if (m_captureThread != NULL) {
        m_captureThread->Delete();
        m_captureThread = NULL;
    }
    m_camera.release();
}

void CameraPanel::OnTimer(wxTimerEvent &event) {
    m_camera >> m_frame;
    if (!m_frame.empty()) {
        img_bitmap->SetImage(m_frame);
    }
}

void CameraPanel::OnSize(wxSizeEvent &e) { img_bitmap->drawBitMap(); }

void CameraPanel::OnCapture(wxCommandEvent &event) {
    if (m_isCapturing) {
        return;
    }
    // m_isCapturing = true;
    // m_captureButton->Disable();
    // m_stopCaptureButton->Enable();

    // m_captureThread = new CaptureThread();
    // m_captureThread->Create();
    // m_captureThread->Run();
}

void CameraPanel::OnStopCapture(wxCommandEvent &event) {
    // m_stopCaptureButton->Disable();
    // if (m_captureThread != NULL) {
    //     m_captureThread->Delete();
    //     m_captureThread = NULL;
    // }
    // m_isCapturing = false;
    // m_captureButton->Enable();
}

void CameraPanel::OnButton(wxCommandEvent &e) {
    if (e.GetId() == Enum::CP_Capture_Button_ID) {
        // wxLogMessage("capture");
        // img_bitmap->SetImage(m_frame);
    }
}

// clang-format off
wxBEGIN_EVENT_TABLE(CameraPanel, wxPanel) 
EVT_BUTTON(Enum::P2_C_Button_ID, CameraPanel::OnCapture)
EVT_BUTTON(Enum::P2_S_Button_ID, CameraPanel::OnStopCapture)
EVT_BUTTON(wxID_ANY, CameraPanel::OnButton)
wxEND_EVENT_TABLE()
