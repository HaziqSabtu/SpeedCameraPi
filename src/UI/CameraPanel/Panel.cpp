#include <UI/CameraPanel/Panel.hpp>

CameraPanel::CameraPanel(wxWindow *parent, wxWindowID id)
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

    camera.open(0);
    if (!camera.isOpened()) {
        wxMessageBox("Could not open camera", "Error", wxOK | wxICON_ERROR);
        Close();
    }
    camera.set(cv::CAP_PROP_FRAME_WIDTH, 640);
    camera.set(cv::CAP_PROP_FRAME_HEIGHT, 480);
    camera.set(cv::CAP_PROP_FPS, 30);

    timer.SetOwner(this, wxID_ANY);
    timer.Start(33); // 30 FPS

    Connect(wxID_ANY, wxEVT_TIMER, wxTimerEventHandler(CameraPanel::OnTimer));
};

CameraPanel::~CameraPanel() {
    timer.Stop();
    if (captureThread != NULL) {
        captureThread->Delete();
        captureThread = NULL;
    }
    camera.release();
}

void CameraPanel::OnTimer(wxTimerEvent &event) {
    camera >> frame;
    if (!frame.empty()) {
        img_bitmap->SetImage(frame);
    }
}

void CameraPanel::OnSize(wxSizeEvent &e) { img_bitmap->drawBitMap(); }

void CameraPanel::OnCapture() {
    if (isCapturing) {
        return;
    }
    wxLogMessage("Start Capture");
    isCapturing = true;
    isProcessing = true;
    button_panel->onCaptureToggle(isCapturing);
    imgData.clear();
    captureThread =
        new CaptureThread(&isCapturing, &isProcessing, &imgData, &frame);
    captureThread->Create();
    captureThread->Run();
}

void CameraPanel::OnStopCapture() {
    wxLogMessage("Stop Capture");
    isCapturing = false;
    button_panel->onCaptureToggle(isCapturing);
    if (captureThread != NULL) {
        captureThread->Delete();
        captureThread = NULL;
    }
    wxLogMessage("Capture Stopped");
    wxLogMessage("Image Data Size: %zd", imgData.size());
}

void CameraPanel::OnButton(wxCommandEvent &e) {
    if (e.GetId() == Enum::CP_Capture_Button_ID) {
        OnCapture();
    }

    if (e.GetId() == Enum::CP_Stop_Button_ID) {
        OnStopCapture();
    }
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
