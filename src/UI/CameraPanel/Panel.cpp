#include <UI/CameraPanel/Panel.hpp>

CameraPanel::CameraPanel(wxWindow *parent, wxWindowID id)
    : wxPanel(parent, id), imgData(std::vector<ImageData>()), threadPool(1),
      processThread(nullptr) {
    button_panel = new CameraPanelButton(this, Enum::CP_BUTTON_PANEL_ID,
                                         &camera, &imgData, &threadPool);
    button_panel_hough =
        new ButtonPanelHough(this, Enum::CP_BUTTON_PANEL_HOUGH_ID);

    img_bitmap = new wxImagePanel(this);

    main_sizer = new wxBoxSizer(wxVERTICAL);
    main_sizer->Add(button_panel, 0, wxEXPAND);
    main_sizer->Add(button_panel_hough, 0, wxEXPAND);
    main_sizer->Add(img_bitmap, 1, wxEXPAND);

    button_panel_hough->Hide();
    SetSizer(main_sizer);
    Fit();

    // img_bitmap->Bind(wxEVT_SIZE, &CameraPanel::OnSize, this);
    // img_bitmap->Bind(wxEVT_LEFT_DOWN, &CameraPanel::OnLeftDown, this);

    AppConfig *config = new AppConfig();
    CameraConfig cameraConfig = config->GetCameraConfig();
    camera.open(cameraConfig.Camera_ID);
    if (!camera.isOpened()) {
        wxMessageBox("Could not open camera", "Error", wxOK | wxICON_ERROR);
        Close();
    }
    camera.set(cv::CAP_PROP_FRAME_WIDTH, cameraConfig.Camera_Width);
    camera.set(cv::CAP_PROP_FRAME_HEIGHT, cameraConfig.Camera_Height);
    camera.set(cv::CAP_PROP_FPS, cameraConfig.Camera_FPS);
};

CameraPanel::~CameraPanel() {
    if (camera.isOpened()) {
        camera.release();
    }

    // if (loadFileThread != nullptr) {
    //     loadFileThread->Delete();
    //     loadFileThread->Wait();
    //     delete loadFileThread;
    //     loadFileThread = nullptr;
    // }

    if (processThread != nullptr) {
        processThread->Delete();
        processThread->Wait();
        delete processThread;
        processThread = nullptr;
    }

    delete button_panel;
    delete img_bitmap;
}

void CameraPanel::OnLeftDown(wxMouseEvent &e) {}

void CameraPanel::OnSize(wxSizeEvent &e) {
    // img_bitmap->drawBitMap(); }
}

void CameraPanel::OnButton(wxCommandEvent &e) {

    // if (e.GetId() == Enum::CP_Load_Button_ID) {
    //     OnLoadFile();
    // }

    if (e.GetId() == Enum::CP_Camera_Button_ID) {
        button_panel->Hide();
        button_panel_hough->Show();
        GetSizer()->Layout();
    }

    if (e.GetId() == Enum::CP_Canny_Button_ID) {
        button_panel_hough->Hide();
        button_panel->Show();
        GetSizer()->Layout();
    }
}

void CameraPanel::OnUpdateImage(UpdateImageEvent &e) {
    if (e.GetId() == UPDATE_IMAGE) {
        cv::Mat imageData = e.GetImageData();
        img_bitmap->SetImage(imageData);
    }

    if (e.GetId() == CLEAR_IMAGE) {
        img_bitmap->SetImage();
    }
}

void CameraPanel::OnProcessImage(wxCommandEvent &e) {
    std::cout << "Process Image" << std::endl;
    processThread = new ProcessThread(this, &threadPool, &imgData);
    processThread->Run();
}

void CameraPanel::OnLoadFile() {
    // AppConfig *config = new AppConfig();
    // wxString filePath = config->GetLoadFileName();
    // if (filePath == "") {
    //     return;
    // }
    // if (loadFileThread != nullptr) {
    //     return;
    // }

    // loadFileThread = new LoadFileThread(this, &threadPool, &imgData,
    // filePath); loadFileThread->Run();
}

// clang-format off
wxBEGIN_EVENT_TABLE(CameraPanel, wxPanel) 
    EVT_UPDATEIMAGE(wxID_ANY, CameraPanel::OnUpdateImage)
    EVT_COMMAND(wxID_ANY, c_PROCESS_IMAGE_EVENT ,CameraPanel::OnProcessImage)
    EVT_BUTTON(wxID_ANY, CameraPanel::OnButton)
wxEND_EVENT_TABLE()
