#include <UI/CameraPanel/Panel.hpp>

CameraPanel::CameraPanel(wxWindow *parent, wxWindowID id, AppConfig *config)
    : wxPanel(parent, id), threadPool(3) {
    button_panel = new CameraPanelButton(this, Enum::CP_BUTTON_PANEL_ID);

    ptns = new std::vector<cv::Point2f>();

    img_bitmap = new CameraBitmap(this, Enum::CP_IMG_PANEL_ID);
    img_bitmap->SetIsCapturing(&isCapturing);
    img_bitmap->SetIsProcessing(&isProcessing);
    img_bitmap->SetPoints(ptns);
    img_bitmap->Bind(wxEVT_SIZE, &CameraPanel::OnSize, this);
    img_bitmap->Bind(wxEVT_LEFT_DOWN, &CameraPanel::OnLeftDown, this);

    main_sizer = new wxBoxSizer(wxVERTICAL);
    main_sizer->Add(button_panel, 0, wxEXPAND);
    main_sizer->Add(img_bitmap, 1, wxEXPAND);

    SetSizer(main_sizer);
    Fit();

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
    maxLoadFrame = config->GetMaxLoadFrame();

    timer.Bind(wxEVT_TIMER, &CameraPanel::OnTimer, this);
    timer.Start(config->GetCameraPanelRefreshRate());

    threadCheckTimer.Bind(wxEVT_TIMER, &CameraPanel::OnThreadCheck, this);

    isCapturing = false;
    isProcessing = false;
};

CameraPanel::~CameraPanel() {
    if (captureThread != NULL) {
        captureThread->Delete();
        captureThread = NULL;
    }

    if (loadThread != NULL) {
        loadThread->Delete();
        loadThread = NULL;
    }

    if (camera.isOpened()) {
        camera.release();
    }
}

void CameraPanel::OnTimer(wxTimerEvent &e) {
    if (!isTimerRunning) {
        img_bitmap->SetImage();
        return;
    }
    camera >> frame;
    if (!frame.empty()) {
        img_bitmap->SetImage(frame);
    }
}

void CameraPanel::OnLeftDown(wxMouseEvent &e) {
    wxLogMessage("Left Down");
    wxPoint mousePos = e.GetPosition();
    wxPoint realPos = img_bitmap->GetRealMousePos(mousePos);
    addPoints(realPos);
    // checkForLine(realPos);
    img_bitmap->drawBitMap();
}

void CameraPanel::addPoints(wxPoint realMousePos) {
    if (ptns == NULL) {
        ptns = new std::vector<cv::Point2f>();
        img_bitmap->SetPoints(ptns);
    }
    ptns->push_back(cv::Point2f(realMousePos.x, realMousePos.y));
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

    isProcessing = true;
    const int max = 5;

    if (!imgData.empty()) {
        imgData.clear();
    }

    button_panel->DisableAllButtons();
    timer.Stop();
    // OnToggleCamera();

    captureExecutor(max);
    img_bitmap->SetImage(imgData[0].image);

    siftExecutor(max);

    isProcessing = false;

    for (int i = 0; i < max; i++) {
        img_bitmap->SetImage(imgData[i].image);
        wxYield();
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }

    for (int i = 1; i < max; i++) {
        double time = imgData[i].TimeDiff(imgData[i - 1]);
        std::cout << "Time Diff: " << time << std::endl;
    }

    // OnToggleCamera();
    button_panel->EnableAllButtons();
}

void CameraPanel::OnButton(wxCommandEvent &e) {
    if (e.GetId() == Enum::CP_Capture_Button_ID) {
        OnCapture();
    }

    if (e.GetId() == Enum::CP_Load_Button_ID) {
        OnLoadFile();
    }

    if (e.GetId() == Enum::CP_Camera_Button_ID) {
        OnToggleCamera();
    }
}

void CameraPanel::OnLoadFile() {
    if (isCapturing || isProcessing) {
        return;
    }

    isProcessing = true;
    const int max = 5;

    if (!imgData.empty()) {
        imgData.clear();
    }

    button_panel->DisableAllButtons();
    timer.Stop();
    // OnToggleCamera();

    loadExecutor(max);
    // ! No guarantee that the images are already loaded
    img_bitmap->SetImage(imgData[0].image);

    siftExecutor(max);
    std::cout << "Sift Done" << std::endl;
    houghExecutor(max);
    std::cout << "Hough Done" << std::endl;

    isProcessing = false;

    for (int i = 0; i < 5; i++) {
        // img_bitmap->SetImage(imgData[i].image);
        img_bitmap->SetImage(imgData[i].hough.canny);
        cv::Mat canny = imgData[i].hough.canny;
        std::cout << "Canny: " << canny.size() << std::endl;
        std::cout << "Canny: " << canny.channels() << std::endl;
        std::vector<Detection::Line> lines = imgData[i].hough.lines;
        for (Detection::Line line : lines) {
            std::cout << line.ToString() << std::endl;
        }
        wxYield();
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }

    // OnToggleCamera();
    button_panel->EnableAllButtons();
}

void CameraPanel::OnToggleCamera() {
    AppConfig *config = new AppConfig();
    timer.Start(config->GetCameraPanelRefreshRate());
    // if (isTimerRunning) {
    //     isTimerRunning = false;
    //     timer.Start(1000);
    //     img_bitmap->SetImage();
    // } else {
    //     isTimerRunning = true;
    //     AppConfig *config = new AppConfig();
    //     timer.Start(config->GetCameraPanelRefreshRate());
    // }
}

std::vector<ImageData> CameraPanel::GetImgData() {
    if (imgData.empty()) {
        return std::vector<ImageData>();
    }
    return imgData;
}

// TODO: better implementation than MAX use ImageData.size() instead
void CameraPanel::captureExecutor(const int max) {
    threadPool.AddTask(new CaptureTask(&imgData, &camera, max));
    while (threadPool.isWorkerBusy() ||
           threadPool.HasTasks(TaskType::TASK_CAPTURE)) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        wxYield();
    }
}

void CameraPanel::loadExecutor(const int max) {
    threadPool.AddTask(new LoadTask(&imgData, filePath, max));
    while (threadPool.isWorkerBusy() ||
           threadPool.HasTasks(TaskType::TASK_LOAD)) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        wxYield();
    }
}

void CameraPanel::siftExecutor(const int max) {
    for (int i = 1; i < max; i++) {
        threadPool.AddTask(new SiftTask(&imgData, i));
    }
    while (threadPool.isWorkerBusy() ||
           threadPool.HasTasks(TaskType::TASK_SIFT)) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        wxYield();
    }
}

void CameraPanel::houghExecutor(const int max) {
    for (int i = 0; i < max; i++) {
        threadPool.AddTask(new HoughTask(&imgData, i));
    }
    while (threadPool.isWorkerBusy() ||
           threadPool.HasTasks(TaskType::TASK_HOUGHLINE)) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        wxYield();
    }
}

// clang-format off
wxBEGIN_EVENT_TABLE(CameraPanel, wxPanel) 
    EVT_BUTTON(wxID_ANY, CameraPanel::OnButton)
wxEND_EVENT_TABLE()
