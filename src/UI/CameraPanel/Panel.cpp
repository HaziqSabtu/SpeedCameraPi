#include <UI/CameraPanel/Panel.hpp>

CameraPanel::CameraPanel(wxWindow *parent, wxWindowID id, AppConfig *config)
    : wxPanel(parent, id) {
    button_panel = new CameraPanelButton(this, Enum::CP_BUTTON_PANEL_ID);

    img_bitmap = new CameraBitmap(this, Enum::CP_IMG_PANEL_ID);
    img_bitmap->SetIsCapturing(&isCapturing);
    img_bitmap->SetIsProcessing(&isProcessing);
    img_bitmap->Bind(wxEVT_SIZE, &CameraPanel::OnSize, this);

    main_sizer = new wxBoxSizer(wxVERTICAL);
    main_sizer->Add(button_panel, 0, wxEXPAND);
    main_sizer->Add(img_bitmap, 1, wxEXPAND);

    SetSizer(main_sizer);

    SetSize(800, 600);
    Center();

    CameraConfig cameraConfig = config->GetCameraConfig();
    camera.open(cameraConfig.Camera_ID);
    if (!camera.isOpened()) {
        wxMessageBox("Could not open camera", "Error", wxOK | wxICON_ERROR);
        Close();
    }
    camera.set(cv::CAP_PROP_FRAME_WIDTH, cameraConfig.Camera_Width);
    camera.set(cv::CAP_PROP_FRAME_HEIGHT, cameraConfig.Camera_Height);
    camera.set(cv::CAP_PROP_FPS, cameraConfig.Camera_FPS);

    filePath = config->GetLoadFileName();

    // timer.SetOwner(this, wxID_ANY);
    timer.Bind(wxEVT_TIMER, &CameraPanel::OnTimer, this);
    timer.Start(config->GetCameraPanelRefreshRate()); // 30 FPS

    threadCheckTimer.Bind(wxEVT_TIMER, &CameraPanel::OnThreadCheck, this);

    isCapturing = false;
    isProcessing = false;
};

CameraPanel::~CameraPanel() {
    timer.Stop();
    if (captureThread != NULL) {
        captureThread->Delete();
        captureThread = NULL;
    }

    if (loadThread != NULL) {
        loadThread->Delete();
        loadThread = NULL;
    }
    camera.release();
}

void CameraPanel::OnTimer(wxTimerEvent &e) {
    camera >> frame;
    if (!frame.empty()) {
        img_bitmap->SetImage(frame);
    }
}

void CameraPanel::OnThreadCheck(wxTimerEvent &e) {
    if (!isThreadRunning) {
        threadCheckTimer.Stop();
        button_panel->EnableAllButtons();
    }
}

void CameraPanel::OnSize(wxSizeEvent &e) { img_bitmap->drawBitMap(); }

void CameraPanel::OnCapture() {
    if (isCapturing || isProcessing) {
        return;
    }
    wxLogMessage("Start Capture");
    button_panel->DisableAllButtons();
    isThreadRunning = true;
    imgData.clear();
    captureThread = new CaptureThread(&isCapturing, &isProcessing,
                                      &isThreadRunning, &imgData, &frame);
    captureThread->Create();
    captureThread->Run();
    threadCheckTimer.Start(100);
}

void CameraPanel::OnButton(wxCommandEvent &e) {
    if (e.GetId() == Enum::CP_Capture_Button_ID) {
        OnCapture();
    }

    if (e.GetId() == Enum::CP_Load_Button_ID) {
        OnLoadFile();
    }
}

void CameraPanel::OnLoadFile() {
    if (isCapturing || isProcessing) {
        return;
    }

    if (!imgData.empty()) {
        imgData.clear();
    }

    FILEH264::ReadFile(filePath, imgData);
    button_panel->DisableAllButtons();
    isThreadRunning = true;
    loadThread =
        new DemoThread(&isCapturing, &isProcessing, &isThreadRunning, &imgData);
    loadThread->Create();
    loadThread->Run();
    threadCheckTimer.Start(100);
}

std::vector<ImageData> CameraPanel::GetImgData() {
    if (imgData.empty()) {
        return std::vector<ImageData>();
    }
    return imgData;
}

// clang-format off
wxBEGIN_EVENT_TABLE(CameraPanel, wxPanel) 
    EVT_BUTTON(wxID_ANY, CameraPanel::OnButton)
wxEND_EVENT_TABLE()
